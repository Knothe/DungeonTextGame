#include "Item.h"

Item::Item()
{
	_id = 0;
	_text = "";
}

/*
@param id: item id
@param text: text displayed when finding the item
*/
Item::Item(int id, std::string text) : _id(id), _text(text){}

/*
@return item id
*/
int Item::getID()
{
	return _id;
}

/*
@return item text
*/
std::string Item::getText()
{
	return _text;
}

string Item::getValues()
{
	return _text;
}