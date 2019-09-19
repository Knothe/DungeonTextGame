
#include <windows.h>
#include <string>
#include <iostream>
#include <string>
#include <forward_list>
#include <fstream>
#include <stdio.h>
#include "Item.h"
#include "Key.h"
#include "Player.h"
#include "Room.h"
#include "Shield.h"
#include "Sword.h"
#include "Door.h"
#include "Boss.h"
#include "Dungeon_Battle.h"
#include "Dungeon_Exception.h"
#include "RoomSaver.h"
#include "SetGame.h"

#define FILE_MENU_NEW 1
#define FILE_MENU_EXIT 2
#define GET_TEXT 3
#define FILE_MENU_SAVE 4
#define MIN_SIZE_X 1400
#define MIN_SIZE_Y 800

using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;
using std::array;

vector<Sword> sword_list;
vector<Shield> shield_list;
vector<Key> key_list;
vector<Room> room_list;
Player player;
array<bool, 28> rooms_visited;

void setRooms();
void setDoorList();
void setItems();
void fillEnemyRoom(int);
void fillEnemyRoom();
void fillRoom(int, vector<int>);
void fillRoom();
void loadPlayer();
void loadPlayer(PlayerSaver);
void loadGame();
void saveGame();
void newGame();
void DrawMap(HWND, int, int);
Key* getKey(int);
void paintRect(HDC, RECT*, int);
void DrawSavedMap(HWND);
void SetNewText();

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

HMENU hMenu;
HWND TextBox;
HWND DisplayText;

