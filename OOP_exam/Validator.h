#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include <algorithm>
#include"invalid_expresion_exception.h"
#include"lexeme.h"
#include"Operand.h"
#include"Operator.h"
using std::vector;
using std::string;
using std::stack;
using std::find;
using std::cout;
using std::cin;
using std::endl;

class Validator {
public:
	static void prevalidation(string source_expression);
	static void postvalidation(vector<Lexeme*> parsed_expression);

private:
	const static char valid_symbols[];
	const static char valid_operators[];

	//pre checkers below
	static void symbols_validation(string source_expression);
	static void no_repeat(string source_expression);
	static void is_not_empty(string source_expression);
	static void opr_in_the_begining_or_in_the_end(string source_expression);
	static void incorrect_parenthesis_usage(string source_expression);

	//post checkers below
	static void no_operator_btw_num_and_opening_parenthesis(vector<Lexeme*> parsed_expression);
	static void no_expression_btw_parenthesis(vector<Lexeme*> parsed_expression);
	static void no_expression_btw_opening_parenthesis_and_opr(vector<Lexeme*> parsed_expression);
	static void no_expression_btw_opr_and_closing_parenthesis(vector<Lexeme*> parsed_expression);
	static void no_binary_opr_near_oprd(vector<Lexeme*> parsed_expression);

	//utility methods
	static bool is_operator(char s);
	//char Validator::get_char(Lexeme* lexeme);
	static bool is_operand(Lexeme* lexeme);
	static bool is_operator_or_bracket(Lexeme* lexeme);
	static bool is_operator(Lexeme* lexeme);
};

