#pragma once
#include"lexeme.h"

class Operator : public Lexeme {
	char value;
public:
	Operator(char value) : value(value) {}
	/*void set_value(char value)
	{
		this->value = value;
	}*/
	char get_value()
	{
		return value;
	}
};