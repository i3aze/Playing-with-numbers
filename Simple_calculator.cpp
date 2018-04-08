//This is a simple calculator made by Blazhe Jakimovski aka i3aze
//All the program does is takes input through getline, and make numbers and signs
//from the string and stores them in vector of doubles. The signes are also stored
//as doubles(chars converted into ascii value) for practicality reasons.
//Than with iteration of the vector it makes the calculations and changes the values
//in the vector acording to the mathematical expression rules.
//The calculator uses brackets and parentheses, and alo has functions for 
//calculating factorial and exponent. Also, the calculator can take negative numbers
//if the number altogether with the negative sign '-' is wraped in brackets

#include "iostream"
#include "vector"
#include "string"
#include "exception"

void fill_vectors(std::string s, std::vector<double> &num);				//Function for pushing back elements in the vector
double factorial(int fac_num);								//Function with algorithm for calculating factorial
double exponent(double a, int n);						        //Function with algorithm for calculating exponent of a given number
void calculate_factorial(std::vector<double> &num);			    		//Function for calculating factorial
bool check_decimals(std::string s_n);							//Function for checking decimals. The calculator takes up to two decimal numbers
bool check_decimals_zero(std::string s_n);				        	//Function for checking if the number has zero decimals
void calculate_exponent(std::vector<double> &num);			    		//Function for calculaing exponent
void multiply_and_divide(std::vector<double> &num);				     	//Function for calculating multiplication and division
void add_and_subtract(std::vector<double> &num);				      	//Function for calculaing adition and subtraction
double negative_number(double n);								          //Function for creating negative numbers
void calculate_brackets(std::vector<double> &cal_brack, std::vector<double> &num, double &temp_brack);	  //This and the next function calculate everything in a brackets
void brackets(std::vector<double> &num, std::vector<double> &cal_brack, double &temp_brack);
void calculate_parentheses(std::vector<double> &cal_paren, std::vector<double> &num, double &temp_par);   //This and the next function calculate everything in a parentheses
void parentheses(std::vector<double> &num, std::vector<double> &cal_paren, double &temp_par);

int main()
try{
	std::string expression;
	std::vector<double> numbers;
	std::vector<double> calculate_par;
	std::vector<double> calculate_brack;
	double temp_par = 0;
	double temp_brack = 0;
	double number = 0;

	std::cout << "THIS IS A CALCULATOR BY i3aze" << std::endl;
	std::cout << "The calculator uses + - * / ! ^ (), {} and = for calculations" << std::endl;
	std::cout << "Enter 'quit' for exit from the calculator" << "\n" << std::endl;
	std::cout << "Please enter expression:" << std::endl;

	while (std::getline(std::cin, expression) && expression != "quit" && !expression.empty())	//Prompt the user to enter expression, insert 'quit' to exit from the program
	{
		fill_vectors(expression, numbers);					 //Fill the vector with the string expression

		bool b = false;
		for (unsigned i = 0; i < numbers.size(); i++)				 //Iterate the vector
		{
			if (numbers.at(i) == 40.001 || numbers.at(i) == 41.001)		 //If there are brackets (40 and 41 are ascii representation of '(', ')' resprectively). I add three decimal numbers on every sign so I can distinct them from the numbers
			{
				b = true;
			}
			if (b && numbers.at(i) == 123.001)				 //Error check if there are parentheses inside the brackets
			{
				throw("Bad expression!");
			}
		}
		
		if (b)									 //b = true means there are brackets
		{
			brackets(numbers, calculate_brack, temp_brack);			 //Call the functions to calculate everything inside the brackets
		}

		bool p = false;
		for (unsigned i = 0; i < numbers.size(); i++)				 //Same procedure with the parentheses
		{
			if (numbers.at(i) == 123.001 || numbers.at(i) == 125.001)
			{
				p = true;
			}
		}
		if (p)
		{
			parentheses(numbers, calculate_par, temp_par);
		}

		calculate_factorial(numbers);						//When we are done with the brackets and the parentheses if there were any, now we have mathematical expression without them
		calculate_exponent(numbers);						//I am calling the other functions for calculating
		multiply_and_divide(numbers);
		add_and_subtract(numbers);

		std::cout << "=";							//Print the result
		for (unsigned i = 0; i < numbers.size(); i++)
		{
			if (numbers.at(i) != 61.001)
			{
				std::cout << numbers.at(i) << " ";
			}
		}
		numbers.clear();
		std::cout << "\n\n";
		std::cout << "Try again:" << std::endl;
	}

	system("pause");
    return 0;
}

