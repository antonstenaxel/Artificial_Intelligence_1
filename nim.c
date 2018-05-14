#include <stdio.h>
#include <stdlib.h>

#define MAX 1
#define MIN -1

#define INFINITY 9999999

int minmaxValue(int state, int turn); /* forward declaration: mutual recursion */

int minmaxValue(int state, int turn) {
  int move, minmax = turn *INFINITY;
  /* terminal state ? */
  if (state == 1) {
    return (turn * 1); /* Max wins if min is in a terminal state */
  } 
  /* non-terminal state */  
  for (move = 1; move <= 3; move++) {
    if (state - move > 0) { /* legal move */
      int m = minmaxValue(state - move, -turn);
      if (((turn == 1) && (m < minmax)) || ((turn == -1) && (m > minmax)) ) minmax = m;
    }
  }
  return minmax;
}

int minimaxDecision(int state, int turn) {
  int move, bestmove, max, min;
  if (turn == MAX) {
    max = -INFINITY;
    for (move = 1; move <= 3; move++) {
      if (state - move > 0) { /* legal move */
        int m = minmaxValue(state - move, MAX);
        if (m > max) {
          max = m;
          bestmove = move;
        }
      }
    }
    return bestmove;
  }
  /* turn == MIN */
  min = INFINITY;
  for (move = 1; move <= 3; move++) {
    if (state - move > 0) { /* legal move */
      int m = minmaxValue(state - move, MIN);
      if (m < min) {
        min = m;
        bestmove = move;
      }
    }
  }
  return bestmove;
}

void playNim(int state) {
  int turn = 1;
  while (state != 1) {
    int action = minimaxDecision(state, turn);
    printf("%d: %s takes %d\n", state, 
           (turn==MAX ? "Max" : "Min"), action);
    state = state - action;
    turn *= -1;
  }
  printf("1: %s looses\n", (turn==MAX ? "Max" : "Min"));
}

int main(int argc, char *argv[]) {
  if ((argc != 2) || (atoi(argv[1]) < 3)) {
    fprintf(stderr, "Usage: %s <number of sticks>, where ", argv[0]);
    fprintf(stderr, "<number of sticks> must be at least 3!\n");
    return -1;
  }

  playNim(atoi(argv[1]));

  return 0;
}
