#include <wiringPi.h>
#include <stdlib.h>
#include "alphabet.h"

//Necessary defines to abstract the wiringPi numbers
#define SCREEN_WIDTH 5
#define SCREEN_HEIGHT 5
const int cols[] = {13, 10, 11, 22, 21};
const int rows[] = {30, 31, 8, 9, 7};

typedef struct {
  int row;
  int col;
}Point;

//Setup a matrix to correspond with the LEDs
Point **setupMatrix() {
  Point **p = malloc(sizeof(Point*) * SCREEN_WIDTH);

  for(int i = 0; i < SCREEN_WIDTH; i++) {
    p[i] = malloc(sizeof(Point) * SCREEN_HEIGHT);
    for(int k = 0; k < SCREEN_HEIGHT; k++) {
      Point temp;
      temp.row = rows[i];
      temp.col = cols[k];
      p[i][k] = temp;
    }
  }
  return p;
}

//Provide functions to make working with the LED Matrix easier
void initializePins()
{
  for(int i = 0; i < SCREEN_WIDTH; i++) {
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}
void plot(Point p, int state)
{
  digitalWrite(p.row, state);
  digitalWrite(p.col, state);
}
void writeToScreen(const int data[SCREEN_WIDTH][SCREEN_HEIGHT], Point **matrix)
{
  for(int i = 0; i < SCREEN_WIDTH; i++)
    for(int k = 0; k < SCREEN_HEIGHT; k++) {
      if(data[i][k])
        plot(matrix[i][k], HIGH);
      delay(0.5);
      plot(matrix[i][k], LOW);
    }
}

//Function for writing text to the screen
void textScroll(int screen[SCREEN_HEIGHT][SCREEN_WIDTH], Point **ledMatrix, char *sequence, int nFrames)
{
  for(int letter = 0; letter < strlen(sequence); letter++) {
    for(int offset = 0; offset < SCREEN_WIDTH+1; offset++) {
      for(int i = 0; i < SCREEN_WIDTH; i++)
        for(int k = 0; k < SCREEN_HEIGHT; k++) {
          if(i+offset < SCREEN_WIDTH)
            screen[k][i] = alphabet[sequence[letter]-'A'][k][i+offset];
          else if(i+offset > SCREEN_WIDTH)
            screen[k][i] = alphabet[sequence[(letter+1)%(strlen(sequence))]-'A'][k][(i+offset)%(SCREEN_WIDTH+1)];
          else
            screen[k][i] = 0;
        }
      for(int frame = 0; frame < nFrames; frame++)
        writeToScreen(screen, ledMatrix);
    }
  }
}