#include "Player.h"
#include <sstream>
#include <algorithm>
#include "Enemy.h"
#include <time.h>
#include "Dungeon_Battle.h"

/*
@param life: initial life
@param attack: base attack
@param defense: base defense
@param speed: base speed
@param magic_attack: base magic attack
@param magic_defense: base magic defense
@param current_room: pointer to the first room

*/
Player::Player(int life, int attack, int defense, int speed, int magic_attack, int magic_defense, Room* current_room) 
:_life(life), _attack(attack),_defense(defense),_speed(speed),_magic_attack(magic_attack),
_magic_defense(magic_defense), _current_room(current_room) {
	_setIndicationList();
}

Player::Player() : _life(100), _attack(10), _defense(10), _speed(20), _magic_attack(10),
_magic_defense(10){
	_setIndicationList();
	_sword = NULL;
	_sword = NULL;
}

/*
@param current_room: pointer to the first room
*/
Player::Player(Room* current_room) : _life(100), _attack(10), _defense(10), _speed(20), _magic_attack(10),
_magic_defense(10), _current_room(current_room) {
	_setIndicationList();
	_sword = NULL;
	_sword = NULL;
}

void Player::setHWND(HWND hWnd) {
	_hWnd = hWnd;
}

void Player::setCurrentRoom(Room* current_room) {
	_current_room = current_room;
}

