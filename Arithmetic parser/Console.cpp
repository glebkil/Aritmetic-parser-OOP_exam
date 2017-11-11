#include "Console.h"
#include <stdlib.h>

void Console::run()
{
	bool repeat = false;
	do
	{
		repeat = input();
	} while (repeat);
}

bool Console::input()
{
	string input = "";
	cout << "Input a string: ";
	if (cin.peek() == '\n')
	{
		cin.get();
	}
	getline(cin, input);
	Expression expression(input);
	try
	{			
		cout << expression.get_source_expression() << " = "
			<< expression.prevalidation().parse().postvalidation().calculate().get_result() << endl;
		return input_or_exit();
	}
	catch (invalid_expresion_exception obj)
	{
		cout << obj.get_error_text() << endl;
		return input_or_exit();
	}
}
	

bool Console::input_or_exit()
{
	cout << endl;

	cout << "Enter 1 to input again" << endl;
	cout << "Enter 2 to exit" << endl;

	switch ((int)input_number())
	{
	case 1:
		return true;
		break;
	case 2:
		return false;
		break;
	default:
		input_or_exit();
		break;
	}
}

double Console::input_number()
{
	char str[MAX_STRING_LENGTH];
	//gets_s(str, MAX_STRING_LENGTH - 1);
	cin >> str;
	double result = atof(str);
	if (result == NULL)
	{
		cout << "Incorrect input." << endl;
		input_number();
	}
	else
	{
		return result;
	}
}

