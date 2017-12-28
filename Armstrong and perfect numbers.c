// This program checks if a number is armstrong or perfect

#include <stdio.h>
#include <cmath>
#include <iostream>

int armstrong(int num);
int perfect(int num);


int main()
{
	int a, b, c;

	printf("Enter number to check if its armstrong\n");
	scanf_s("%i", &a);

	b = armstrong(a);	// pass the value of a in the paramether of the function and assign the function to b
	c = perfect(a);		// pass the value of a in the paramether of the function and assign the function to c

#pragma region printing

	if (b == a)		// if the return value (the sum) of the function is equals to the entered value...
	{
		printf("The number %i is armstrong\n", a);
	}
	else if (b != a)        // if its not...
	{
		printf("The number %i is not armstrong\n", a);
	}

	if (c == a)		// if the return value (the sum) of the function is equals to the entered value...
	{
		printf("The number %i is perfect\n", a);
	}
	else if (c != a)        // if its not...
	{
		printf("The number %i is not perfect\n", a);
	}

#pragma endregion

	system("pause");
	return 0;
}

int armstrong(int num)
{
	int arr[100];
	int i = 0;
	int count = 0;
	int sum = 0;

	while (num > 0)
	{
		int digit = num % 10;		// get the remainder of the number
		arr[i] = digit;				// put it in the array
		i++;						// increase the position in the array
		num /= 10;					// divide and assign the value of the number
	}

	for (int j = 0; j <= i - 1; j++)	// check how many single numbers are there in the whole number 
	{
		count++;
	}

	for (int j = 0; j <= i - 1; j++)	// rase every one to the n-th of numbers in the array and sum them up
	{
		sum += pow(arr[j], count);
	}

	return sum;			// return the sum of them
}

int perfect(int num)
{
	int arr1[100];
	int j = 0;
	int sum1 = 0;

	for (int i = 1; i <= num - 1; i++)		// check if the number is divisor to num, if it is put it in array
	{
		if (num % i == 0)
		{
			arr1[j] = i;
			j++;
		}
	}

	for (int i = 0; i <= j - 1; i++)	// sum all the numbers in the array
	{
		sum1 += arr1[i];
	}

	return sum1;						// return the sum
}