void Player::_setIndicationList()
{
	std::map<std::string, short> list;

	_indication_list.insert(pair<string, short>("atacar", 0));
	_indication_list.insert(pair<string, short>("pelear", 0));
	_indication_list.insert(pair<string, short>("pelea", 0));
	_indication_list.insert(pair<string, short>("ataque", 0));
	_indication_list.insert(pair<string, short>("batalla", 0));
	_indication_list.insert(pair<string, short>("iniciar", 0));
	_indication_list.insert(pair<string, short>("abrir", 1));
	_indication_list.insert(pair<string, short>("entrar", 1));
	_indication_list.insert(pair<string, short>("pasar", 1));
	_indication_list.insert(pair<string, short>("atravesar", 1));
	_indication_list.insert(pair<string, short>("cruzar", 1));
	_indication_list.insert(pair<string, short>("intercambiar", 2));
	_indication_list.insert(pair<string, short>("recoger", 2));
	_indication_list.insert(pair<string, short>("agarrar", 2));
	_indication_list.insert(pair<string, short>("coger", 2));
	_indication_list.insert(pair<string, short>("tomar", 2));
	_indication_list.insert(pair<string, short>("tirar", 3));
	_indication_list.insert(pair<string, short>("soltar", 3));
	_indication_list.insert(pair<string, short>("dejar", 3));
	_indication_list.insert(pair<string, short>("consultar", 4));
	_indication_list.insert(pair<string, short>("examinar", 4));
	_indication_list.insert(pair<string, short>("revisar", 4));
	_indication_list.insert(pair<string, short>("checar", 4));
	_indication_list.insert(pair<string, short>("ver", 4));
	_indication_list.insert(pair<string, short>("botin", 5));
	_indication_list.insert(pair<string, short>("crear", 5));
	_indication_list.insert(pair<string, short>("construir", 5));
	_indication_list.insert(pair<string, short>("hacer", 5));
	_indication_list.insert(pair<string, short>("habilidad", 6));
	_indication_list.insert(pair<string, short>("hechizo", 6));
	_indication_list.insert(pair<string, short>("lootear", 100));
	_indication_list.insert(pair<string, short>("save", 101));
	_indication_list.insert(pair<string, short>("salvar", 101));
	_indication_list.insert(pair<string, short>("guardar", 101));
	_indication_list.insert(pair<string, short>("nueva", 102));
	_indication_list.insert(pair<string, short>("partida", 102));
	_indication_list.insert(pair<string, short>("reinicio", 102));
	_indication_list.insert(pair<string, short>("reiniciar", 102));
	_indication_list.insert(pair<string, short>("help", 103));

	list.insert(pair<string, short>("enemigo", 0));
	list.insert(pair<string, short>("minion", 21));
	list.insert(pair<string, short>("boss", 22));
	list.insert(pair<string, short>("jefe", 22));
	list.insert(pair<string, short>("fisico", 0));
	list.insert(pair<string, short>("fuerte", 23));
	list.insert(pair<string, short>("debil", 23));
	list.insert(pair<string, short>("magico", 6));
	list.insert(pair<string, short>("magia", 6));
	_action_list.push_back(list);
	list.clear();

	list.insert(pair<string, short>("puerta", 9));
	_action_list.push_back(list);
	list.clear();

	list.insert(pair<string, short>("espada", 10));
	list.insert(pair<string, short>("katana", 10));
	list.insert(pair<string, short>("scimitarra", 10));
	list.insert(pair<string, short>("guadaña", 10));
	list.insert(pair<string, short>("escudo", 11));
	list.insert(pair<string, short>("llave", 12));
	_action_list.push_back(list);
	list.clear();

	list.insert(pair<string, short>("espada", 13));
	list.insert(pair<string, short>("katana", 13));
	list.insert(pair<string, short>("scimitarra", 13));
	list.insert(pair<string, short>("guadaña", 13));
	list.insert(pair<string, short>("escudo", 14));
	list.insert(pair<string, short>("llave", 15));
	_action_list.push_back(list);
	list.clear();

	list.insert(pair<string, short>("cuarto", 16));
	list.insert(pair<string, short>("habitacion", 16));
	list.insert(pair<string, short>("cosas", 17));
	list.insert(pair<string, short>("carga", 17));
	list.insert(pair<string, short>("items", 17));
	list.insert(pair<string, short>("objetos", 17));
	list.insert(pair<string, short>("espada", 17));
	list.insert(pair<string, short>("escudo", 17));
	list.insert(pair<string, short>("loot", 17));
	list.insert(pair<string, short>("enemigo", 18));
	list.insert(pair<string, short>("enemigos", 18));
	list.insert(pair<string, short>("monstruos", 18));
	list.insert(pair<string, short>("estado", 19));
	list.insert(pair<string, short>("vida", 19));
	list.insert(pair<string, short>("mana", 19));
	list.insert(pair<string, short>("ataque", 19));
	list.insert(pair<string, short>("defensa", 19));
	list.insert(pair<string, short>("velocidad", 19));
	list.insert(pair<string, short>("player", 19));
	list.insert(pair<string, short>("stats", 19));
	list.insert(pair<string, short>("state", 19));
	list.insert(pair<string, short>("estatus", 19));
	list.insert(pair<string, short>("hechizos", 20));
	list.insert(pair<string, short>("spells", 20));
	list.insert(pair<string, short>("magia", 20));
	list.insert(pair<string, short>("crafteable", 24));
	list.insert(pair<string, short>("construir", 24));
	list.insert(pair<string, short>("construible", 24));
	list.insert(pair<string, short>("craftear", 24));
	list.insert(pair<string, short>("crafteable", 24));
	list.insert(pair<string, short>("hacer", 24));
	list.insert(pair<string, short>("reglas", 30));
	list.insert(pair<string, short>("instrucciones", 30));
	list.insert(pair<string, short>("indicaciones", 30));
	_action_list.push_back(list);
	list.clear();

	list.insert(pair<string, short>("espada", 25));
	list.insert(pair<string, short>("katana", 26));
	list.insert(pair<string, short>("guadaña", 27));
	list.insert(pair<string, short>("scimitarra", 28));
	list.insert(pair<string, short>("simitarra", 28));
	list.insert(pair<string, short>("excalibur", 29));
	_action_list.push_back(list);
	list.clear();
}

/*
@param indication: text that the player inputted
*/
void Player::readIndication(string indication){

	short first_word = -1;
	std::transform(indication.begin(), indication.end(), indication.begin(), ::tolower);
	std::stringstream ss(indication);
	string word;
	while(ss && first_word == -1) {
		ss >> word;
		first_word = findInMap(&_indication_list, word);
	} 
	if (first_word != -1) {
		short second_word = -1;
		short number = -1;
		bool isNumber = true;
		while (ss && second_word == -1 && first_word < _action_list.size()) {
			ss >> word;
			second_word = findInMap(&_action_list[first_word], word);
		}
		while (ss)  {
			ss >> word;
			isNumber = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (word[i] < '0' || word[i] > '9') {
					isNumber = false;
					break;
				}
			}
			if (isNumber) {
				number = stoi(word);
				break;
			}
				
		}
		if (second_word == -1)
			second_word = first_word;
		applyAction(second_word, number);
	} else {
		throw Dungeon_Exception("No pusiste una accion aceptable");
	}
}

