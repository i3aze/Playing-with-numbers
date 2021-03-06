// This is a simple program for converting roman numerals into arabic.
// It is designed for studying purpose only and it has some flaws e.g. if you enter MDIIV
// you'll get 1505. MDIIV is not a valid roman number! MDV is!
// Nevertheless, I had fun designing it and despite its flaws it works fine.

//------------------------------------------------------------------------------------------
// This is the header file

#include "std_lib_facilities.h"

class Roman_nums				// Define class that will deal with input of a string
{						// in the form of a roman numeral and output arabic number
private:
	string a;

public:
	Roman_nums();				// Default constructor
	Roman_nums(string aa);			// Contructor of the string into an object
	~Roman_nums();				// Default destructor
	vector<int> myvec;			// Vector that will hold the converted numbers
	bool is_roman(char c);			// Function for checking of the entered number is roman
	int to_num(char s);			// Function for converting roman digits into arabic
	void to_vector();			// Function that inputs the converted numbers in the vector
	void make_nums();			// Function for making nums from digits
	void to_arabic();			// Function that prints the numbers as a final number
	void input();				// Function for input
};

//------------------------------------------------------------------------------------------
// This is the source file

#include <Roman_numerals_header.h>
Roman_nums::Roman_nums() {};				// Constructors and destructors definition
Roman_nums::Roman_nums(string aa)
	: a(aa)
{}
Roman_nums::~Roman_nums() {};
vector<int> myvec;
bool Roman_nums::is_roman(char c)			// Check if the character is roman number
{
	if (c != 'I' || c != 'V' || c != 'X' || c != 'L' || c != 'C' || c != 'D' || c != 'M')
	{
		return false;
	}
	else
		return true;
}
int Roman_nums::to_num(char s)				// Convert the roman numbers into arabic numbers
{
	int a = 0;
	if (s == 'I')
	{
		a = 1;
	}
	else if (s == 'V')
	{
		a = 5;
	}
	else if (s == 'X')
	{
		a = 10;
	}
	else if (s == 'L')
	{
		a = 50;
	}
	else if (s == 'C')
	{
		a = 100;
	}
	else if (s == 'D')
	{
		a = 500;
	}
	else if (s == 'M')
	{
		a = 1000;
	}
	else
		error("Bad input!");
	return a;
}
void Roman_nums::to_vector()				// Iterate the string for roman numbers and put them in the vector
{
	int num = 0;
	for (int i = 0; i < a.size(); i++)
	{
		if (is_roman(a[i])) error("Not a roman number!");
		num = to_num(a[i]);
		myvec.push_back(num);
	}
	make_nums();
}
void Roman_nums::make_nums()				// Contruct the numbers 4, 9 and so on...
{
	for (int i = 1; i < myvec.size(); i++)
	{
		if (myvec[i] == 5 && (myvec[i - 1]) == 1)
		{
			myvec[i] = 4;
			myvec[i - 1] = 0;
		}
		if (myvec[i] == 10 && (myvec[i - 1]) == 1)
		{
			myvec[i] = 9;
			myvec[i - 1] = 0;
		}
		if (myvec[i] == 50 && (myvec[i - 1]) == 10)
		{
			myvec[i] = 40;
			myvec[i - 1] = 0;
		}
		if (myvec[i] == 100 && (myvec[i - 1]) == 10)
		{
			myvec[i] = 90;
			myvec[i - 1] = 0;
		}
		if (myvec[i] == 500 && (myvec[i - 1]) == 100)
		{
			myvec[i] = 400;
			myvec[i - 1] = 0;
		}
		if (myvec[i] == 1000 && (myvec[i - 1]) == 100)
		{
			myvec[i] = 900;
			myvec[i - 1] = 0;
		}
	}
	for (int i = 1; i < myvec.size(); i++)		// Check for bad input like IC or XD
	{
		if (myvec[i] == 10 && myvec[i - 1] == 5) error("Bad input!");
		if (myvec[i] == 50 && myvec[i - 1] == 1 || myvec[i] == 50 && myvec[i - 1] == 5) error("Bad input!");
		if (myvec[i] == 100 && myvec[i - 1] == 50 || myvec[i] == 100 && myvec[i - 1] == 1 || myvec[i] == 100 && myvec[i - 1] == 5) error("Bad input!");
		if (myvec[i] == 500 && myvec[i - 1] == 1 || myvec[i] == 500 && myvec[i - 1] == 50 || myvec[i] == 500 && myvec[i - 1] == 10 || myvec[i] == 500 && myvec[i - 1] == 5) error("Bad input!");
		if (myvec[i] == 1000 && myvec[i - 1] == 500 || myvec[i] == 1000 && myvec[i - 1] == 1 || myvec[i] == 1000 && myvec[i - 1] == 50 || myvec[i] == 1000 && myvec[i - 1] == 10 || myvec[i] == 1000 && myvec[i - 1] == 5) error("Bad input!");
	}
	to_arabic();
}
void Roman_nums::to_arabic()						// Iterate the vector and sum up the numbers in it
{
	int result = 0;
	for (int f = 0; f < myvec.size(); f++)
	{
		result += myvec[f];
	}
	cout << "The number is: " << result << endl;	// Print the result
	myvec.clear();							// Clear the vector to be prepaired for another input
}

void Roman_nums::input()						// Input roman number from the keyboard
{
	cout << "Enter roman number for conversion, enter '~' to quit" << endl;
	while (cin >> a && a != "~")
	{
		to_vector();
		cout << "Enter roman number for conversion again" << endl;
	}
}

//------------------------------------------------------------------------------------------
// This is the main file

#include <Roman_numerals_header.h>

int main()
try
{
	Roman_nums roman;				// Initialize a class object
	roman.input();					// Call the input function

	keep_window_open();
	return 0;
}
catch (exception& e)
{
	cerr << "Exception: " << e.what() << endl;
	keep_window_open();
	return 2;
}
catch (...)
{
	cerr << "Oops, unknown exception" << endl;
	keep_window_open();
	return 1;
}
