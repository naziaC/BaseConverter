
/*============================================================================
Name : base2Base.c
Author : Nazia Chowdhury (with template from Ferrie's assignment 5 document and taken from Katrina Poulin's  tutorial)
Version : 1.0
Copyright : Your copyright notice
Description : A "C" command line program with three arguments:
 : 1. A string corresponding to a number in a base from [2,36]
 : 2. An integer corresponding to the base of the first argument
 : 3. An integer corresponding to the base of the converted output.
============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
* Function Prototypes Here
*/

int string2Int(char *inString, int inBase, int *decValue);
char *int2String(int decValue, int outBase);
int char2Int(char inChar);
void reverseString(char* str);

/**
* Definitions Here
*/

#define MAXBUF 34 										// Longest output string is 34 characters (sign) and '\0'
#define MINBASE 2 										// Base ranges
#define MAXBASE 36										// numbers + letters(?)
#define true 1 											// Useful to define true and false
#define false !true										// false is defined to be not true = because booleans don't exist = can be replaced by 0


/**
* Globals Here
*/

static char *LUT = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 			// Lookup table for conversions

/**
* The main routine parses input, calls conversion routines and prints the results.
* Some of the code below is taken from Katrina Poulin's tutorials
* main method
*/

int main(int argc, char *argv[]) {									// always the same, for memory...
		int inBase, outBase, decValue;


	char input[strlen(argv[1])];								// creating a string of length of input
	strcpy(input, argv[1]);										// copying string

	inBase = atoi(argv[2]);										// converts string to integer with atoi
	outBase = atoi(argv[3]);

	if (argc != 4){												// when there is too many or too little arguments
		printf("Usage: base2Base [input-string][input-base][output-base]\n");
	} else if ((inBase < MINBASE || inBase > MAXBASE) && (outBase < MINBASE || outBase > MAXBASE)){		// when both input and output base are not within [2,36]
		printf("The input base must be between [2,36].\n");
		printf("The output base must be between [2,36].\n");
	} else if ((inBase < MINBASE) || (inBase > MAXBASE)){										// when both input base is not within [2,36]
		printf("The input base must be between [2,36].\n");
	} else if ((outBase < MINBASE) || (outBase > MAXBASE)){										// when both output base is not within [2,36]
		printf("The output base must be between [2,36].\n");
	} else if ((inBase >= MINBASE || inBase <= MAXBASE) && (outBase >= MINBASE || outBase <= MAXBASE)){

		// if the input is in the correct input base
		for (int i = 0; i<= strlen(input); i++){
			for (int j = 0; j<= inBase; j++){

				if (char2Int(input[i]) < inBase){
					string2Int(input,inBase, &decValue);
					printf("%s has a value of %d as a decimal integer.\n", input, decValue);
					printf("%s has an equivalent representation of %s in Base-%d.\n", input, int2String(decValue, outBase), outBase);
					printf("Program terminated.\n");
					return -1;

				} else {			// if the input is not in the correct input base
					printf("%s does not correspond to a valid integer in Base-%d.\n", input,inBase);
					return -1;
				}
			}
		}
	}
  }



/**
* int string2Int(char *inString, int inBase, int *decValue);
* inString - input string representing number in inBase
* inBase - base corresponding to number above
* decValue - pointer to location in which to write return value
* returns - 0 no error, 1 invalid representation for specified base
* Taken from assignment 5 handout and from Katrina Poulin's tutorial
*/

int string2Int(char *inString, int inBase, int *decValue) {

	int sum=0;										// initialize
	int power=1;
	int sign=1;

	int length = strlen(inString);						// length of argv 1

	for (int i = length - 1; i >= 0; i--){

		char current = toupper(inString[i]);						// Get current character
		if (i == 0 && current == '-'){					// if first character AND character is '-'
			sign = -1;									// setting sign to -1
		} else {

		int index = char2Int(current);					// convert to integer index

		if (index == -1){
			// error...
			printf("There is an error.");
			return -1;

		} else {
		sum = sum + index*power;
		power = power*inBase;
				}
			}
		}

		sum = sum*sign;
		*decValue = sum;								// going to address and changing result at location referenced by decValue
		return 0;

}


/**

* int char2Int(char inChar)
* inChar - character to search for in LUT
* returns - the index if found, otherwise -1
* Taken from Katrina Poulin's tutorials
*/


int char2Int(char inChar) {

	char* value = strchr(LUT, inChar);		// finding character in LUT and returns substring starting from that character
	int index = (int)(value - LUT);			// get the index of the character in LUT
	return index;

}

/**
* char *int2String(int decValue, int outBase);
* decValue - decimal value to encode as a string in target base
* outBase - the target base to convert to
* Taken from the assignment 5 handout
*/

char *int2String(int decValue, int outBase) {

	char *buffer = (char *)malloc(MAXBUF*sizeof(char));				   // allocating space for buffer

	int arg = abs(decValue);
	int index=0;

	while (arg > 0) {
			int current = arg%outBase;
			arg = arg/outBase;
			buffer[index++] = LUT[current];								// convert index to character
		}

		if (decValue < 0) buffer[index++] = '-';    					// Add in sign
		buffer[index] = '\0';											// Add end-of-string terminator

		reverseString(buffer);											// reverses buffer
		return buffer;

		free(buffer);													// deallocating buffer
}

/**
 * This function reverses a string
 * str - represents the string that will be reversed
 * Inspired by what Katrina Poulin explained from the tutorial
 */

void reverseString(char* str){

	char temp;
	int length = strlen(str);

	for (int i = 0; i <length/2; i++){
		temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;


	}

}
