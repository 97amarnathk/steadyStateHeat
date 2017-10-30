/*
  =============================================================================
  Name        :   steadyStateHeat.c
  Authors     :   Chahak Mehta, Amarnath Karthi
  Description :   Solve the 2D Heat Equation to get the steady state temperature
  =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MROWS 1024
#define MCOLS 1024
#define VERBOSE 0


/*  GRID Functions
    to create, initialize, free, display the temperature grid
 */
double **createGrid(int m, int n);
double **initGridSerial(int m, int n, double l, double r, double u, double d);
double **freeGrid(double **grid, int m, int n);
void   displayGrid(double **grid, int m, int n);

int main() {
  /*  tgrid = temperature grid
   *  m     = number of rows
   *  n     = number of cols
   *  eps   = error tolerance
   *  l     = left temperature
   *  r     = right temperature
   *  u     = up temperature
   *  d     = down temperature
   */
  int m = 3, n = 6;
  double eps = 0.01;
  double l = 1, r = 2, u = 3, d = 4;
  double **tgrid;

  if(VERBOSE)
    printf("Hello World!\n");

  //Check limits
  if(m>MROWS || m<=0) {
    printf("m should be between 0 and %d\n", MROWS);
    return(0);
  }
  if(n>MCOLS || n<=0) {
    printf("n should be between 0 and %d\n", MCOLS);
    return(0);
  }
  if(eps<=0) {
    printf("eps should be greater than 0\n");
    return(0);
  }

  //Create and initialize Temperature Grid
  tgrid = initGridSerial(m, n, l, r, u, d);
  if(tgrid == NULL) {
    printf("tgrid could not be initialized\n");
    return(0);
  }
  if(VERBOSE)
    printf("tgrid initialized sucessfully\n");

  //Do whatever you want

  displayGrid(tgrid, m, n);

  //Free the grid
  tgrid = freeGrid(tgrid, m, n);
  if(VERBOSE)
    printf("grid freed\n");
  return(0);
}

/*  GRID Functions
    to create, initialize, free, display the temperature grid
 */
double **createGrid(int m, int n) {
  double **grid;
  int i;
  grid = (double**) malloc(m*sizeof(double*));
  for(i=0;i<m;i++)
    grid[i] = (double*) malloc(n*sizeof(double));
  return(grid);
}

double **initGridSerial(int m, int n, double l, double r, double u, double d) {
  double **grid;
  grid = createGrid(m, n);
  int i,j;

  //If not created return NULL
  if(grid == NULL)
    return(NULL);

  //Initialize the boundary
  for(i=0; i<n;i++) {
    grid[0][i] = d;
    grid[m-1][i] = u;
  }
  for(j=1; j<m-1; j++) {
    grid[j][0] = l;
    grid[j][n-1] = r;
  }

  //Initialize inner values with mean of the boundary
  double mean = (((double)l+r)*(m-2) + ((double)u+d)*(n))/(2*n+2*m-4);
  for(j=1; j<m-1; j++)
    for(i=1; i<n-1; i++)
      grid[j][i]=mean;

  return grid;
}

double **freeGrid(double **grid, int m, int n) {
  int i;
  for(i=0; i<m; i++)
    free(grid[i]);
  free(grid);
  return NULL;
}

void displayGrid(double **grid, int m, int n) {
  printf("\n");
  int i,j;
  //print from top to bottom
  for(j=m-1; j>=0; j--) {
    //print from left to right
    for(i=0; i<n; i++)
      printf("%lf ", grid[j][i]);
    printf("\n");
  }
}