void AddMenu(HWND hWnd);
void AddControls(HWND hWnd);
void resetMap(HWND hWnd);


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, INT ncmdshow) {
	
	try {
		loadGame();
	}
	catch (std::exception& e) {
		return -1;
	}
	player.isTurn();
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"myWindowClass", L"Dungeon Game", WS_POPUP | WS_VISIBLE,0,0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NULL, NULL, NULL, NULL);
	
	MSG msg = { 0 };

	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_CREATE:
		AddMenu(hWnd);
		AddControls(hWnd); 
		break;
	case WM_COMMAND: {
		switch (wp) {
		case FILE_MENU_EXIT:
			DestroyWindow(hWnd);
			break;
		case FILE_MENU_NEW: {
			int i = MessageBoxA(hWnd, "Estas seguro", "Really", MB_YESNO | MB_ICONQUESTION);
			if (i == IDYES) {
				newGame();
				MessageBoxA(hWnd, "Se ha creado un nuevo juego", "Nuevo Juego", MB_OK);
				resetMap(hWnd);
				SetNewText();
			}
			
			break;
		}
		case FILE_MENU_SAVE: {
			if (!player.isInBattle()) {
				int i = MessageBoxA(hWnd, "Estas seguro", "Really", MB_YESNO | MB_ICONQUESTION);
				if (i == IDYES) {
					saveGame();
					MessageBoxA(hWnd, "Se ha guardado el juego", "Guardar", MB_OK);
				}
			}
			else {
				MessageBoxA(hWnd, "Estas en pelea", "Mensaje", MB_OK);
			}
			
			break;
		}
		case GET_TEXT: {

			try {
				player.setPlayerTurn(false);
				player.setHWND(hWnd);
				int length = GetWindowTextLength(TextBox) + 1;
				char text[50];
				std::string _s;
				GetWindowTextA(TextBox, text, length);
				_s = text;
				SetWindowTextA(TextBox, "");
				if (_s == "")
					throw Dungeon_Exception("No pusiste nada");
				player.readIndication(_s);
			}
			catch (Dungeon_Exception& e) {
				string s = e.what();
				MessageBoxA(hWnd, s.c_str(), "Mensaje", MB_OK);
				if (s == "Crafteaste una Katana III")
					player.setSword(&sword_list[5]);
				else if (s == "Crafteaste una Espada III")
					player.setSword(&sword_list[2]);
				else if (s == "Crafteaste una Scimitarra III")
					player.setSword(&sword_list[8]);
				else if (s == "Crafteaste una Guadaña III")
					player.setSword(&sword_list[11]);
				else if (s == "Crafteaste a Excalibur")
					player.setSword(&sword_list[12]);
				else if (s == "Se guardara la partida") {
					int i = MessageBoxA(hWnd, "Estas seguro", "Really", MB_YESNO | MB_ICONQUESTION);
					if (i == IDYES) {
						saveGame();
						MessageBoxA(hWnd,"Partida Guardada", "Mensaje", MB_OK);
					}
				} else if (s == "Nueva Partida") {
					if (MessageBoxA(hWnd, "Estas seguro", "Really", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						newGame();
						MessageBoxA(hWnd, "Partida Nueva", "Mensaje", MB_OK);
						resetMap(hWnd);
					}
				} else if ((s == "Estas en pelea") || (s == "No es válida la indicacion") 
					|| (s == "Estas en pelea") || (s == "Especifica lo que queires ver") ||
					(s == "No pusiste una accion aceptable") || (s == "No es un hechizo valido")){
					player.setPlayerTurn(true);
				}
				s = player.getCurrentRoom()->getData();
				SetWindowTextA(DisplayText, s.c_str());
			}
			catch (string s) {
				player.setPlayerTurn(true);
				SetWindowTextA(DisplayText, s.c_str());
			}
			catch (int i) {
				string s;
				s = player.getCurrentRoom()->getData();
				SetWindowTextA(DisplayText, s.c_str());
				rooms_visited[player.getCurrentRoom()->getID() - 1] = true;
				DrawMap(hWnd, i, player.getCurrentRoom()->getID());
				
			}
			
			if (player.isInBattle() && !player.isTurn()) {
				if (player.getCurrentRoom()->hasEnemy()) {
					player.enemyTurn(player.getCurrentRoom()->getEnemyList());
					player.reduceSpells();
				} else {
					player.endBattle();
				}
				
			}

			}
			break;
		default:
			return DefWindowProc(hWnd, msg, wp, lp);
		}
		break;
	}
	case WM_GETMINMAXINFO: {
		MINMAXINFO* pMinMax = (MINMAXINFO*)lp;
		pMinMax->ptMinTrackSize.x = MIN_SIZE_X;
		pMinMax->ptMinTrackSize.y = MIN_SIZE_Y;
		break;
	}
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		RECT rc;
		DrawSavedMap(hWnd);
		EndPaint(hWnd, &ps);

		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void resetMap(HWND hWnd) {
	string s;
	RECT rc;
	HDC hdc = GetDC(hWnd);
	rc.top = 0;
	rc.left = 360;
	rc.right = 1281;
	rc.bottom = 1053;
	FillRect(hdc, &rc, (HBRUSH)GetStockObject(GRAY_BRUSH));
	rooms_visited.fill(false);
	rooms_visited[0] = true;
	DrawMap(hWnd, -1, 1);
	s = room_list[0].getData();
	SetWindowTextA(DisplayText, s.c_str());
}

void AddMenu(HWND hWnd){
	hMenu = CreateMenu();
	HMENU fileHMenu = CreateMenu();
	AppendMenu(fileHMenu, MF_STRING, FILE_MENU_NEW, L"New");
	AppendMenu(fileHMenu, MF_STRING, FILE_MENU_SAVE, L"Save");
	AppendMenu(fileHMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(fileHMenu, MF_STRING, FILE_MENU_EXIT, L"Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)fileHMenu, L"File");
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}

void AddControls(HWND hWnd) {
	TextBox = CreateWindowW(L"Edit", L"", WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 10, 10, 330, 20, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"Button", L"Ingresar", WS_VISIBLE | WS_CHILD | WS_BORDER, 270, 40, 70, 20, hWnd, (HMENU)GET_TEXT, NULL, NULL);
	DisplayText = CreateWindowW(L"Static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 1500, 30, 400, 1000, hWnd, NULL, NULL, NULL);
	SetNewText();
}

void SetNewText() {
	string s = "Has sido un prisionero durante suficiente tiempo, después de esperar has encontrado a los aliados perfectos para salir, solo hay un pequeño problema: \n";
	s += "           -Todos al ser criminales de alto nivel están siendo vigilados por monstruos ancestrales\n";
	s += "Tu objetivo será recorrer la prisión en busca de tus 4 compañeros de escape, derrota a los 4 jefes y serás libre\n\n";
	s += "          -------------------------Indicaciones-------------------------\n";
	s += "     === Instrucciones ===\n";
	s += "Todas las indicaciones deberán tener un verbo y después el sujeto :\n";
	s += "\tAtacar enemigo (indicacion correcta)\n";
	s += "\tEnemigo atacar (indicacion incorrecta)\n";
	s += "Habrá cosas que puedes poner con una sola palabra, será cosa de que las descubras\n\n";
	s += "     === Batallas ===\n";
	s += "Cuando encuentre enemigos podrás ignorarlos tranquilamente, pero para iniciar una pelea deberás ingresar la palabra 'pelear'\n";
	s += "El único momento donde no se te permite ignorar a los enemigos es cuando hay un boss presente, así que prepárate antes de enfrentar uno\n";
	s += "Habrá acciones que no puedes hacer hasta que la batalla termine, pero no hay de que preocuparse, no perderás tu turno por ingresar un comando mal\n";
	s += "Cuando derrotes a los enemigos del cuarto podrás lootearlos, así conseguiras items que puedes intercambiar por armas, escudos y curaciones\n";
	s += "Es importante lootear a los enemigos, ya que si sales del juego antes de hacerlo se mantendrán muertos y se PERDERAN las cosas que cargan\n\n";
	s += "Siempre que tengas dudas puedes escribir 'help' para ver los comandos utilizables";
	SetWindowTextA(DisplayText, s.c_str());
}

void DrawMap(HWND hWnd, int prevID, int currentID) {
	HDC hdc = GetDC(hWnd);
	RECT rc;
	int id = prevID;

	for (int i = 0; i < 2; i++) {
		switch (id) {
		case 1:
			rc.top = 972;
			rc.left = 522;
			rc.right = 1281;
			rc.bottom = 1053;
			paintRect(hdc, &rc, i);
			rc.top = 162;
			rc.left = 1170;
			rc.right = 1281;
			rc.bottom = 972;
			break;
		case 2:
			rc.top = 810;
			rc.bottom = 891;
			rc.left = 360;
			rc.right = 441;
			break;
		case 3:
			rc.top = 810;
			rc.bottom = 891;
			rc.left = 522;
			rc.right = 603;
			break;
		case 4:
			rc.top = 810;
			rc.bottom = 891;
			rc.left = 684;
			rc.right = 768;
			break;
		case 5:
			rc.top = 810;
			rc.bottom = 891;
			rc.left = 846;
			rc.right = 927;
			break;
		case 6:
			rc.top = 810;
			rc.bottom = 891;
			rc.left = 1008;
			rc.right = 1089;
			break;
		case 7:
			rc.left = 360;
			rc.right = 441;
			rc.top = 648;
			rc.bottom = 729;
			break;
		case 8:
			rc.left = 522;
			rc.right = 603;
			rc.top = 648;
			rc.bottom = 729;
			break;
		case 9:
			rc.left = 684;
			rc.right = 768;
			rc.top = 648;
			rc.bottom = 729;
			break;
		case 10:
			rc.left = 1008;
			rc.right = 1089;
			rc.top = 648;
			rc.bottom = 729;
			break;
		case 11:
			rc.left = 360;
			rc.right = 441;
			rc.top = 486;
			rc.bottom = 567;
			break;
		case 12:
			rc.left = 533;
			rc.right = 768;
			rc.top = 486;
			rc.bottom = 567;
			break;
		case 13:
			rc.left = 846;
			rc.right = 927;
			rc.top = 324;
			rc.bottom = 729;
			break;
		case 14:
			rc.left = 1008;
			rc.right = 1089;
			rc.top = 486;
			rc.bottom = 567;
			break;
		case 15:
			rc.left = 360;
			rc.right = 441;
			rc.top = 324;
			rc.bottom = 405;
			break;
		case 16:
			rc.left = 522;
			rc.right = 603;
			rc.top = 324;
			rc.bottom = 405;
			break;

		case 17:
			rc.left = 684;
			rc.right = 768;
			rc.top = 324;
			rc.bottom = 405;
			break;
		case 18:
			rc.left = 1008;
			rc.right = 1089;
			rc.top = 324;
			rc.bottom = 405;
			break;
		case 19:
			rc.left = 360;
			rc.right = 441;
			rc.top = 162;
			rc.bottom = 243;
			break;
		case 20:
			rc.left = 522;
			rc.right = 603;
			rc.top = 162;
			rc.bottom = 243;
			break;
		case 21:
			rc.left = 684;
			rc.right = 768;
			rc.top = 162;
			rc.bottom = 243;
			break;
		case 22:
			rc.left = 846;
			rc.right = 927;
			rc.top = 162;
			rc.bottom = 243;
			break;
		case 23:
			rc.left = 1008;
			rc.right = 1089;
			rc.top = 162;
			rc.bottom = 243;
			break;
		case 24:
			rc.left = 360;
			rc.right = 441;
			rc.top = 0;
			rc.bottom = 81;
			break;
		case 25:
			rc.left = 522;
			rc.right = 603;
			rc.top = 0;
			rc.bottom = 81;
			break;
		case 26:
			rc.left = 684;
			rc.right = 768;
			rc.top = 0;
			rc.bottom = 81;
			break;
		case 27:
			rc.left = 846;
			rc.right = 927;
			rc.top = 0;
			rc.bottom = 81;
			break;
		case 28:
			rc.left = 1008;
			rc.right = 1089;
			rc.top = 0;
			rc.bottom = 81;
			break;
		default:
			rc.top = 0;
			rc.left = 0;
			rc.right = 0;
			rc.bottom = 0;
		}
		paintRect(hdc, &rc, i);
		id = currentID;
	}
}

void DrawSavedMap(HWND hWnd) {
	bool isVisited;
	for (int i = 1; i <= 28; i++) {
		if (rooms_visited[i - 1]) {
			if (i == player.getCurrentRoom()->getID())
				DrawMap(hWnd, -1, i);
			else
				DrawMap(hWnd, i, -1);
		}
	}
}

void paintRect(HDC hdc, RECT* rc, int i) {
	if (i == 0) {
		FillRect(hdc, rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
	}
	else if (i == 1) {
		FillRect(hdc, rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
	} 
}

void newGame() {
	remove("DungeonGame.dat");
	room_list.erase(room_list.begin(), room_list.end());
	setRooms();
	setDoorList();
	fillEnemyRoom();
	fillRoom();
	player.restartPlayer(&room_list[0]);
}

void setRooms()
{
	room_list.push_back(Room("Te encuentras en el pasillo que lleva a las celdas de alto nivel, a partir de aqui solo puedes acceder a un cuarto sin llave, aunque es más fácil tomar la otra puerta.", false, 1, 0));
	room_list.push_back(Room("¡Uno de los prisioneros está siendo protegido por un Ciclope!\nEs tan alto que básicamente toca el techo de la prisión, deberás derrotarlo para llegar a uno de tus aliados", true, 2, 0));
	room_list.push_back(Room("Esta zona es bastante concurrida por estar tan cerca de la salida, los enemigos aparecen bastante seguido", true, 3, -2));
	room_list.push_back(Room("La puerta que tomes desde esta zona determinará tu destino, que decides?", false, 4, 2));
	room_list.push_back(Room("Solo es un pasillo que lleva de la cocina al comedor, tal vez por eso hay sangre y huesos tirados por todos lados, aunque los rasguños son algo raros", false, 5, 0));
	room_list.push_back(Room("La cocina no se ve tan mal, al final, un poco grasosa, bastantes cosas tiradas en el suelo y, eso es un sartén mordido?", true, 6, -3));
	room_list.push_back(Room("La celda de uno de tus compañeros está cerca, estás seguro que tienes la llave?", false, 7, 0));
	room_list.push_back(Room("Detrás de esta puerta hay una sala de torturas, aunque las paredes son bastante grandes aquí incluso podrías escuchar los gritos desde este lado, que les harán?", false, 8, 0));
	room_list.push_back(Room("Por alguna razón, aunque estamos cerca de la salida a los guardias no les gusta pasar mucho por aqui, realmente nadie más pasa por aqui", true, 9, 0));
	room_list.push_back(Room("¡Uno de los prisioneros está siendo protegido por un cerbero, su pelaje y tamaño son bastante intimidantes. Un momento, trae una espada en el hocico?", true, 10, 0));

	room_list.push_back(Room("Parece que por aquí se llevan a los prisioneros del otro cuarto, no tienen mucho sentido de la limpieza porque aún puedes ver la sangre en el suelo, se siente bastante húmeda\n Deberían subir los estándares de limpieza", false, 11, 0));
	room_list.push_back(Room("¡LA SALA DE TORTURA! Tiene herramientas increíbles, hay una rueda, una silla de picos, una sierra, una cuña, parece que hay de todo aquí. Aunque es la primera vez que veo una pera así", true, 12, 5));
	room_list.push_back(Room("El comedor, es bastante grande, las sillas son de bastantes tamaños, hasta hay un plato que parece ser para perros, unos 3 al parecer.\nComo todo buen comedor está a lado de la sala de tortura, ¿a quién no se le antoja comer a lado de las almas en pena de los torturados?", true, 13, 10));
	room_list.push_back(Room("De aquí llegamos al comedor y, al parecer atrás de esta puerta está otro de tus aliados, ¿crees que las marcas de las garras en la puerta signifiquen algo?", false, 14, 0));
	room_list.push_back(Room("Los guardas revisan a los prisioneros que llegan de la sala de torturas aquí, siempre son los mismos al parecer", true, 15, 0));
	room_list.push_back(Room("¿No se te hace raro que los guardias aquí sean un poco inhumanos?, allá atrás encontré una bola de pelos", false, 16, 0));
	room_list.push_back(Room("¿Quién cierra esa puerta a la sala de torturas? Parece que la lógica no se aplica para nada a esta prisión", false, 17, 0));
	room_list.push_back(Room("Del otro lado de esta puerta está el mismo cuarto por el que llegaste pero, ¿Porqué esta puerta la mantienen cerrada?, les ha de gustar recibir a la gente por el otro lado\nQue gente tan amable", false, 18, 0));
	room_list.push_back(Room("Este cuarto tiene muchos golpes en las paredes y puertas, son circulares como si alguien golpeara un escudo contra todo, ¿será un indicio de lo que sucede aquí?\nNah, ha de ser meramente estético, me gusta el tono barroco que le da el detalle, curioso", false, 19, 0));
	room_list.push_back(Room("¡Mira!, un anuncio, parece que dice algo así:\n     'La puerta del jefe se encuentra cerrada, la entrada es por el otro ... ¿pato?', nunca he sido tan buen traductor la verdad", false, 20, 0));

	room_list.push_back(Room("Que curioso, ¿te has dado cuenta que en toda la prisión solo hay un baño?, y está aquí!\nPuedes pasar si tienes la necesidad ... ¿no? ... bueno, como quieras", true, 21, 0));
	room_list.push_back(Room("Escamas y pelo, escamas y pelo, esas cosas no se suelen llevar, no me imagino mucho a una serpiente y un gato de amigos, vaya, que divertida prisión", false, 22, 0));
	room_list.push_back(Room("¡Mira! dados, al parecer aquí se juntan los guardias para jugar, tal vez por eso no es tan transcurrido", true, 23, -5));
	room_list.push_back(Room("¡Un Minotauro, por eso las marcas en las paredes!, parece que un escudo es suficiente para pelear contra tí, tendrás que derrotarlo si quieres salir de aquí", true, 24, 0));
	room_list.push_back(Room("Bienvenido a la sala del director, tiene 2 puertas porque es un hombre exigente, aunque no se porque mantiene una cerrada siempre, hombre curioso, seguro oculta cosas privadas como, algún hobby extraño debe ser\n¡Mira! una colección de monedas", true, 25, 0));
	room_list.push_back(Room("Esta sala no concuerda con el resto de la prisión, está demasiado limpia y sin cosas, tal vez por eso no les gusta pasar por aquí", false, 26, 0));
	room_list.push_back(Room("Pelos y escamas, pelos y escamas, ¡Hay demasiadas!", false, 27, 0));
	room_list.push_back(Room("¡Quimeras, Quimeras!, en mi opinion la cola es la peor parte para tener a una serpente pero, de todas formas hay que derrotarlo", true, 28, 0));
	room_list.push_back(Room("Cuarto final, el jefe de la prisión está aqui para derrotarte, mientras no mueras todo estará bien, sencillo, ¿no?", true, 29, 0));

}

void fillEnemyRoom(int id) {
	switch (id) {
	case 1:
		room_list[1].addEnemy(new Boss(50, 23, 8, 7, 12, 20, 5, 9, 6, 15, &sword_list[2], NULL));
		room_list[1].addEnemy(new Enemy(30, 20, 8, 7, 10, 15, 1, 2, 3, 1));
		room_list[1].addEnemy(new Enemy(30, 12, 13, 21, 7, 17, 3, 3, 3, 3));
		break;
	case 8:
		room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));
		room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 7));
		room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));
		break;
	case 9:
		room_list[9].addEnemy(new Boss(50, 5, 22, 11, 7, 20, 4, 3, 1, 16, &sword_list[8], NULL));
		room_list[9].addEnemy(new Enemy(30, 23, 8, 7, 12, 20, 3, 2, 3, 0));
		room_list[9].addEnemy(new Enemy(30, 12, 13, 21, 7, 17, 3, 3, 3, 3));
		break;
	case 14:
		room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 1, 1, 0));
		room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 1, 7, 1));
		room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 4, 1, 1));
		break;
	case 20:
		room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 8, 1, 0, 5));
		room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 5, 0));
		room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 7, 0, 0));
		break;
	case 23:
		room_list[23].addEnemy(new Boss(50, 12, 13, 21, 7, 17, 4, 4, 4, 14, NULL, &shield_list[2]));
		room_list[23].addEnemy(new Enemy(30, 5, 22, 11, 7, 20, 2, 3, 3, 0));
		room_list[23].addEnemy(new Enemy(30, 23, 8, 7, 12, 20, 1, 2, 3, 2));
		break;
	case 24:
		room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 2));
		room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));
		room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));
		break;
	case 27:
		room_list[27].addEnemy(new Boss(50, 5, 22, 11, 12, 20, 3, 2, 3, 0, NULL, &shield_list[8]));
		room_list[27].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));
		room_list[27].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));
		break;
	
	}
}