/*
@param map: pointer to the map we are looking into
@param word: word we are looking

@return: if word is found, return its number, else return -1
*/
int Player::findInMap(map<string, short>* const map, string word)
{
	std::map<string, short>::iterator it;
	it = map->find(word);
	if(it != map->end()) {
		return it->second;
	} else {
		return -1;
	}
}

/*
@param action: number of the action the player is going to do
@param number: number inputted by the player
*/
void Player::applyAction(short action, short number) {
	switch (action) {
	case 0:
		if (_current_room->hasEnemy()) {
			if (!_isInBattle) {
				startBattle();
			}
			else {
				attackEnemy(_current_room->getEnemyList(), false);
			}
		} else
			throw Dungeon_Exception("No hay enemigos aqui");
		break;
	case 1:
		throw Dungeon_Exception("No completaste la indicacion");
		break;
	case 2:
		if(!_isInBattle)
			throw Dungeon_Exception("Indica lo que quieres recoger");
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 3:
		if (!_isInBattle)
			throw Dungeon_Exception("Indica lo que quieres tirar");
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 4:
		throw Dungeon_Exception("Especifica lo que queires ver");
		break;
	case 5:
		throw Dungeon_Exception("Indica que quieres construir");
		break;
	case 6:
		if (_isInBattle) {
			_magicAttack(number);
		}
		else
			throw Dungeon_Exception("Tienes que iniciar batalla primero");
		break;
	case 9:
		if (!_isInBattle)
			changeRoom(number);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 10: 
		if (!_isInBattle) {
			if (_current_room->hasEnemy())
				throw Dungeon_Exception("Hay enemigos en el cuarto");
			else
				_sword = grabItem(_sword, number);
			throw Dungeon_Exception("Has agarrado el item");
		}
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 11:
		if (!_isInBattle) {
			if (_current_room->hasEnemy())
				throw Dungeon_Exception("Hay enemigos en el cuarto");
			else
				_shield = grabItem(_shield, number);
			throw Dungeon_Exception("Has agarrado el item");
		}
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 12:
		if (!_isInBattle) {
			if (_current_room->hasEnemy())
				throw Dungeon_Exception("Hay enemigos en el cuarto");
			else
				grabKey(number);
		}
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 13:
		if (!_isInBattle)
			_sword = grabItem(_sword, -2);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 14:
		if (!_isInBattle)
			_shield = grabItem(_shield, -2);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 15:
		if (!_isInBattle)
			leaveKey(number);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 16:
		throw _current_room->getData();
		break;
	case 17:
		printItems();
		break;
	case 18:
		throw _current_room->printEnemies();
		break;
	case 19:
		printStatus();
		break;
	case 20:
		printMagic();
		break;
	case 21:
		if (_isInBattle)
			attackMinion(_current_room->getEnemyList(), false);
		else
			throw Dungeon_Exception("Necesitas iniciar la batalla");
		break;
	case 22:
		if (_isInBattle)
			attackBoss(_current_room->getEnemyList(), false);
		else
			throw Dungeon_Exception("Necesitas iniciar la batalla");
		break;
	case 23:
		if (_isInBattle)
			attackEnemy(_current_room->getEnemyList(), true);
		else
			throw Dungeon_Exception("Necesitas iniciar la batalla");
		break;
	case 24:
		if (!_isInBattle)
			checkCrafteable();
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 25:
		if (!_isInBattle)
			_craftearItem(1);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 26:
		if (!_isInBattle)
			_craftearItem(0);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 27:
		if (!_isInBattle)
			_craftearItem(2);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 28:
		if (!_isInBattle)
			_craftearItem(3);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 29:
		if (!_isInBattle)
			_craftearItem(6);
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 30:
		_verIndicaciones();
	case 100:
		if (!_isInBattle)
			lootEnemies();
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 101:
		if (!_isInBattle)
			throw Dungeon_Exception("Se guardara la partida");
		else
			throw Dungeon_Exception("Estas en pelea");
		break;
	case 102:
		throw Dungeon_Exception("Nueva Partida");
		break;
	case 103:
		_displayHelpText();
	default:
		throw Dungeon_Exception("No es válida la indicacion");
	}
	
}

