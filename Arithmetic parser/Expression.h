#pragma once
#include<string>
#include<vector>
#include"lexeme.h"
#include"Validator.h"
#include"Calculator.h"
#include"Parser.h"
using std::string;
using std::vector;

class Expression
{
public:
	Expression(string source_expression);

	Expression& parse();
	Expression& prevalidation();
	Expression& postvalidation();
	Expression& calculate();
	double get_result(){ return result; }
	string get_source_expression(){ return source_expression; }
private:
	string source_expression;
	vector<Lexeme*> parsed_expression;
	double result;
};