void fillEnemyRoom() {
	room_list[1].addEnemy(new Boss(50, 23, 8, 7, 12, 20, 5, 9, 6, 15, &sword_list[2], NULL));
	room_list[1].addEnemy(new Enemy(30, 20, 8, 7, 10, 15, 1, 2, 3, 1));
	room_list[1].addEnemy(new Enemy(30, 12, 13, 21, 7, 17, 3, 3, 3, 3));

	room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));
	room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 7));
	room_list[8].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));

	room_list[9].addEnemy(new Boss(50, 5, 22, 11, 7, 20, 4, 3, 1, 16, &sword_list[8], NULL));
	room_list[9].addEnemy(new Enemy(30, 23, 8, 7, 12, 20, 3, 2, 3, 0));
	room_list[9].addEnemy(new Enemy(30, 12, 13, 21, 7, 17, 3, 3, 3, 3));

	room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 1, 1, 0));
	room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 1, 7, 1));
	room_list[14].addEnemy(new Enemy(15, 7, 7, 15, 5, 5, 1, 4, 1, 1));

	room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 8, 1, 0, 5));
	room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 5, 0));
	room_list[20].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 7, 0, 0));

	room_list[23].addEnemy(new Boss(50, 12, 13, 21, 7, 17, 4, 4, 4, 14, NULL, &shield_list[2]));
	room_list[23].addEnemy(new Enemy(30, 5, 22, 11, 7, 20, 2, 3, 3, 0));
	room_list[23].addEnemy(new Enemy(30, 23, 8, 7, 12, 20, 1, 2, 3, 2));

	room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 2));
	room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));
	room_list[24].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));

	room_list[27].addEnemy(new Boss(50, 5, 22, 11, 12, 20, 3, 2, 3, 0, NULL, &shield_list[8]));
	room_list[27].addEnemy(new Enemy(25, 5, 5, 15, 9, 15, 2, 2, 2, 0));
	room_list[27].addEnemy(new Enemy(20, 10, 3, 10, 5, 20, 1, 1, 0, 0));
}

