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
        A[i][j] = average(A[i-1][j] ,A[i+1][j] ,A[i][j+1] ,A[i][j-1])
```

### Parallel

The main problem in parallelising this algorithm is the inherent data dependency. To apply relaxation on `A[i][j]`, we need to first relax its 4 neighbors `A[i-1][j]` ,`A[i+1][j]` ,`A[i][j+1]` ,`A[i][j-1]`. Therefore we cannot do a simple row or column based data decomposition. Instead we need to do something called **Red Black Decomposition**. (Imagine a chessboard, red and black). All red nodes depend only on black nodes, and vice versa. There is no dependence between 2 nodes of same color. Using this data decomposition we can apply the following logic:


```
for n in range(N_ITER):

    # iterate through all black nodes parallely
    <!--BEGIN PARALLEL REGION-->
    for i in range(M/2):
        for j in range(N/2):
            m = 2*i
            n = 2*j
            A[m][n] = average(A[m-1][n] ,A[m+1][n] ,A[m][n+1] ,A[m][n-1])
            
     # iterate through all red nodes parallely
    <!--BEGIN PARALLEL REGION-->
    for i in range(M/2):
        for j in range(N/2):
            m = 2*i + 1
            n = 2*j + 1
            A[m][n] = average(A[m-1][n] ,A[m+1][n] ,A[m][n+1] ,A[m][n-1])
            
```

## Authors
* Chahak Mehta
* Amarnath Karthi
