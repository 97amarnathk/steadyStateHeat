# steadyStateHeat
A parallel solver for Laplace's PDE. Built using OpenMP.

## Usage
Compile on GCC using the flags `lm`, `fopenmp` in C99 mode.

```
gcc steadyStateHeat.c -lm -fopenmp -std=C99 -o steadyStateHeat
```

Command line arguments:
* m : Grid width
* n : Grid height
* p : Number of threads to use. 

For example, if you want to solve on a 1024x1024 grid using 16 processors run the following:

```
./steadyStateHeat 1024 1024 16
```

## Authors
* Chahak Mehta
* Amarnath Karthi