catch (const char *msg)
{
	std::cerr << "Exception thrown: " << msg << std::endl;
	system("pause");
	return 1;
}
catch (...)
{
	std::cerr << "Oops, unknown exception!" << std::endl;
	system("pause");
	return 2;
}

//What this function does is basically iterates through the string
//and composes doubles out of the numbers and numbers with three decimals
//out of the signs and puts them in the numbers vector using reference
void fill_vectors(std::string s, std::vector<double> &num)
{
	std::vector<char> signs{ '.', '+', '-', '*', '/', '!', '(', ')', '{', '}', '=', '^' };
	std::string::size_type ss_type;
	std::string s_number;
	
	for (char &c : s)									 //Iterate the string expression
	{
		bool valid_sign = false;
		if (isalpha(c))								        //Don't take letters
		{
			throw("Bad input!");
		}
		else if (ispunct(c))						      		//If it is puctuation
		{
			for (unsigned i = 0; i < signs.size(); i++)				//Check if the char is contained in the signs vector
			{
				if (c == signs.at(i))
				{
					valid_sign = true;
				}
			}
			if (!valid_sign)						        //If not, throw an exception
			{
				throw("Bad input!");
			}
		}
		if (ispunct(c) && c != '.')					  		//Check for decimals in the numbers
		{
			if (check_decimals(s_number))
			{
				throw ("Cannot input more than two decimals!");
			}
			if (!s_number.empty())					    		//If the string has numbers in it
			{
				double number = std::stod(s_number, &ss_type);			//Convert it to double
				num.push_back(number);				    		//And put it in the numbers vector
				s_number.clear();					        //Clear the string
				num.push_back(c - ('\0') + 0.001);				//Put in the sign converted as decimal with three decimal numbers
			}
			else
			{
				num.push_back(c - ('\0') + 0.001);				//If the string is full, just put in the sign
			}
		}
		else if (isdigit(c) || c == '.')						//If it's digit and is not a decimal sign
		{
			s_number += c;							       	//add the char to the s_number string
		}
	}
}