void Player::_displayHelpText() {
	string s = "----------Comandos----------\n";
	int i = 0;

	for (map<string, short>::iterator map_itr = _indication_list.begin(); map_itr != _indication_list.end(); map_itr++) {
		s += map_itr->first + "\n";
	}

	throw s;

}

void Player::_verIndicaciones() {
	string s = "          -------------------------Indicaciones-------------------------\n";
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
	s += "Es importante lootear a los enemigos, ya que si sales del juego antes de hacerlo se mantendrán muertos y se PERDERAN las cosas que cargan\n";
	throw s;
}

void Player::printMagic() {
	string s;

	s =  "-----Player Magic-----\n";
	s += "\t\t\t\t\t\tCosto\n";
	s += "0 -> Daña a los enemigos un poco\t\t\t   10\n";
	s += "1 -> Daña a los enemigos mucho\t\t\t   20\n";
	s += "2 -> Cura\t\t\t\t\t   10\n";
	s += "3 -> Aumenta el ataque por 5 turnos\t\t\t   15\n";
	s += "4 -> Aumenta el ataque magico por 5 turnos\t\t   20\n";
	s += "5 -> Aumenta la velocidad por 3 turnos\t\t   25\n";
	s += "6 -> Aumenta la velocidad mucho por 3 turnos\t\t   40\n";;
	s += "7 -> Ataque mixto a todos los enemigos\t\t   70\n";

	throw s;
}

void Player::printStatus() {
	string s;
	s = "-----Player Status-----\n";
	cout << "-----Player Status-----" << endl;
	s+="Vida : " + to_string(_life) + "\n";
	s+="Ataque : " + to_string(getAttack()) + "\n";
	s+="Defensa : " + to_string(getDefense()) + "\n";
	s+="Ataque Magico : " + to_string(getMagicAttack()) + "\n";
	s+="Defensa Magica  : " + to_string(getMagicDefense()) + "\n";
	s+="Velocidad : " + to_string(getSpeed()) + "\n";
	s+="Mana : " + to_string(_mana) + "\n";

	throw s;
}

void Player::printItems()
{
	string s;
	s = "-----Player Items----\n";
	s += "Sword: ";
	if (_sword)
		s += _sword->getValues();
	s += "\n";
	s += "Shield: ";
	if (_shield)
		s += _shield->getValues();
	s += "\n";
	for (int i = 0; i < _key_list.size(); i++) 
		s+= "Llave: " + std::to_string(_key_list[i]->getID()) + " \n";

	s += "-----Partes de monstruo-----: \n";
	s += "Tripas : " + to_string(_loot_list[0]) + "\n";
	s += "Colmillos : " + to_string(_loot_list[1]) + "\n";
	s += "Huesos : " + to_string(_loot_list[2]) + "\n";
	s += "Metal : " + to_string(_loot_list[3]) + "\n";
	throw s;


}

/*
@param door: door the player is trying to open
*/
void Player::changeRoom(int door) {
	bool hasKey = false;
	int prevRoom = _current_room->getID();
	for (int i = 0; i < _key_list.size(); i++) {
		if (door == _key_list[i]->getID())
			hasKey = true;
	}
	_current_room = _current_room->getDoor(door, hasKey, _bosses_defeated)->getNextDoor(_current_room);
	_rooms_passed++;
	if (_current_room->generateEnemies(_rooms_passed)) {
		_rooms_passed = 0;
	}
	if (_current_room->hasBoss())
		startBattle();

	throw prevRoom;
}

/*
@return pointer to current Room
*/ 
Room* Player::getCurrentRoom() {
	return _current_room;
}

void Player::grabKey(int n) {
	if (_key_list.size() < 5)
	{
		if (n != -1) {
			_key_list.push_back(_current_room->grabKey(n));
		}
		else {
			_key_list.push_back(_current_room->grabKey());
		}
		throw Dungeon_Exception("Agarraste una llave");
	}
	else {
		throw Dungeon_Exception("No tienes llaves para tirar");
	}
}

