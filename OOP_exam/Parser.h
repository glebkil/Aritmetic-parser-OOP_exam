#pragma once
#include<string>
#include<vector>
#include"lexeme.h"
#include"Operand.h"
#include"Operator.h"
#include<algorithm>
#include <locale>
using std::isdigit;
using std::vector;
using std::string;
//so many includes and usings... is there any more clear way to do it?

class Parser {
public:
	static vector<Lexeme*> parse(string input_expression);
};

