#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
//The calculator program. ;
//For calculation used the Postfix Polish notation. ;
//More details about the algorithm https://habrahabr.ru/post/100869/; 
//Author Ramis Valiev. 2016 ;
class Calculator
{
private:
	string data;
	//The function returns the Postfix Polish notation as a vector;
	vector<string> getPPN(); 
	bool isCorrectSimbol(char sim);
	bool isOperator(char sim);
	bool isNumber(char sim);
	vector<string> getSplitString();
public:
	void setData(string data);
	Calculator(string data);
	Calculator();
	//  The result obtained from the Polish notation;
	float getRez();
	~Calculator();
};
#endif