void Player::leaveKey(int n) {
	if (n == -1)
	{
		throw Dungeon_Exception("No ingresaste numero de llave");
	}
	else
	{
		for (int i = 0; i < _key_list.size(); i++)
		{
			if (_key_list[i]->getID() == n)
			{
				_current_room->addItem(*_key_list.begin() + i);
				_key_list.erase(_key_list.begin() + i);
				throw Dungeon_Exception("Tiraste la llave");
			}
		}
		throw Dungeon_Exception("No tienes esa llave");
	}
}

void Player::attackBoss(forward_list<Enemy*>* const enemy_list, bool p) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		if ((*i)->isAlive() && (*i)->isBoss()) {
			Boss* b = (Boss*) & *(*i);
			attackAnyone(b, p);
		}
	}
	throw Dungeon_Exception("Aqui no hay un boss");
}

void Player::attackEnemy(forward_list<Enemy*>* const enemy_list, bool p) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		if ((*i)->isAlive()) 
			attackAnyone((*i), p);
	}
}

void Player::attackMinion(forward_list<Enemy*>* const enemy_list, bool p) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		if ((*i)->isAlive() && !(*i)->isBoss())
			attackAnyone((*i), p);
	}
	throw Dungeon_Exception("Aqui no hay minions");
}

template<class T>
void Player::attackAnyone(T* t, bool p) {
	if (p) {
		if (!isAvoidedStrong(_speed, t->getSpeed())) {
			t->setLife(getDamageStrong(getAttack(), t->getAttack()));
		}
		else
			throw Dungeon_Exception("Fallaste el ataque");
	}
	else {
		if (!isAvoidedWeak(_speed, t->getSpeed())) {
			t->setLife(getDamageWeak(getAttack(), t->getAttack()));
		}
		else
			throw Dungeon_Exception("Fallaste el ataque");
	}
}

/*
@param number of spell to use
*/
void Player::_magicAttack(int n) {
	switch (n) {
	case 0:
		if (_mana >= 10) {
			_mana -= 10;
			_magicAttack0(_current_room->getEnemyList());
		}
			
		break;
	case 1:
		if (_mana >= 20) {
			_mana -= 20;
			_magicAttack1(_current_room->getEnemyList());
		}
			
		break;
	case 2:
		if (_mana >= 10) {
			_mana -= 10;
			_magicAttack2();
		}
		break;
	case 3:
		if (_mana >= 15) {
			_mana -= 15;
			_magicAttack3();
		}
		
		break;
	case 4:
		if (_mana >= 20) {
			_mana -= 20;
			_magicAttack4();
		}
		
		break;
	case 5:
		if (_mana >= 25) {
			_mana -= 25;
			_magicAttack5();
		}
		break;
	case 6:
		if (_mana >= 40) {
			_mana -= 40;
			_magicAttack6();
		}
		
		break;
	case 7:
		if (_mana >= 70) {
			_mana -= 70;
			_magicAttack7(_current_room->getEnemyList());
		}
		break;
	default:
		throw Dungeon_Exception("No es un hechizo valido");

	}
	throw Dungeon_Exception("No tienes suficiente mana");
}

void Player::startBattle() {
	_isPlayerTurn = true;
	_isInBattle = true;
	MessageBoxA(_hWnd, "Ha iniciado una batalla", "Batalla", MB_OK);	
}

void Player::endBattle() {
	_isInBattle = false;
	for (int i = 0; i < 8; i++) {
		_magic_list[i] = 0;
	}
	if (_current_room->hasBoss())
		_bosses_defeated++;
	_current_room->setIsLooteable();
	if(_bosses_defeated == 5)
		MessageBoxA(_hWnd, "El juego ha terminado", "Batalla", MB_OK);
	else
		MessageBoxA(_hWnd, "La batalla ha terminado", "Batalla", MB_OK);
}

bool Player::isInBattle() {
	return _isInBattle;
}

bool Player::isTurn() {
	return _isPlayerTurn;
}

void Player::setPlayerTurn(bool n) {
	_isPlayerTurn = n;
}

void Player::setIsInBattle(bool n) {
	_isInBattle = n;
}

