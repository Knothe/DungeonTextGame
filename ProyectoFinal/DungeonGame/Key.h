#pragma once
#include "Item.h"

class Key : public Item
{
private:
public:
	Key(int id, std::string text) : Item(id, text) {}
	string getValues() override;
};

