#include "Calculator.h"

Calculator::Calculator(string data):data(data)
{}
Calculator::Calculator(){}
Calculator::~Calculator()
{
}

void Calculator::setData(string data){
	this->data = data;
}

bool Calculator::isOperator(char sim){
	switch (sim)
	{
	case '+':
	case '-':
	case '/':
	case '*':
		return true;
	}
	return false;
}

bool Calculator::isNumber(char sim){
	string temp = "0123456789";
	for (int i = 0; i < temp.length(); i++){
		if (temp[i] == sim) return true;
	}
	return false;
}

bool Calculator::isCorrectSimbol(char sim){
	if (isOperator(sim) || isNumber(sim)) return true;
	switch (sim)
	{
	case '(':
	case ')':
	case ',':
	case '.':
		return true;
	}
	return false;
}
//a string of the form "A+B*  C/ F" converting to vector {A,+,*,C,/,F};
vector<string> Calculator::getSplitString(){
	vector<string> splitStr;
	string correctStr = "";
	int punctFlag = 0;
	// a string of the form "A+B*  C/ F" bring to  "A + B * C / F" ;
	for (int i = 0; i < data.length(); i++){
		//Viewing the incorrect characters;
		if (!isCorrectSimbol(data[i]) && data[i]!=' '){
			string excepStr = "";
			while (!isCorrectSimbol(data[i]) && i<data.length()){
				excepStr += data[i];
				i++;
			}
			throw new string("Incorrect data. Invalid characters "+excepStr+".");  // Throw an exception if found invalid characters;
		}
		if (isOperator(data[i]) || data[i] == ')' || data[i] == '('){ 
			correctStr = correctStr + " " + data[i] + " ";
			punctFlag = 0;
			continue;
		}
		if (data[i] == '.' || data[i]==','){
			punctFlag++;
			// Processing if you set the number in view .d or ,d and their translation in 0,d ; (2+ .2) => (2+ 0.2) ;
			if (i == 0 || data[i - 1] == ' ' || isOperator(data[i - 1]) || data[i-1]=='(' || data[i-1]==')') correctStr += '0';
			// Error processing when the number of a few commas or dots. Examples 2..3 ;   3,3.4;
			if (punctFlag >= 2)throw new string("Incorrect data. The extra characters in the number.");
			correctStr += '.';
			continue;
		}
		correctStr += data[i];
	}
	// a string of the form "A + B * C / F" converting to vector splitStr;
	istringstream str(correctStr);
	string String;
	while (str >> String) splitStr.push_back(String);
	return splitStr;
}
//The function returns the Postfix Polish notation as a vector;
vector<string> Calculator::getPPN(){
	stack<string> temp;
	vector<string> dataSplit;
	vector<string> results;
	try{
		dataSplit = getSplitString();
	}
	catch (string* excep){
		throw excep; //Throw the exception above;
	}
	for (int i = 0; i < dataSplit.size(); i++){
		char sim = dataSplit[i][0];
		if (sim == '-' && (i == 0 || dataSplit[i - 1][0] == '(')) results.push_back("0");
		if (isNumber(sim)){
			results.push_back(dataSplit[i]);
			continue;
		}
		if (isOperator(sim)){
			if (sim == '+' || sim=='-'){
				while (!temp.empty() && !(temp.top()[0] == '(')){
					results.push_back(temp.top());
					temp.pop();
				}
				temp.push(dataSplit[i]);
			}
			if (sim == '*' || sim == '/'){
				while (!temp.empty() && (temp.top()[0] == '*' || temp.top()[0] == '/')){
					results.push_back(temp.top());
					temp.pop();
				}
				temp.push(dataSplit[i]);
			}
			continue;	
		}
		if (sim == '('){
			temp.push(dataSplit[i]);
			continue;
		}
		if (sim == ')'){
			while (!temp.empty() && !(temp.top()[0] == '(')){
				results.push_back(temp.top());
				temp.pop();
			}
			if (temp.empty()) throw new string("Incorrect data. Extra right parenthesis.");
			if (temp.top()[0] == '(') temp.pop();
			continue;
		}
		
	}
	while (!temp.empty() && temp.top()[0] != '('){
		results.push_back(temp.top());
		temp.pop();
	}
	if (!temp.empty() && temp.top()[0] == '(') throw new string("Incorrect data. Extra left parentheses.");
	return results;
}
// The result obtained from the Polish notation;
float Calculator::getRez(){
	vector<string> dataPPN = getPPN();
	stack<float> rez;
	if (dataPPN.size() == 0)return 0;
	for (int i = 0; i < dataPPN.size(); i++){
		if (isNumber(dataPPN[i][0])){
			rez.push((float)stof(dataPPN[i]));
			continue;
		}
		if (isOperator(dataPPN[i][0])){
			float number1;
			float number2;
			number2 = rez.top();
			rez.pop();
			if (rez.empty())throw new string("Incorrect data. The extra operators."); 
			number1 = rez.top();
			rez.pop();
			switch (dataPPN[i][0])
			{
				case '+':{
							 rez.push(number1 + number2);
						 break;
				}
				case '-':{
							 rez.push(number1 - number2);
						 break;
				}
				case '*':{
							 rez.push(number1 * number2);
						 break;
				}
				case '/':{
							 if (number2 == 0)throw new string("Divide by zero");
							 rez.push(number1 / number2);
						 break;
				}
			}
		}
	}
	if (rez.size() >= 2) throw new string("Incorrect data. Not enough operators.");
	return rez.top();
}