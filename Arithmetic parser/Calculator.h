#pragma once
#include<stack>
#include<vector>
#include"lexeme.h"
#include"Operand.h"
#include"Operator.h"
using std::stack;
using std::vector;


class Calculator
{
public:
	static double calculate(vector<Lexeme*> lexemes);//calculates expression value using stacks
private:
	static bool push_allowed(Operator op, stack<double> d_stack, stack<char> c_stack);
};

