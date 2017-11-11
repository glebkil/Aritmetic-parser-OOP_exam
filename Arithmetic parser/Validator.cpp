#include "Validator.h"

const char Validator::valid_symbols[] = { '.','(',')','+','-','/','*','^',' ','0','1','2','3','4','5','6','7','8','9'};
const char Validator::valid_operators[] = { '+','-','/','*','^' };

void Validator::prevalidation(string source_expression)
{
	try
	{
		is_not_empty(source_expression);
		symbols_validation(source_expression);
		no_repeat(source_expression);
		opr_in_the_begining_or_in_the_end(source_expression);
		incorrect_parenthesis_usage(source_expression);
	}
	catch (invalid_expresion_exception obj)
	{
		throw invalid_expresion_exception(obj.get_error_text());
	}
}

void Validator::postvalidation(vector<Lexeme*> parsed_expression)
{
	try
	{
		no_operator_btw_num_and_opening_parenthesis(parsed_expression);
		no_expression_btw_parenthesis(parsed_expression);
		no_expression_btw_opening_parenthesis_and_opr(parsed_expression);
		no_expression_btw_opr_and_closing_parenthesis(parsed_expression);
		no_binary_opr_near_oprd(parsed_expression);
	}
	catch (invalid_expresion_exception obj)
	{
		throw invalid_expresion_exception(obj.get_error_text());
	}
}


void Validator::symbols_validation(string source_expression)
{
	for (auto iter = source_expression.begin(); iter < source_expression.end(); ++iter)
	{
		if (find(std::begin(valid_symbols), std::end(valid_symbols), *iter) == std::end(valid_symbols))
		{
			throw invalid_expresion_exception("There are invalid symbols in your input!");
		}
	}
}

void Validator::no_repeat(string source_expression)
{
	bool prev_is_opr = false;
	for (auto iter = source_expression.begin(); iter < source_expression.end(); ++iter)
	{
		if (is_operator(*iter) || *iter == '.')
		{
			if (prev_is_opr)
			{
				throw invalid_expresion_exception("There are some repetitive operators in your input!");
			}
			prev_is_opr = true;
		}
		else
		{
			prev_is_opr = false;
		}
	}
}

void Validator::is_not_empty(string source_expression)
{
	if (source_expression == "")
	{
		throw invalid_expresion_exception("Your input is empty =(");
	}
}

void Validator::opr_in_the_begining_or_in_the_end(string source_expression)
{
	if (is_operator(*(source_expression.begin())) || *(source_expression.begin()) == '.')
	{
		throw invalid_expresion_exception("Operation usage in the begining of the expression is inapropriate");
	}
	if (is_operator(*(source_expression.end() - 1)) || *(source_expression.begin()) == '.')
	{
		throw invalid_expresion_exception("Operation usage in the end of the expression is inapropriate");
	}
}

void Validator::incorrect_parenthesis_usage(string source_expression)
{
	stack<char> st;
	for (auto iter = source_expression.begin(); iter < source_expression.end(); ++iter)
	{
		if (*iter == '(')
		{
			st.push(*iter);
		}
		if (*iter == ')')
		{
			if (st.size() > 0)
			{
				st.pop();
			}
			else
			{
				throw invalid_expresion_exception("Incorrect parentesis usage!");
			}
		}
	}
	if (st.size() != 0)
	{
		throw invalid_expresion_exception("Incorrect parentesis usage!");
	}
}


void Validator::no_operator_btw_num_and_opening_parenthesis(vector<Lexeme*> parsed_expression)
{
	for (auto iter = parsed_expression.begin(); iter < parsed_expression.end(); ++iter)
	{
		if (is_operand(*iter))
		{
			++iter;
			if (dynamic_cast<Operator*>(*iter)->get_value() == '(')
			{
				throw invalid_expresion_exception("Looks like you have a '(' right after one of the operands");
			}
			else
			{
				--iter;
			}
		}
		else
		{
			continue;
		}
	}
}

void Validator::no_expression_btw_parenthesis(vector<Lexeme*> parsed_expression)
{
	bool prev_is_opening = false;
	for (auto iter = parsed_expression.begin(); iter < parsed_expression.end(); ++iter)
	{
		if (is_operand(*iter))
		{
			prev_is_opening = false;
		}
		else
		{
			if (dynamic_cast<Operator*>(*iter)->get_value() == ')')
			{		
				if (prev_is_opening)
				{
					throw invalid_expresion_exception("There is no expression between your parenthesis!");
				}
			}
			if (dynamic_cast<Operator*>(*iter)->get_value() == '(')
			{
				prev_is_opening = true;
			}
		}
	}
}

void Validator::no_expression_btw_opening_parenthesis_and_opr(vector<Lexeme*> parsed_expression)
{
	bool prev_is_opening = false;
	for (auto iter = parsed_expression.begin(); iter < parsed_expression.end(); ++iter)
	{
		if (is_operand(*iter))
		{
			prev_is_opening = false;
		}
		else
		{
			if (is_operator(dynamic_cast<Operator*>(*iter)->get_value()))
			{
				if (prev_is_opening)
				{
					throw invalid_expresion_exception("Looks like you have an invalid operator usage before operand");
				}
			}
			if (dynamic_cast<Operator*>(*iter)->get_value() == '(')
			{
				prev_is_opening = true;
			}
		}
	}
}

void Validator::no_expression_btw_opr_and_closing_parenthesis(vector<Lexeme*> parsed_expression)
{
	bool prev_is_opr = false;
	for (auto iter = parsed_expression.begin(); iter < parsed_expression.end(); ++iter)
	{
		if (is_operand(*iter))
		{
			prev_is_opr = false;
		}
		else
		{
			if (dynamic_cast<Operator*>(*iter)->get_value() == ')')
			{
				if (prev_is_opr)
				{
					throw invalid_expresion_exception("Looks like you have an invalid operator usage after operand");
				}
			}
			if (is_operator(dynamic_cast<Operator*>(*iter)->get_value()))
			{
				prev_is_opr = true;
			}
		}
	}
}

void Validator::no_binary_opr_near_oprd(vector<Lexeme*> parsed_expression)
{
	bool after_is_opr = false;
	bool before_is_opr = false;
	for (auto iter = parsed_expression.begin(); iter < parsed_expression.end(); ++iter)
	{
		if (is_operand(*iter))
		{
			if (iter < parsed_expression.end() - 1)
			{
				++iter;
				if (is_operator(*iter))
				{
					after_is_opr = true;
				}
				--iter;
			}
			if (iter > parsed_expression.begin())
			{
				--iter;
				if (is_operator(*iter))
				{
					before_is_opr = true;
				}
				++iter;
			}
			if (!(after_is_opr || before_is_opr))
			{
				throw invalid_expresion_exception("One of your operands don't have binary operator near it!");
			}
		}
	}
}


bool Validator::is_operator(char s)
{
	if (find(std::begin(valid_operators), std::end(valid_operators), s) == std::end(valid_operators))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Validator::is_operand(Lexeme* lexeme)
{
	return typeid(*lexeme) == typeid(Operand);
}

bool Validator::is_operator_or_bracket(Lexeme* lexeme)
{
	return typeid(*lexeme) == typeid(Operator);
}

bool Validator::is_operator(Lexeme * lexeme)
{
	return is_operator(dynamic_cast<Operator*>(lexeme)->get_value());
}


