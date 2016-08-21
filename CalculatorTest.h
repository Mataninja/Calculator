#include <cxxtest/TestSuite.h>

#include "Calculator.h"

class CalculatorTest : public CxxTest::TestSuite
{
private:
	Calculator calc;
public:
	void testGetRez(){
		TS_TRACE("Starting Calculator::getRez test");
		calc.setData("-1+5-3");
		TS_ASSERT_EQUALS(calc.getRez(), 1);
		calc.setData("-10+(8*2.5)-(3/1,5)");
		TS_ASSERT_EQUALS(calc.getRez(), 8);
		calc.setData("1+(2*(2.5+2.5+(3-2)))-(3/1.5)");
		TS_ASSERT_EQUALS(calc.getRez(),11);
		try{
			calc.setData("1.1+2.1+abc");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. Invalid characters abc.");
		}
		try{
			calc.setData("((1-1)");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. Extra left parentheses.");
		}
		try{
			calc.setData("(1-1))");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. Extra right parenthesis.");
		}
		try{
			calc.setData("(1-+1)");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. The extra operators.");
		}
		try{
			calc.setData("(1 2 3 4 + 5)");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. Not enough operators.");
		}
		try{
			calc.setData("1/(1-1)");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Divide by zero");
		}
		try{
			calc.setData("1-1..,0");
			calc.getRez();
		}
		catch (string* e){
			TS_ASSERT_EQUALS(*e, "Incorrect data. The extra characters in the number.");
		}
		TS_TRACE("Finishing Calculator::getRez test");
	}
};