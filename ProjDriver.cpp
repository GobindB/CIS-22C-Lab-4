/*
Alexander Zhang
Yasuhiro Yamada
22C Manish Goel

This program demonstrates the Calculator class which can turn an infix equation into its
postfix and prefix forms.

There is extensive input validation which catches all the specified cases, ensuring that the
calculator can calculate the correct value.

Flexibility in the parenthesis has been implemented. Parenthesis are not ambiguous with/without
spaces, so they are implemented in a way which reflects their consistency.

The thorough validation process works. Any valid equation works here as long as the operator
is in the list specified, and there are no negatives, as per instructions. If the equation is
unambiguous, it can be validated.

The infix to postfix uses a stack of operators and a queue to parse through the equation.
The infix to prefix uses the method taught in class: reverse infix, find postfix, reverse postfix
Therefore, this part can reuse the code from the infix to postfix function

The user can loop this program as long as they want. They simply press Enter afterwards to
continue.
If the user wishes to end, type anything then press Enter.

*/
#include <iostream>
#include <string>
#include "Calculator.h" //includes Stack and Queue ADT
using namespace std;

void getInfixPrompt(Calculator &);

void clarityLine();





int main()
{
	Calculator calc;

	char choice = '\n'; //choice = newline

	while (choice == '\n') // while choice == newline
	{

		getInfixPrompt(calc); //get the equation and convert them

							  //output the equation in infix, postfix, and prefix form
		cout << "Infix: " << calc.getInfixEquation() << endl;
		cout << "Postfix: " << calc.getPostfixEquation() << endl;
		cout << "Prefix: " << calc.getPrefixEquation() << endl;
		clarityLine();

		//allows user to repeat
		cout << "Only press Enter to repeat. Type anything else, then enter, to end. ";
		cin.get(choice);
		clarityLine();
	}

	system("pause");
	return 0;
}



/* outputs a line for visual clarity
Pre:
Post:
Return:
*/
void clarityLine()
{
	cout << string(30, '=') << endl;
}


/* gets the equation from the user. checks if valid.
Pre: &calc - Calculator object by reference.
Post: Equation is entered into the calculator object, which stores it
Return:
*/
void getInfixPrompt(Calculator &calc)
{
	string eqn; //holds the user input

				//checks if the input is invalid. Will be invalid first run to start the loop
	while (!calc.checkValidEqn(eqn))
	{
		cout << "Enter an Infix equation (No Negative Numbers)." << endl;
		cout << "(Separate Operands and Operators by a space): ";
		getline(cin, eqn);

		if (!calc.checkValidEqn(eqn)) //if invalid, report to user. will repeat loop
		{
			cout << "Invalid Equation!" << endl;
		}
	} //exits once equation is valid.
	  //sets the equation in the calculator object, which immediately finds the post and prefix form
	calc.setEquation(eqn);
}
