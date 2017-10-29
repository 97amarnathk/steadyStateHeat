/*
  =============================================================================
  Name        :   grid.h
  Authors     :   Chahak Mehta, Amarnath Karthi
  Description :   Header file to provide grid functionalities
  =============================================================================
 */

#ifndef GRID_H
#define GRID_H

double **createGrid(int m, int n) {
  double **grid;
  int i;
  grid = (double**) malloc(m*sizeof(double*));
  for(i=0;i<m;i++)
    grid[i] = (double*) malloc(n*sizeof(double));
  return(grid);
}

double **initGridSerial(int m, int n, int l, int r, int u, int d) {
  double **grid;
  grid = createGrid(m, n);
  int i,j;

  //If not created return NULL
  if(grid == NULL)
    return(NULL);

  //Initialize the boundary
  for(j=0; j<n;j++) {
    grid[0][j] = d;
    grid[m-1][j] = u;
  }
  for(i=1; i<m-1; i++) {
    grid[i][0] = l;
    grid[i][n-1] = r;
  }

  //Initialize inner values with mean of the boundary
  double mean = (((double)l+r)*(m-2) + ((double)u+d)*(n))/(2*n+2*m-4);
  for(i=1; i<m-1; i++)
    for(j=1; j<n-1; j++)
      grid[i][j]=mean;

  return grid;
}

void freeGrid(double **grid, int m, int n) {
  int i;
  for(i=0; i<m; i++)
    free(grid[i]);
  free(grid);
  return NULL;
}

#endif