void fillRoom(int id, vector<int> item_list) {
	try {
		for (int i = 0; i < item_list.size(); i++) {
			if (item_list[i] >= 50 && item_list[i] < 65) {
 				room_list[id].addItem(&sword_list[item_list[i] % 50]);
			}
			else if (item_list[i] >= 65) {
				room_list[id].addItem(&shield_list[item_list[i] % 65]);
			}
			else {
				room_list[id].addItem(getKey(item_list[i]));
			}
		}
	}
	catch (std::exception& e) {
		cout << e.what();
	}
	
}

void fillRoom() {
	//0
	room_list[0].addItem(&sword_list[0]); 
	//1
	room_list[1].addItem(&shield_list[5]);
	//5
	room_list[5].addItem(&key_list[2]);
	room_list[5].addItem(&sword_list[3]);
	//6
	room_list[6].addItem(&key_list[9]);
	room_list[6].addItem(&sword_list[7]);
	//7
	room_list[7].addItem(&key_list[1]);
	room_list[7].addItem(&shield_list[0]);
	//10
	room_list[10].addItem(&shield_list[3]);
	//11
	room_list[11].addItem(&key_list[6]);
	//12
	room_list[12].addItem(&key_list[4]);
	room_list[12].addItem(&sword_list[6]);
	//13
	room_list[13].addItem(&key_list[8]);
	room_list[13].addItem(&shield_list[6]);
	//15
	room_list[15].addItem(&sword_list[10]);
	//17
	room_list[17].addItem(&key_list[7]);
	//18
	room_list[18].addItem(&sword_list[1]);
	//19
	room_list[19].addItem(&key_list[5]);
	room_list[19].addItem(&shield_list[1]);
	//20
	room_list[20].addItem(&sword_list[9]);
	//21
	room_list[21].addItem(&shield_list[4]);
	//22
	room_list[22].addItem(&key_list[0]);
	//24
	room_list[24].addItem(&shield_list[5]);
	//25
	room_list[25].addItem(&key_list[3]);
	//26
	room_list[26].addItem(&sword_list[4]);
}

