# COP290 Task 1.1: User-Defined Matrix Functions

## Features

- **Fully Connected Layer** in which an input matrix, a weight matrix and a bias matrix are taken in as inputs and the output is given by the product of the input and weight matrices added to the bias matrix. (fullyConnected)

- **Activation** Activating a matrix using either *relu* or *tanh* functions. (reluActivate,tanhActivate)

- **Subsampling** Reducing the size of a square matrix by a certain factor by either *max* or *average* pooling. (maxPool,avgPool)

- **Probability Conversion** Converting a vector of values into a vector of probabilities using either the *softmax* or the *sigmoid* function. (softmaxProb,sigmoidProb)

- **Exceptions handled-** Invalid function names, invalid types, invalid number of arguments and input file does not exist

## Execution

### Compilation

```bash
    make
```

This will compile the `matrix.cpp` file into an executable `yourcode.out`

### Running Instructions

#### Fully Connected Layer

The command should be of the format:

```bash
    ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
```

Where `inputmatrix.txt`, `weightmatrix.txt` and `biasmatrix.txt` are `.txt` files containing the respective matrices and `outputmatrix.txt` will contain the resulting matrix.

#### Activation

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

Where *type* is *softmax/sigmoid*, `inputvector.txt` contains the input vector and `outputvector.txt` contains the output vector.

## Note

- Matrices are inputted with their column dimension, row dimension and then all the elements in column major order.
- Names of `.txt` files given in this README are not binding.
