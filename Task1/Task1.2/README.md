# COP290 Task 1.2: Using predifined libraries and p-threads to improve fullyconnected layer

## Authors :- Nischay Diwan and Srijan Gupta

## Files:-

matrix_mkl.cpp: this contains source code for generation of output files performing matrix calculations using intel mkl math library.

matrix_openblas.cpp: this contains source code for generation of output files performing matrix calculations using openblas math library.

matrix_pthread.cpp: this contains source code for generation of output files performing matrix calculations using c++ pthreads implementations. By default number of threads used are 4, which can be set in the variable 'th' in the code. It assigns nth row of first matrix to the ith thread if (n mod th = i).

makefile: this contains compile codes for specific targets.

combinedplot.gnu: this is gnuplot script to plot the runtimes of 100 iterations of a sample case, under each method, y axis is runtime in ns and x axis is 1-mkl, 2-openblas, 3-pthread.

individualplots.gnu: this is gnuplot script to plot the mean and standard deviations of runtimes of 10 sample matrix size combinations.

## Features

- **Fully Connected Layer** in which an input matrix, a weight matrix and a bias matrix are taken in as inputs and the output is given by the product of the input and weight matrices added to the bias matrix. (fullyConnected)

- **Implementation** in which a argument is passed while execution to choose which way to implement. (mkl, openblas, pthread( uses 4 threads))

### Compilation

```bash
    make {Target}
```

{Target} : all
This will echo a message indicating the use.

{Target} : mkl
This will compile the `matrix_mkl.cpp` file into an executable `yourcode.out`

{Target} : openblas
This will compile the `matrix_openblas.cpp` file into an executable `yourcode.out`

{Target} : pthread
This will compile the `matrix_pthread.cpp` file into an executable `yourcode.out`

{Target} : naive
This will compile the `matrix_naive.cpp` file into an executable `yourcode.out`

{Target} : clean
This removes executable `yourcode.out`

### Running Instructions

#### Fully Connected Layer

The command should be of the format:

```bash
    ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt type
```

Where `inputmatrix.txt`, `weightmatrix.txt` and `biasmatrix.txt` are `.txt` files containing the respective matrices and `outputmatrix.txt` will contain the resulting matrix.

Where *type* is *mkl/pthread/openblas*
*type* should be left empty for naive implementation.

#### Gnuplot

```bash
    gnuplot
    load "combinedplot.gnu"
    load "individualplots.gnu"
```

## Observations

- MKL Library was both the most efficient and showed the least amount of deviation.
- Our self made pthread implementation could not match running speeds of the pre-made libraries MKL and Openblas.
- Naive implementation is faster for most of matrix sizes than pthread but less than pre-defined libraries.

## Note

- Matrices are inputted with their column dimension, row dimension and then all the elements in column major order.
- Names of `.txt` files given in this README are not binding.
