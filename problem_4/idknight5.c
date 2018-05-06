#include <stdio.h>
#include <stdlib.h>

#define N 500   /* N times N chessboard */

int actions[8][2] = {  /* knight moves */
  {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1,-2}, {1,2}, {2, -1}, {2, 1}
};
int costToPath[N][N];
int estimatedCostToGoal[N][N];
unsigned long statesVisited = 0;

int isValidLocation(int x, int y) {
  return (0<=x && x < N && 0<= y && y < N);
}

void initialize(int row, int col, int rowGoal, int columnGoal) {
  int r, c, x, y;
  for (r=0; r < N; r++) {
    for (c=0; c < N; c++) {
      costToPath[r][c] = 999999; /* represents infinity */
      x = abs(c-columnGoal);
      y = abs(r-rowGoal);
      estimatedCostToGoal[r][c] = (x+y)/3; /*manhattan distance divided by three */
    }
  }
  costToPath[row][col] = 0; 
}

int knightAstar(int row, int column, int rowGoal, int columnGoal) {
  int act, rNow, cNow, costMIN = 99999, costGuess;
  statesVisited++; 
  for (act=0; act < 8; act++) {
    int r = row + actions[act][0];
    int c = column + actions[act][1]; 
    /* the location has to be valid & pick the minimum */
    if(isValidLocation(r, c)){
      /*update steps to path, if the path has not been visited yet, or not in the steps before */
      if(costToPath[r][c] > costToPath[row][column] +1){
        costToPath[r][c] = costToPath[row][column] +1;
      } 

      /*costguess */
      costGuess = estimatedCostToGoal[r][c] + costToPath[r][c] ;

      /* picks the minimum cost out of the choices */
      if(costGuess < costMIN){
	costMIN = costGuess;
	rNow = r;
	cNow = c;
      }
    }
  } 
  /*update previous step*/
  estimatedCostToGoal[row][column] = costMIN +1; 
  /* the end */
  if(rNow == rowGoal && cNow == columnGoal){
    return costMIN;
  }
  /* look further */
  else{
    return knightAstar(rNow, cNow, rowGoal, columnGoal);
  } 
} 

int main(int argc, char *argv[]) {
  int x0,y0, x1,y1;
  do {
    printf("Start location (x,y) = "); fflush(stdout);
    scanf("%d %d", &x0, &y0);
  } while (!isValidLocation(x0,y0));
  do {
    printf("Goal location (x,y)  = "); fflush(stdout);
    scanf("%d %d", &x1, &y1);
  } while (!isValidLocation(x1,y1));

  initialize(y0, x0, y1, x1);
  printf("Length shortest path: %d\n", knightAstar(y0,x0, y1,x1));
  printf("#visited states: %lu\n", statesVisited);
  return 0;
}