void Player::enemyTurn(forward_list<Enemy*>* enemy_list) {
	int r;
	try {
		for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
			srand(time(NULL));
			r = rand() % 3 + 1;
			try {
				if ((*i)->isAlive()) {
					if ((*i)->isBoss()) {
						Boss* b = (Boss*) & *(*i);
						enemyAttack(b, r);
					}
					else
						enemyAttack((*i), r);
				}
			}
			catch (Dungeon_Exception e) {
				string s;
				s = e.what();
				MessageBoxA(_hWnd, s.c_str(), "Ataque de enemigo", MB_OK);
			}
		}
	}
	catch (std::exception e) {
		cout << e.what() << endl;
	}
}

void Player::reduceSpells() {
	_magic_list[3]--;
	_magic_list[4]--;
	_magic_list[5]--;
	_magic_list[6]--;
}

template<class T>
void Player::enemyAttack(T* t, int r) {
	if (r == 1) {
		if (!isAvoidedStrong(t->getSpeed(), _speed)) {
			_life -= getDamageStrong(t->getAttack(), _defense);
			throw Dungeon_Exception("Te han pegado");
		}
	}
	else if (r == 2) {
		if (!isAvoidedWeak(t->getSpeed(), _speed)) {
			_life -= getDamageWeak(t->getAttack(), _defense);
			throw Dungeon_Exception("Te han pegado");
		}
	}
	else {
		_life -= getMagicDamage(t->getMagicAttack(), _magic_defense);
		throw Dungeon_Exception("Te han pegado");
	}
	throw Dungeon_Exception("Esquivaste el ataque");
}

template<class T>
T* Player::grabItem(T* t, int n) {
	T* s;
	s = t;
	if (n == -2) {
		if (t) {
			t = NULL;
			leaveItem(s);
			throw Dungeon_Exception("Has tirado el item");
		}
		else
			throw Dungeon_Exception("No tienes ese item para tirar");
	}
	t = _current_room->getItem(t, n);
	leaveItem(s);
	return t;
}

template<class T>
void Player::leaveItem(T* s) {
	if (s)
		_current_room->addItem(s);
}

int Player::getAttack() {
	int v;
	v = _attack;
	if (_sword)
		v += _sword->getAttack();
	if (_magic_list[3] > 0)
		v += 10;
	v += _bosses_defeated * 5;
	return v;

}

int Player::getDefense() {
	int v;
	v = _defense;
	if (_sword)
		v += _sword->getDefense();
	if (_shield)
		v += _shield->getDefense();
	v += _bosses_defeated * 5;
	return v;
}

int Player::getSpeed() {
	int v;
	v = _speed;
	if (_sword)
		v += _sword->getSpeed();
	if (_shield)
		v += _shield->getSpeed();
	if (_magic_list[5] > 0)
		v += 5;
	if (_magic_list[6] > 0)
		v += 15;
	v += _bosses_defeated * 5;
	return v;
}

int Player::getMagicAttack() {
	int v;
	v = _magic_attack;
	if (_sword)
		v += _sword->getMagicAttack();
	if (_magic_list[4] > 0)
		v += 10;
	v += _bosses_defeated * 5;
	return v;
}

int Player::getMagicDefense() {
	int v;
	v = _magic_defense;
	if (_sword)
		v += _sword->getMagicDefense();
	if (_shield)
		v += _shield->getMagicDefense();
	v += _bosses_defeated * 5;
	return v;
}

void Player::lootEnemies() {
	if (_current_room->isLooteable())
		_current_room->lootEnemies(&_loot_list);
	else
		throw Dungeon_Exception("No se puede lootear en este cuarto");
}

void Player::_magicAttack0(forward_list<Enemy*>* enemy_list) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		try {
			if ((*i)->isAlive()) {
				if ((*i)->isBoss()) {
					Boss* b = (Boss*) & *(*i);
					b->setLife(getMagicDamage(getMagicAttack(), b->getDefense()));
				}
				else {
					(*i)->setLife(getMagicDamage(getMagicAttack(), (*i)->getDefense()));
				}
			}
		}
		catch (Dungeon_Exception e) {
			string s = e.what();

		}
	}
	throw Dungeon_Exception("Heriste a los enemigos");
}