//This function counts the decimals of the elements in the numbers vector
//If there are three or more it checks if there are other numbers except zeros in the decimal
//The calculator takes three decimals only for the signs represented as ascii
//In every sign the decimal is .001
//It is just my way of distinction mathematical signs from numbers
bool check_decimals(std::string s_n)
{
	std::vector<char> temp;
	int counter_zeros = 0;
	for (std::string::reverse_iterator rit = s_n.rbegin(); rit != s_n.rend(); rit++)
	{
		bool has_zero;
		if (*rit != '.')
		{
			counter_zeros++;
			temp.push_back(*rit);
		}
		else if (*rit == '.')
		{
			for (unsigned i = 0; i < temp.size(); i++)
			{
				if (temp.at(i) != '0')
				{
					has_zero = true;
					break;
				}
				else
				{
					has_zero = false;
				}
			}
			if (counter_zeros >= 3)
			{
				if (has_zero)
				{
					return true;
				}
				else if (!has_zero)
				{
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

//This function checks if the number is decimal number
//This is needed for factorial and exponent calculation
//The calculator does not calculate factorial of a decimal number and 
//does not take decimal number as exponent
bool check_decimals_zero(std::string s_n)
{
	std::vector<char> temp;
	for (std::string::reverse_iterator rit = s_n.rbegin(); rit != s_n.rend(); rit++)
	{
		if (*rit != '.')
		{
			temp.push_back(*rit);
		}
		else if (*rit == '.')
		{
			for (unsigned i = 0; i < temp.size(); i++)
			{
				if (temp.at(i) != '0')
				{
					return true;
				}
			}
		}
	}
	return false;
}

double factorial(int fac_num)		  	//Factorial algorithm
{
	int x = 1;
	for (int i = 1; i <= fac_num; i++)
	{
		x *= i;
	}
	return x;
}

double exponent(double a, int n)		//Exponent algorithm
{
	double temp = a;
	for (int i = 1; i < n; i++)
	{
		temp *= a;
	}
	return temp;
}

//This function searches the ascii representation of '*' or '/' in the vector
//and calculates acordingly the next and the previous elements
//After the calculation it erases the elements in the vector (the two numbers and the sign)
//and on the position of the sign it assigns the result
//It also makes error checking for invalid input and division with zero
void multiply_and_divide(std::vector<double> &num)
{
	bool has_multiply_or_divide = true;
	while (has_multiply_or_divide)
	{
		double temp = 0;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 42.001 || num.at(i) == 47.001)
			{
				if (num.at(i - 1) == 40.001 || num.at(i - 1) == 123.001 || num.at(i - 1) == 42.001 || num.at(i - 1) == 47.001 ||
					num.at(i - 1) == 45.001 || num.at(i - 1) == 43.001 || num.at(i - 1) == 94.001)
				{
					throw("Bad expression!");
				}
				if (num.at(i) == 42.001)
				{
					temp = num.at(i - 1) * num.at(i + 1);
					num.erase(num.begin() + (i - 1), num.begin() + (i + 1));
					num.at(i - 1) = temp;
				}
				else if (num.at(i) == 47.001)
				{
					if (num.at(i + 1) == '\0' || num.at(i - 1) == '\0')
					{
						throw ("Cannot divide by zero");
					}
					temp = num.at(i - 1) / num.at(i + 1);
					num.erase(num.begin() + (i - 1), num.begin() + (i + 1));
					num.at(i - 1) = temp;
				}
			}
		}
		bool has_multiply_or_divide_two = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 42.001 || num.at(i) == 47.001)
			{
				has_multiply_or_divide_two = true;
			}
		}
		if (has_multiply_or_divide_two)
		{
			has_multiply_or_divide = true;
		}
		else if (!has_multiply_or_divide_two)
		{
			has_multiply_or_divide = false;
		}
	}
}

//This function does the same as the previous, it just does addition and subtraction instead of multiplication and division
void add_and_subtract(std::vector<double> &num)
{
	bool add_or_subtract = true;
	while (add_or_subtract)
	{
		double temp = 0;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 43.001 || num.at(i) == 45.001)
			{
				if (num.at(i - 1) == 40.001 || num.at(i - 1) == 123.001 || num.at(i - 1) == 42.001 || num.at(i - 1) == 47.001 ||
					num.at(i - 1) == 45.001 || num.at(i - 1) == 43.001 || num.at(i - 1) == 94.001)
				{
					throw("Bad expression!");
				}
				if (num.at(i) == 43.001)
				{
					temp = num.at(i - 1) + num.at(i + 1);
					num.erase(num.begin() + (i - 1), num.begin() + (i + 1));
					num.at(i - 1) = temp;
					break;
				}
				else if (num.at(i) == 45.001)
				{
					temp = num.at(i - 1) - num.at(i + 1);
					num.erase(num.begin() + (i - 1), num.begin() + (i + 1));
					num.at(i - 1) = temp;
					break;
				}
			}
		}
		bool add_or_subtract_two = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 43.001 || num.at(i) == 45.001)
			{
				add_or_subtract_two = true;
			}
		}
		if (add_or_subtract_two)
		{
			add_or_subtract = true;
		}
		else if (!add_or_subtract_two)
		{
			add_or_subtract = false;
		}
	}
}

