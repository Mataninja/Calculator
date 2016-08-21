#include "Calculator.h"

using namespace std;
int main(){
	cout << "If you want to exit, enter (n)!" << endl;
	cout << "Input expression :" ;
	string data="";
	getline(cin, data);
	Calculator* calc = new Calculator();
	while (data != "n"){
		try{
			calc->setData(data);
			cout.setf(ios::fixed,ios::floatfield); // 2 digits after the decimal;
			cout.precision(2);
			cout << "Result: " << calc->getRez() << endl;

		}
		catch (string* str){
			cout <<*str << endl;
		}
		cout << "Input expression :";
		getline(cin, data);
	}
	delete calc;
	return 0;
}