void Player::_magicAttack1(forward_list<Enemy*>* enemy_list) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		try {
			if ((*i)->isAlive()) {
				if ((*i)->isBoss()) {
					Boss* b = (Boss*) & *(*i);
					b->setLife(getMagicDamage(getMagicAttack() * 1.50, b->getDefense()));
				}
				else {
					(*i)->setLife(getMagicDamage(getMagicAttack() * 1.50, (*i)->getDefense()));
				}
			}
		}
		catch (Dungeon_Exception e) {
			string s = e.what();
			if (s != "Has dañado a este enemigo")
				cout << "< " << s << " >" << endl;
		}
	}
	throw Dungeon_Exception("Heriste a los enemigos");
}

void Player::_magicAttack2() {
	_life += (getMagicAttack() / 50) * 40;
	if (_life >= 100)
		_life == 100;
	throw Dungeon_Exception("Te has curado");
}

void Player::_magicAttack3() {
	_loot_list[3] = 6;
}

void Player::_magicAttack4() {
	_loot_list[4] = 6;
}

void Player::_magicAttack5() {
	_loot_list[5] = 4;
}

void Player::_magicAttack6() {
	_loot_list[6] = 4;
}

void Player::_magicAttack7(forward_list<Enemy*>* enemy_list) {
	for (forward_list<Enemy*>::iterator i = enemy_list->begin(); i != enemy_list->end(); i++) {
		try {
			if ((*i)->isAlive()) {
				if ((*i)->isBoss()) {
					Boss* b = (Boss*) & *(*i);
					b->setLife(getMagicDamage((getMagicAttack() + getAttack()) / 2, b->getDefense()));
				}
				else {
					(*i)->setLife(getMagicDamage((getMagicAttack() + getAttack()) / 2, (*i)->getDefense()));
				}
			}
		}
		catch (Dungeon_Exception e) {
			string s = e.what();
			if (s != "Has dañado a este enemigo")
				cout << "< " << s << " >" << endl;
		}
	}
	throw Dungeon_Exception("Heriste a los enemigos");
}
	
void Player::checkCrafteable() {
	string s;
	s = "----- Objetos crafteables -----\n";
	s += "\t\t     Tripas     Colmillos     Huesos     Metal\n";
	s += "Katana III\t       08              09                  09             14\n";
	s += "Espada III\t       02              08                  20             10\n";
	s += "Scimitarra III\t       15              10                  05             10\n";
	s += "Guadaña III\t       14              15                  07             09\n";
	s += "Curacion\t       03              03                  01             00\n";
	s += "Mana\t\t       01              02                  02             01\n";
	s += "Excalibur\t       10              10                  10             20\n";

	throw s;
	
}

