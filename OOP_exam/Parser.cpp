#include "Parser.h"

vector<Lexeme*> Parser::parse(string input_expression)
{
	vector<Lexeme*> lexemes;

	input_expression.erase(std::remove_if
	(input_expression.begin(), input_expression.end(), [](char s)->bool {return s == ' '; }),
		input_expression.end()); //erasing all spaces from input

	lexemes.push_back(new Operator('('));
	//lexemes.push_back(new Operand(0));

	for (auto iter = input_expression.begin(); iter < input_expression.end(); ++iter)
	{
		if (isdigit(*iter))
		{
			string temp_str;
			for (;;)
			{
				if (isdigit(*iter) || *iter == '.')
				{
					temp_str.push_back(*iter);
					iter++;
				}
				else
				{
					break;
				}
				if (iter < input_expression.end())
				{
					continue;
				}
				else
				{
					break;
				}
			}
			iter--;
			lexemes.push_back(new Operand(stod(temp_str)));
			//it's unsafe. If conversion fails 0 is returned so the final result would be incorrect
		}
		else
		{
			lexemes.push_back(new Operator(*iter));
		}
	}
	lexemes.push_back(new Operator(')'));

	return lexemes;
}

