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

## Algorithm

The solver works on the Gauss Seidel Approach.

### Serial 

The serial algorithms is quite simple. To approach the final solution, each point in the grid takes up the value which is average of its surrounding 4 neighbors (Left, Right, Up, Down). This step is known as a **relaxation**. At every iteration all points in the grid are relaxed. This goes on until either we complete a specific number of iterations or if the difference between any 2 neighboring points is no more than **e** (epsilon), which is a preset value.


```
for n in range(N_ITER):
    for i in range(M):
      for j in range(N):
        A[i][j] = average(A[i-1][j] + A[i+1][j] + A[i][j+1] + A[i][j-1])
```

## Authors
* Chahak Mehta
* Amarnath Karthi
