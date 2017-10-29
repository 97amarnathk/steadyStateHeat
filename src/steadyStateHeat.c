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
#include "grid.h"

#define MROWS 8192
#define MCOLS 8192


#define VERBOSE 0

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
  int m = 100, n = 100;
  double eps = 0.01;
  double l = 100.0, r = 100.0, u = 100.0, d = 0.0;

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
  tgrid = initGrid(m, n, l, r, u, d);
  if(tgrid == NULL) {
    printf("tgrid could not be initialized\n");
    return(0);
  }
  if(VERBOSE)
    printf("tgrid initialized sucessfully");

  //Do whatever you want




  //Free the grid
  tgrid = freeGrid(tgrid, m, n);
  if(VERBOSE)
    printf("grid freed\n");
  return(0);
}
