#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>

#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct charVector charVector;
struct charVector {
	char *buffer;
	int size;
	int lastPlaceInString;
	int cursorPosition;
	charVector *prevInput;
	charVector *nextInput;
};

typedef struct {
	charVector *mostRecentUserInput;
	charVector *leastRecentUserInput;
	charVector *userHistoryIterator;
	int size;
} vectorVector;

typedef struct {
	char **args;
	int actualSize;
	int size;
} commandMatrix;

typedef struct {
	commandMatrix *commands;
	int actualSize;
	int size;
} executionMatrix;

/* 
 * Gets userInput, stores the input in history, and handles the special characters
 * backspace, delete, and arrow keys. Returns userInput as well as user's input
 * history on a linefeed.
*/
void getAndDisplayUserInput (charVector **userInput, vectorVector *historyUserInput);

/* 
 * Parses user's input by spaces and pipe symbols. Returns an array containing
 * the first command (i.e. executionArray.commands[i].args[0]) followed by its
 * arguments if any (i.e. executionArray.commands[i].args[1..n]). Commands and 
 * their arguments are placed by their position relative to the last pipe
 * operator (i.e. command-zero and args-for-command-zero are placed in 
 * executionArray.commands[0], command-one and args-for-command-one which
 * were directly preceeded by a pipe operator are placed in 
 * executionArray.commands[1])
*/
void parseInput (char *bufferCopy, executionMatrix *executionArray);

/*
 * Runs the processes provided by the user according to a properly formatted 
 * executionArray (the final position in the arguments array must be NULL).
*/
void runTheProcesses (executionMatrix *executionArray, vectorVector *historyUserInput);

#endif /* COMMANDS_H */