//This function does the same, it just searches for '!' in the vector and
//uses the factorial algorithm for the calculation
//Also, does error checking for factorial of decimal number
//and if the element before the '!' in the vector is number
void calculate_factorial(std::vector<double> &num)
{
	bool has_factorial = true;
	while (has_factorial)
	{
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 33.001)
			{
				if (check_decimals(std::to_string(num.at(i - 1))))
				{
					throw("Bad expression!");
				}
				if (check_decimals_zero(std::to_string(num.at(i - 1))))
				{
					throw("Cannot calculate factorial of decimal number!");
				}
				num.at(i - 1) = factorial(num.at(i - 1));
				num.erase(num.begin() + i, num.begin() + (i + 1));
			}
			bool has_factorial_two = false;
			for (unsigned i = 0; i < num.size(); i++)
			{
				if (num.at(i) == 33.001)
				{
					has_factorial_two = true;
				}
			}
			if (has_factorial_two)
			{
				has_factorial = true;
			}
			else if (!has_factorial_two)
			{
				has_factorial = false;
			}
		}
	}
}

//This function does the same as the previous one, it just searches for '^' in the vector
//and does the calculation and error checking accordingly
void calculate_exponent(std::vector<double> &num)
{
	bool has_exponent = true;
	while (has_exponent)
	{
		for (unsigned i = 0; i < num.size(); i++)
		{
			double temp = 0;
			if (num.at(i) == 94.001)
			{
				if (num.at(i - 1) == 45.001 || num.at(i - 1) == 43.001 || num.at(i - 1) == 42.001 || num.at(i - 1) == 47.001 ||
					num.at(i - 1) == 61.001 || num.at(i - 1) == 123.001 || num.at(i - 1) == 40.001)
				{
					throw("Bad expression!");
				}
				if (check_decimals_zero(std::to_string(num.at(i + 1))))
				{
					throw("Cannot calculate decimal exponent!");
				}
				temp = exponent(num.at(i - 1), num.at(i + 1));
				num.erase(num.begin() + (i - 1), num.begin() + (i + 1));
				num.at(i - 1) = temp;
			}
			bool has_exponent_two = false;
			for (unsigned i = 0; i < num.size(); i++)
			{
				if (num.at(i) == 94.001)
				{
					has_exponent_two = true;
				}
			}
			if (has_exponent_two)
			{
				has_exponent = true;
			}
			else if (!has_exponent_two)
			{
				has_exponent = false;
			}
		}
	}
}

//This function is an algorithm for turning positive number into negative
double negative_number(double n)
{
	double x = n;
	for (int i = 1; i <= 2; i++)
	{
		x -= n;
	}
	return x;
}

//This function although is somewhat larger, what it basically does is error checking
//if the brackets does not match, checks if there is negative number e.g. (-2) and calls the
//function(algorithm) for calculating negative number and if there is no errors
//it calls the calculate_brackets function for actual calulation of the elements in the brackets
void brackets(std::vector<double> &num, std::vector<double> &cal_brack, double &temp_brack)
{
	bool calculate = true;
	bool nn = false;
	while (calculate)
	{
		bool small = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 40.001)
			{
				if (num.at(i) == 40.001 && i > 0)
				{
					if (!check_decimals(std::to_string(num.at(i - 1))) || num.at(i - 1) == 33.001)
					{
						throw("Bad expression!");
					}
					if (num.at(i + 1) == 45.001)
					{
						double temp_negative = 0;
						temp_negative = negative_number(num.at(i + 2));
						num.erase(num.begin() + i, num.begin() + (i + 3));
						num.at(i) = temp_negative;
						nn = true;
					}
				}
				if (!small)
				{
					small = true;
				}
				else
				{
					throw("Brackets does not match!");
				}
			}
			if (num.at(i) == 41.001)
			{
				if (!check_decimals(std::to_string(num.at(i + 1))))
				{
					throw("Bad expression!");
				}
				if (small)
				{
					small = false;
				}
				else
				{
					throw("Brackets does not match!");
				}
			}
			if (nn)
			{
				small = false;
			}
			if (small && num.at(i) != 40.001)
			{
				cal_brack.push_back(num.at(i));
			}
		}
		if (small)
		{
			throw("Brackets does not match!");
		}
		if (!nn)
		{
			calculate_brackets(cal_brack, num, temp_brack);
		}
		bool calculate_two = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 40.001)
			{
				calculate_two = true;
			}
		}
		if (calculate_two)
		{
			calculate = true;
		}
		else if (!calculate_two)
		{
			calculate = false;
		}
	}
}

