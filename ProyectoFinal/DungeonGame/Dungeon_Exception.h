#pragma once
#include <iostream>
#include <exception>
class Dungeon_Exception : public std::exception
{
public:
	std::string m_msg;

	Dungeon_Exception(const std::string msg) : m_msg(msg) {}

	~Dungeon_Exception(){}

	virtual const char* what() const throw()
	{
		return m_msg.c_str();
	}
};

