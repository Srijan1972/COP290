# Audio Processing Library

## Features

- Sample audios provided in the audios directory
- A python script `compute_mfcc.py` which takes audio clips and generates a feature vector of size 250 from the same. (Stores the features in a txt file in the mfcc_features directory)
- A header file `dnn_weights.h` which contains pre-trained weights and biases for the neural network.
- The file `audioAPI.cpp` contains a function **libaudioAPI** which takes a file (containing the feature vector) and an struct array and places the both the indices and probabilities of the 3 most prominent sounds in the audio clip and returns the array.
- The header file `audioAPI.h` is used as a header file to generate the library.
- `main.cpp` is a file used for testing.
- `libaudioAPI.so` is a library file used for linking the library to external files.

## Running Instructions

```bash
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
export MKL_BLAS_PATH=$MKLROOT
make
./yourcode.out inputfile.txt outputfile.txt
```

- The export commands are needed to properly set environment variables.
- The command `make` compiles the `audioAPI.cpp` file into a library file `libaudioAPI.so` and then compiles the `main.cpp` file into an executable `yourcode.out`.
- `inputfile.txt` is the location of the file which contains the feature vector (length 250) in row major order.
- `outputfile.txt` is the location of the file in which the output will be written. If the file does not exist it will be created else a line will be appended to the file.

## Output

The output will be of the form:

### inputfile.txt sound1 sound2 sound3 prob1 prob2 prob3

Where sound1,sound2,sound3 are the 3 most heard sounds in the audio and prob1,prob2,prob3 are their probabilities respectively.

## Note

- Available sounds- silence, unknown, yes, no, up, down, left, right, on, off, stop, go.
- The names of the txt files given in the `.txt` files given here are not binding.
- The intel mkl library has been used in `audioAPI.cpp` for matrix multiplication.
- The command `make clean` is also provided to delete the library files and executables.