void Player::_craftearItem(int num) {
	switch(num) {
		case 0:
			if (_loot_list[0] >= 8 && _loot_list[1] >= 9 && _loot_list[2] >= 9 && _loot_list[3] >= 14) {
				try {
					leaveItem(_sword);
					_sword = NULL;
					_loot_list[0] -= 8;
					_loot_list[1] -= 9;
					_loot_list[2] -= 9;
					_loot_list[3] -= 14;
				}
				catch (...) {

				}
				throw Dungeon_Exception("Crafteaste una Katana III");
			}
			break;
		case 1:
			if (_loot_list[0] >= 2 && _loot_list[1] >= 8 && _loot_list[2] >= 20 && _loot_list[3] >= 10) {
				try {
					leaveItem(_sword);
					_sword = NULL;
					_loot_list[0] -= 2;
					_loot_list[1] -= 8;
					_loot_list[2] -= 20;
					_loot_list[3] -= 10;

				}
				catch (...) {

				}
				throw Dungeon_Exception("Crafteaste una Espada III");
			}
			break;
		case 2:
			if (_loot_list[0] >= 14 && _loot_list[1] >= 15 && _loot_list[2] >= 7 && _loot_list[3] >= 9) {
				try {
					leaveItem(_sword);
					_sword = NULL;
					_loot_list[0] -= 14;
					_loot_list[1] -= 15;
					_loot_list[2] -= 7;
					_loot_list[3] -= 9;
				}
				catch (...) {

				}
				throw Dungeon_Exception("Crafteaste una Guadaña III");
			}
			break;
		case 3:
			if (_loot_list[0] >= 15 && _loot_list[1] >= 10 && _loot_list[2] >= 5 && _loot_list[3] >= 10) {
				if (_sword) {
					leaveItem(_sword);
					_sword = NULL;
					_loot_list[0] -= 15;
					_loot_list[1] -= 10;
					_loot_list[2] -= 5;
					_loot_list[3] -= 10;
				}
				throw Dungeon_Exception("Crafteaste una Scimitarra III");
			}
			break;
		case 4:
			if (_loot_list[0] >= 3 && _loot_list[1] >= 3 && _loot_list[2] >= 1 && _loot_list[3] >= 0) {
				_life += 20;
				if (_life > 100) 
					_life = 100;
				_loot_list[0] -= 3;
				_loot_list[1] -= 3;
				_loot_list[2] -= 1;
				throw Dungeon_Exception("Te curaste");
			}
			break;
		case 5:
			if (_loot_list[0] >= 1 && _loot_list[1] >= 2 && _loot_list[2] >= 2 && _loot_list[3] >= 1) {
				_mana += 20;
				if (_mana > 100)
					_mana = 100;
				_loot_list[0] -= 1;
				_loot_list[1] -= 2;
				_loot_list[2] -= 2;
				_loot_list[3] -= 1;
				throw Dungeon_Exception("Recuperaste mana");
			}
			break;
		case 6:
			if (_loot_list[0] >= 10 && _loot_list[1] >= 10 && _loot_list[2] >= 10 && _loot_list[3] >= 20) {
				try {
					leaveItem(_sword);
					_sword = NULL;
					_loot_list[0] -= 10;
					_loot_list[1] -= 10;
					_loot_list[2] -= 10;
					_loot_list[3] -= 20;
				}
				catch (...) {

				}
				throw Dungeon_Exception("Crafteaste a Excalibur");
			}
			break;
		default:
			throw Dungeon_Exception("Ese no es un numero crafteable");
	}
	throw Dungeon_Exception("No te alcanzan los materiales");
}


void Player::setSword(Sword* s) {
	_sword = s;
}

void Player::setShield(Shield* s) {
	_shield = s;
}

void Player::addKey(Key* k) {
	_key_list.push_back(k);
}

void Player::setValues(PlayerSaver p) {
	_life = p.life;
	_mana = p.mana;
	_rooms_passed = p.rooms_passed;
	_bosses_defeated = p.bosses_defeated;
	for (int i = 0; i < 4; i++) {
		_loot_list[i] = p.loot_list[i];
	}
}

PlayerSaver Player::getPlayerSaver() {
	PlayerSaver p;
	p.room_id = _current_room->getID();
	if (_sword)
		p.sword = _sword->getID();
	else
		p.sword = -1;
	if (_shield)
		p.shield = _shield->getID();
	else
		p.shield = -1;
	for (int i = 0; i < _key_list.size(); i++) {
		p.key_list.push_back(_key_list[i]->getID());
	}
	p.life = _life;
	p.rooms_passed = _rooms_passed;
	for (int i = 0; i < 4; i++) {
		p.loot_list[i] = _loot_list[i];
	}
	p.mana = _mana;
	p.bosses_defeated = _bosses_defeated;
	return p;
}

short Player::getBossesDefeated() {
	return _bosses_defeated;
}

void Player::restartPlayer(Room* r) {
	_current_room = r;
	_life = 100;
	_attack = 10;
	_defense = 10;
	_speed = 20;
	_magic_attack = 10;
	_magic_defense = 10;
	_sword = NULL;
	_shield = NULL;
	_key_list.empty();
	_magic_list[0] = 0;
	_magic_list[1] = 0;
	_magic_list[2] = 0;
	_magic_list[3] = 0;
	_magic_list[4] = 0;
	_magic_list[5] = 0;
	_magic_list[6] = 0;
	_magic_list[7] = 0;
	_loot_list[0] = 0;
	_loot_list[1] = 0;
	_loot_list[2] = 0;
	_loot_list[3] = 0;
	_bosses_defeated = 0;
	_rooms_passed = 0;
	_isInBattle = false;
}