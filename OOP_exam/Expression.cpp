#include "Expression.h"

Expression::Expression(string source_expression) : result(0)
{
	this->source_expression = source_expression;
}

Expression & Expression::parse()
{
	parsed_expression = Parser::parse(source_expression);
	return *this;
}

Expression & Expression::prevalidation()
{
	try
	{
		Validator::prevalidation(source_expression);
		return *this;
	}
	catch (invalid_expresion_exception obj)
	{
		throw invalid_expresion_exception(obj.get_error_text());
		return *this;
	}
	
}

Expression & Expression::postvalidation()
{
	try
	{
		Validator::postvalidation(parsed_expression);
		return *this;
	}
	catch (invalid_expresion_exception obj)
	{
		throw invalid_expresion_exception(obj.get_error_text());
		return *this;
	}
}

Expression & Expression::calculate()
{
	result = Calculator::calculate(parsed_expression);
	return *this;
}
