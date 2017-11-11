#pragma once
#include<iostream>
#include<string>
#include"Expression.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
#define MAX_STRING_LENGTH 128

class Console
{
public:
	static void run();
private:
	static bool input();
	static bool input_or_exit();
	static double input_number();
};

