#pragma once
#include <string>

class invalid_expresion_exception{
	std::string error_text;
public:
	invalid_expresion_exception(std::string text) : error_text(text) {}
	std::string get_error_text() { return error_text;  }
};