void setItems() {

	sword_list.push_back(Sword(50, "Espada I", 3, 2, 1, 0, 0));
	sword_list.push_back(Sword(51, "Espada II", 6, 5, 2, 2, 0));
	sword_list.push_back(Sword(52, "Espada III", 16, 10, 5, 5, -3));
	sword_list.push_back(Sword(53, "Katana I", 2, 0, 3, 1, 0));
	sword_list.push_back(Sword(54, "Katana II", 6, 0, 5, 0, 4));
	sword_list.push_back(Sword(55, "Katana III", 12, 0, 7, 7, 7));
	sword_list.push_back(Sword(56, "Scimitarra I", 1, 2, 0, 3, 0));
	sword_list.push_back(Sword(57, "Scimitarra II", 5, 3, 3, 2, 2));
	sword_list.push_back(Sword(58, "Scimitarra III", 7, 7, 7, 7, 5));
	sword_list.push_back(Sword(59, "Guadaña I", 2, 3, 1, 0, 0));
	sword_list.push_back(Sword(60, "Guadaña II", 5, 6, 0, 4, 0));
	sword_list.push_back(Sword(61, "Guadaña III", 10, 16, 3, 3, 0));
	sword_list.push_back(Sword(62, "Excalibur", 20, 15, -2, -2, 4));

	shield_list.push_back(Shield(65, "Escudo de Madera I", 3, 2, 1));
	shield_list.push_back(Shield(66, "Escudo de Madera II", 6, 5, 4));
	shield_list.push_back(Shield(67, "Escudo de Madera III", 12, 11, 10));
	shield_list.push_back(Shield(68, "Escudo de Metal I", 1, 3, 2));
	shield_list.push_back(Shield(69, "Escudo de Metal II", 4, 5, 6));
	shield_list.push_back(Shield(70, "Escudo de Metal III", 10, 12, 11));
	shield_list.push_back(Shield(71, "Escudo pequeño I", 2, 1, 3));
	shield_list.push_back(Shield(72, "Escudo pequeño II", 4, 5, 6));
	shield_list.push_back(Shield(73, "Escudo pequeño III", 11, 10, 12));

	key_list.push_back(Key(4, "Llave de boss"));//0
	key_list.push_back(Key(7, "Llave del comedor"));//1
	key_list.push_back(Key(9, "Llave para la sala de tortura"));//2
	key_list.push_back(Key(10, "Llave de boss"));//3
	key_list.push_back(Key(14, ""));//4
	key_list.push_back(Key(15, "Llave para la sala de tortura"));//5
	key_list.push_back(Key(20, "Llave del primer cuarto"));//6
	key_list.push_back(Key(27, "Llave de boss"));//7
	key_list.push_back(Key(28, "Llave de la oficina del jefe de prisión"));//8
	key_list.push_back(Key(33, "Llave de boss"));//9
}

