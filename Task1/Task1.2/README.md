# Authors :- Nischay Diwan and Srijan Gupta

# COP290 Task 1.2: Using predifined libraries and p-threads to improve fullyconnected layer


## Files:- 

matrix_gen.cpp: this generates input, weight and bias matrix files of random size of given dimensions.

matrix_mkl.cpp: this contains source code for generation of output files performing matrix calculations using intel mkl math library.

matrix_openblas.cpp: this contains source code for generation of output files performing matrix calculations using openblas math library.

matrix_pthread.cpp: this contains source code for generation of output files performing matrix calculations using c++ pthreads implementations. By default number of threads used are 4, which can be set in the variable 'th' in the code. It assigns nth row of first matrix to the ith thread if (n mod th = i).

makefile: this contains compile codes for specific targets.

combinedplot.gnu: this is gnuplot script to plot mean and SD of 100 iterations of a sample case, under each method, y axis is runtime in ns and x axis is 1-mkl, 2-openblas, 3-pthread.

combinedplot.png: box plot image if script, combinedplot.txt: list of times to plot.



## Features

- **Fully Connected Layer** in which an input matrix, a weight matrix and a bias matrix are taken in as inputs and the output is given by the product of the input and weight matrices added to the bias matrix. (fullyConnected)

- **Implementation** in which a argument is passed while execution to choose which way to implement. (mkl, openblas, pthread( uses 4 threads))

Prevoius Features: 
<!-- - **Activation** Activating a matrix using either *relu* or *tanh* functions. (reluActivate,tanhActivate)

- **Subsampling** Reducing the size of a square matrix by a certain factor by either *max* or *average* pooling. (maxPool,avgPool)

- **Probability Conversion** Converting a vector of values into a vector of probabilities using either the *softmax* or the *sigmoid* function. (softmaxProb,sigmoidProb)

- **Exceptions handled-** Invalid function names, invalid types, invalid number of arguments and input file does not exist -->

## Execution

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

{Target} : clean
This clean executables `yourcode.out`

{Target} : gen
This will compile the `matrix_gen.cpp` file into an executable `yourcode.out` and clean it.

### Running Instructions

#### Fully Connected Layer

The command should be of the format:

```bash
    ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt type
```

Where `inputmatrix.txt`, `weightmatrix.txt` and `biasmatrix.txt` are `.txt` files containing the respective matrices and `outputmatrix.txt` will contain the resulting matrix.

Where *type* is *mkl/pthread/openblas*

Previous Instructions:
<!-- #### Activation

The command should be of the format:

```bash
    ./yourcode.out activation type inputmatrix.txt stride outputmatrix.txt
```

Where *type* is *relu/tanh*, `inputmatrix.txt` contains the input matrix, *stride* is the factor by which the size of the matrix is to be reduced and `outputmatrix.txt` contains the output matrix.

#### Subsampling

The command should be of the format:

```bash
    ./yourcode.out pooling type inputmatrix.txt outputmatrix.txt
```

Where *type* is *max/average*, `inputmatrix.txt` contains the input matrix and `outputmatrix.txt` contains the output matrix

#### Probability

The command should be of the format:

```bash
    ./yourcode.out probability type inputvector.txt outputvector.txt
```

Where *type* is *softmax/sigmoid*, `inputvector.txt` contains the input vector and `outputvector.txt` contains the output vector. -->

#### Gnuplot

## Note

- Matrices are inputted with their column dimension, row dimension and then all the elements in column major order.
- Names of `.txt` files given in this README are not binding.