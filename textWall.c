#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "ledMatrix.h"

//Helper functions for error handling
bool correctString(char *s)
{
  for(int i = 0; i < strlen(s); i++) {
    if(s[i] == ' ')
      s[i] = '[';
    else if(!isalpha(s[i])) {
      printf("ERROR: INPUT STRING MUST ONLY CONTAIN LETTERS AND SPACES\n");
      return false;
    }
    else
      s[i] = toupper(s[i]);
  }

  return true;
}

bool isnum(char *s)
{
  for(int i = 0; i < strlen(s); i++)
    if(!isdigit(s[i]))
      return 0;

  return 1;
}

//Begin main method
int main(int argc, char *argv[])
{
  //Check if enough arguments have been passed
  if(argc != 3) {
    printf("ERROR: Must have 2 arguments\n");
    printf("TRY: ./matrix.o <MESSAGE> <FRAMES PER SCROLL>\n");
    return -1;
  }

  //Generate input string
  char *sequence = argv[1];
  if(!correctString(sequence))
    return -1;

  //Check if second parameter is valid
  if(!isnum(argv[2])) {
    printf("ERROR: SECOND ARGUMENT MUST BE INTEGER\n");
    return -1;
  }

  //Continue with program
  int nFrames = atoi(argv[2]);
  int screen[SCREEN_HEIGHT][SCREEN_WIDTH];
  Point **ledMatrix = setupMatrix();

  wiringPiSetup();
  initializePins();

  while(1) {
    textScroll(screen, ledMatrix, sequence, nFrames);
  }

  return 0;
}