//This function calculates everything between the brackets
void calculate_brackets(std::vector<double> &cal_brack, std::vector<double> &num, double &temp_brack)
{
	calculate_factorial(cal_brack);
	calculate_exponent(cal_brack);
	multiply_and_divide(cal_brack);
	add_and_subtract(cal_brack);

	for (unsigned i = 0; i < cal_brack.size(); i++)
	{
		temp_brack = cal_brack.at(i);
	}
	int a, b;
	bool brack = false;
	for (unsigned i = 0; i < num.size(); i++)
	{
		if (num.at(i) == 40.001)
		{
			brack = true;
			num.at(i) = temp_brack;
			a = i;
		}
		else if (num.at(i) == 41.001)
		{
			b = i;
		}
	}
	if (brack)
	{
		num.erase(num.begin() + a, num.begin() + b);
		num.at(a) = temp_brack;
	}
}

//This function checks for errors when there are parentheses in the expression
//If everything is ok (no errors) it calls the calculate_parentheses function
void parentheses(std::vector<double> &num, std::vector<double> &cal_paren, double &temp_par)
{
	bool calculate = true;
	while (calculate)
	{
		bool large = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 123.001)
			{
				if (num.at(i) == 123.001 && i > 0)
				{
					if (!check_decimals(std::to_string(num.at(i - 1))) || num.at(i - 1) == 33.001)
					{
						throw("Bad expression!");
					}
				}
				if (!large)
				{
					large = true;
				}
				else
				{
					throw("Parentheses does not match!");
				}
			}
			if (num.at(i) == 125.001)
			{
				if (!check_decimals(std::to_string(num.at(i + 1))))
				{
					throw("Bad expression!");
				}
				if (large)
				{
					large = false;
				}
				else
				{
					throw("Parentheses does not match!");
				}
			}
			if (large && num.at(i) != 123.001)
			{
				cal_paren.push_back(num.at(i));
			}
		}
		if (large)
		{
			throw("Parentheses does not match!");
		}
		calculate_parentheses(cal_paren, num, temp_par);
		bool calculate_two = false;
		for (unsigned i = 0; i < num.size(); i++)
		{
			if (num.at(i) == 123.001)
			{
				calculate_two = true;
			}
		}
		if (calculate_two)
		{
			calculate = true;
		}
		else if (!calculate_two)
		{
			calculate = false;
		}
	}
}

//This function does the actual calculation of the elements in parentheses
void calculate_parentheses(std::vector<double> &cal_paren, std::vector<double> &num, double &temp_par)
{
	calculate_factorial(cal_paren);
	calculate_exponent(cal_paren);
	multiply_and_divide(cal_paren);
	add_and_subtract(cal_paren);

	for (unsigned i = 0; i < cal_paren.size(); i++)
	{
		temp_par = cal_paren.at(i);
	}
	int a, b;
	bool parenth = false;
	for (unsigned i = 0; i < num.size(); i++)
	{
		if (num.at(i) == 123.001)
		{
			parenth = true;
			num.at(i) = temp_par;
			a = i;
		}
		else if (num.at(i) == 125.001)
		{
			b = i;
		}
	}
	if (parenth)
	{
		num.erase(num.begin() + a, num.begin() + b);
		num.at(a) = temp_par;
	}
}
