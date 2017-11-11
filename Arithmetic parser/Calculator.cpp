#include "Calculator.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

bool Calculator::push_allowed(Operator op, stack<double> d_stack, stack<char> c_stack)
{
	if (op.get_value() == ')')
	{
		return false;
	}
	if (c_stack.size() == 0)
	{
		return true;
	}
	if (c_stack.top() == '(')
	{
		return true;
	}

	int top_el_pr;
	int passed_el_pr;
	auto top_el = c_stack.top();
	auto passed_el = op.get_value();

	if (top_el == ')' || top_el == '(')
	{
		top_el_pr = 1;
	}
	else if (top_el == '^')
	{
		top_el_pr = 2;
	}
	else if (top_el == '*' || top_el == '/')
	{
		top_el_pr = 3;
	}
	else
	{
		top_el_pr = 4;
	}

	if (passed_el == ')' || passed_el == '(')
	{
		passed_el_pr = 1;
	}
	else if (passed_el == '^')
	{
		passed_el_pr = 2;
	}
	else if (passed_el == '*' || passed_el == '/')
	{
		passed_el_pr = 3;
	}
	else
	{
		passed_el_pr = 4;
	}

	return top_el_pr >= passed_el_pr;
}

double calc_pair(double left_opd, char opr, double right_opd)
{
	switch (opr)
	{
	case '+':
		return left_opd + right_opd;
	case '-':
		return left_opd - right_opd;
	case '*':
		return left_opd * right_opd;
	case '/':
		return left_opd / right_opd;
	case '^':
		return pow(left_opd, right_opd);
	}
}

double Calculator::calculate(vector<Lexeme*> lexemes)
{
	stack<double> d_stack;
	stack<char> c_stack;

	for (auto iter = lexemes.begin(); iter < lexemes.end(); ++iter)
	{
		Operator* t = dynamic_cast<Operator*>(*iter);
		if (t != 0)
		{
			if (push_allowed(*t, d_stack, c_stack))
			{
				c_stack.push(t->get_value());
			}
			else
			{

				bool pop_needed = false;
				if (t->get_value() == ')')
				{
					pop_needed = true;
				}
				while (c_stack.top() != '(')
				{
					auto right_opd = d_stack.top();
					d_stack.pop();
					auto left_opd = d_stack.top();
					d_stack.pop();
					auto opr = c_stack.top();
					c_stack.pop();
					d_stack.push(calc_pair(left_opd, opr, right_opd));
				}

				if (pop_needed)
				{
					c_stack.pop(); //to pop a '('
				}
				else
				{
					iter--;
				}
			}
		}
		else
		{
			Operand* t = dynamic_cast<Operand*>(*iter);
			d_stack.push(t->get_value());
		}
	}

	//cout << "d_stack size before return " << d_stack.size() << endl;
	//cout << "c_stack size before return " << c_stack.size() << endl;
	return d_stack.top();
}