#pragma once
#include <string>
#include <iostream>

using std::string;
using std::to_string;

class Item
{
protected:
	int _id;
	string _text;

public:
	Item();
	Item(int, std::string);
	int getID();
	std::string getText();
	virtual string getValues() ;
};

