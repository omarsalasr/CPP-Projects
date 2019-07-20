#include <stdio.h>
#include <stdlib.h>

int maxsize, maxtime;
int neighbors(int anArray[maxsize][maxsize][maxsize+1], int i , int j, int size, int step);
void printGrid(int myGrid[maxsize][maxsize][maxsize+1], int size, int step);

int main(){
  int i,j,k,row,col;
  maxsize = 4;
  maxtime = 2;
  int grid[maxsize][maxsize][maxsize+1];
    for (j = 0; j < maxsize; j++) {
      for (k = 0; k < maxsize; k++) {
        grid[j][k][0] = 0;
      }
    }
  printf("Input coordinates:\n");
  do{
    scanf("%d %d", &row, &col);
    if(row < -1 || col < -1 || row >= maxsize || col >= maxsize){
      printf("Invalid Input\n");
      continue;
    }
    grid[row][col][0] = 1;
  } while (row != -1 && col != -1);
  for(i = 1){

  }
  printGrid(grid, maxsize, 0);
  return 0;
}

int neighbors(int anArray[maxsize][maxsize][maxsize+1], int i , int j, int size, int step){
  int numNeigh = 0;
  int r,c;
  for(r = i-1;r<=i+1;r++)
    for(c = j-1;c<=j+1;c++){
      if(i == r && j == c)
        continue;
      else if(anArray[r][c][step] == 1)
        numNeigh++;
    }
  return numNeigh;
}

void printGrid(int myGrid[maxsize][maxsize][maxsize+1], int size, int step){
  int j,k;
  for (j = 0; j < size; j++) {
    for (k = 0; k < size; k++)
      printf("%d ", myGrid[j][k][step]);
    printf("\n");
  }
}
// 0 1 2 3
// 0 0 0 0 0
// 0 0 0 0 1
// 0 0 0 0 2
// 0 0 0 0 3