void setDoorList() {

	vector<Door*> door_list;
	door_list.push_back(new Door(&room_list[0], &room_list[3], 0, false));
	door_list.push_back(new Door(&room_list[2], &room_list[3], 1, false));
	door_list.push_back(new Door(&room_list[3], &room_list[4], 2, false));
	door_list.push_back(new Door(&room_list[4], &room_list[5], 3, false));
	door_list.push_back(new Door(&room_list[1], &room_list[6], 4, true));
	door_list.push_back(new Door(&room_list[2], &room_list[7], 5, false));
	door_list.push_back(new Door(&room_list[3], &room_list[8], 6, false));
	door_list.push_back(new Door(&room_list[4], &room_list[12], 7, true));
	door_list.push_back(new Door(&room_list[6], &room_list[10], 8, false));
	door_list.push_back(new Door(&room_list[7], &room_list[11], 9, true));
	door_list.push_back(new Door(&room_list[9], &room_list[13], 10, true));
	door_list.push_back(new Door(&room_list[10], &room_list[11], 11, false));
	door_list.push_back(new Door(&room_list[11], &room_list[12], 12, false));
	door_list.push_back(new Door(&room_list[12], &room_list[13], 13, false));
	door_list.push_back(new Door(&room_list[10], &room_list[14], 14, true));
	door_list.push_back(new Door(&room_list[11], &room_list[16], 15, true));
	door_list.push_back(new Door(&room_list[13], &room_list[17], 16, false));
	door_list.push_back(new Door(&room_list[14], &room_list[15], 17, false));
	door_list.push_back(new Door(&room_list[15], &room_list[16], 18, false));
	door_list.push_back(new Door(&room_list[16], &room_list[12], 19, false));
	door_list.push_back(new Door(&room_list[17], &room_list[0], 20, true));
	door_list.push_back(new Door(&room_list[14], &room_list[18], 21, false));
	door_list.push_back(new Door(&room_list[15], &room_list[19], 22, false));
	door_list.push_back(new Door(&room_list[16], &room_list[20], 23, false));
	door_list.push_back(new Door(&room_list[12], &room_list[21], 24, false));
	door_list.push_back(new Door(&room_list[17], &room_list[21], 25, false));
	door_list.push_back(new Door(&room_list[21], &room_list[22], 26, false));
	door_list.push_back(new Door(&room_list[18], &room_list[23], 27, true));
	door_list.push_back(new Door(&room_list[19], &room_list[25], 28, true));
	door_list.push_back(new Door(&room_list[20], &room_list[25], 29, false));
	door_list.push_back(new Door(&room_list[21], &room_list[27], 30, false));
	door_list.push_back(new Door(&room_list[24], &room_list[25], 31, false));
	door_list.push_back(new Door(&room_list[25], &room_list[26], 32, false));
	door_list.push_back(new Door(&room_list[26], &room_list[27], 33, true));
	door_list.push_back(new Door(&room_list[7], &room_list[8], 34, false));
	door_list.push_back(new Door(&room_list[0], &room_list[28], 35, false));

	for (int i = 0; i < door_list.size(); i++) {
		Room* r;
		r = door_list[i]->getNextRoom();
		r->addDoor(door_list[i]);
		r = door_list[i]->getPreviousRoom();
		r->addDoor(door_list[i]);
	}
}

