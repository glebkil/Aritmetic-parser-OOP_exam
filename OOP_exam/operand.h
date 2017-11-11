#pragma once
#include"lexeme.h"

class Operand : public Lexeme {
	double value;
public:
	Operand(double value) : value(value) {}
	/*void set_value(double value)
	{
		this->value = value;
	}*/
	double get_value()
	{
		return value;
	}

};