Author :- Nischay Diwan, 2020CS50433

Title :- COP Task 1/Sub Task 1

Contents :- A .tar.gz file containing, This file Readme.md, a c++ source code file 2020CS50433.cpp, and Makefile.

Brief Description :- The c++ file contains few functions that can be executed by
	1. building the file using make
	2. give command with parameters e.g.; 
		$ ./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt outputmatrix.txt
		$ ./yourcode.out activation relu inputmatrix.txt outputmatrix.txt
		$ ./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt
		$ ./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt
		$ ./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt
		$ ./yourcode.out probability softmax inputvector.txt outputvector.txt
		$ ./yourcode.out probability sigmoid inputvector.txt outputvector.txt

Functions :-

main: takes terminal arguments, to check which function is called, and so execute the respective function along with the file/input parameters.
	
fullyconnected: its take 4 inputs having matrix in column major form, infile(input matrix), wtfile(weight matrix), biasfile(bias matrix), also outfile, which will contain output matrix. Here inner product of in and wt is taken and then added to bias to give out file.

relu: takes in float and apply 'relu' function and return.

tanh: takes in float and apply 'tanh' function and return.

activation: its take 3 inputs, string m(relu or tanh), 2 having matrix in column major form, infile(input matrix), also outfile, which will contain output matrix. Here according to m, relu or tanh is applied to individual elements of matrix and returned.

pooling: its take 4 inputs, string m(relu or tanh), 2 having matrix in column major form, infile(input matrix), int s(stride) also outfile, which will contain output matrix. Here a pooling is performed on input matrix depending on m('max' or 'average') and stride.

probability: it takes 3 inputs, string m that is which probability func to apply, and input output vector files, it applies the softmax or sigmoid funcion.