void loadPlayer(PlayerSaver p) {
	player.setCurrentRoom(&room_list[p.room_id - 1]);
	if (p.sword != -1)
		player.setSword(&sword_list[p.sword % 50]);
	if (p.shield != -1)
		player.setShield(&shield_list[p.shield % 65]);
	for (int i = 0; i < p.key_list.size(); i++) {
		player.addKey(getKey(p.key_list[i]));
	}
	player.setValues(p);
}

void loadPlayer() {
	player.setCurrentRoom(&room_list[0]);
}

void loadGame() {
	setRooms();
	setDoorList();
	setItems();

	ifstream savedFile;
	savedFile.open("DungeonGame.dat", std::ios::in);
	if (!savedFile.fail()) {
		PlayerSaver s;
		RoomSaver r;
		int num;
		short size;
		for (int i = 0; i < 28; i++) {
			savedFile.read((char*)& rooms_visited[i], sizeof(bool));
		}
		savedFile.read((char*)& s.room_id, sizeof(int));
		savedFile.read((char*)& s.sword, sizeof(int));
		savedFile.read((char*)& s.shield, sizeof(int));
		savedFile.read((char*)& s.life, sizeof(int));
		savedFile.read((char*)& s.rooms_passed, sizeof(int));
		savedFile.read((char*)& s.mana, sizeof(int));
		savedFile.read((char*)& s.bosses_defeated, sizeof(short));
		savedFile.read((char*)& size, sizeof(short));
		for (int i = 0; i < size; i++) {
			savedFile.read((char*)& num, sizeof(int));
			s.key_list.push_back(num);
		}
		for (int i = 0; i < 4; i++) {
			savedFile.read((char*)& num, sizeof(int));
			s.loot_list[i] = num;
		}
		loadPlayer(s);

		savedFile.read((char*)& r.id, sizeof(int));
		savedFile.read((char*)& r.hasEnemy, sizeof(bool));
		savedFile.read((char*)& size, sizeof(short));
		while (!savedFile.eof()) {
			if (r.hasEnemy)
				fillEnemyRoom(r.id - 1);
			if (size > 0) {
				vector<int> item;
				for (int i = 0; i < size; i++) {
					savedFile.read((char*)& num, sizeof(int));
					item.push_back(num);
				}
				fillRoom(r.id - 1, item);

			}
			savedFile.read((char*)& r.id, sizeof(int));
			savedFile.read((char*)& r.hasEnemy, sizeof(bool));
			savedFile.read((char*)& size, sizeof(short));
		}
	}
	else {
		rooms_visited.fill(false);
		rooms_visited[0] = true;
		fillRoom();
		fillEnemyRoom();
		loadPlayer(); 
		
	}
	savedFile.close();
}

void saveGame() {
	PlayerSaver playerSaver;
	ofstream saveFile;
	short size;
	saveFile.open("DungeonGame.dat", std::ios::out | std::ios::binary);
	saveFile.write((char*)& rooms_visited[0], 28 * sizeof(bool));
	playerSaver = player.getPlayerSaver();
	saveFile.write((char*)& playerSaver.room_id, sizeof(int));
	saveFile.write((char*)& playerSaver.sword, sizeof(int));
	saveFile.write((char*)& playerSaver.shield, sizeof(int));
	saveFile.write((char*)& playerSaver.life, sizeof(int));
	saveFile.write((char*)& playerSaver.rooms_passed, sizeof(int));
	saveFile.write((char*)& playerSaver.mana, sizeof(int));
	saveFile.write((char*)& playerSaver.bosses_defeated, sizeof(short));
	size = playerSaver.key_list.size();
	saveFile.write((char*)& size, sizeof(short));
	if (size > 0)
		saveFile.write((char*)& playerSaver.key_list[0], size * sizeof(int));
	saveFile.write((char*)& playerSaver.loot_list[0], 4 * sizeof(int));

	for (int i = 0; i < room_list.size(); i++) {
		RoomSaver r;
		r = room_list[i].getRoomSaver();
		size = r.item_id_list.size();
		saveFile.write((char*)& r.id, sizeof(int));
		saveFile.write((char*)& r.hasEnemy, sizeof(bool));
		saveFile.write((char*)& size, sizeof(short));
		if (size > 0) {
			saveFile.write((char*)& r.item_id_list[0], size * sizeof(int));
		}
	}
	
	saveFile.close();
}

Key* getKey(int i) {
	switch (i) {
	case 4: return &key_list[0];
		break;
	case 7: return &key_list[1];
		break;
	case 9: return &key_list[2];
		break;
	case 10: return &key_list[3];
		break;
	case 14: return &key_list[4];
		break;
	case 15: return &key_list[5];
		break;
	case 20: return &key_list[6];
		break;
	case 27: return &key_list[7];
		break;
	case 28: return &key_list[8];
		break;
	case 33: return &key_list[9];
		break;

	}
}
