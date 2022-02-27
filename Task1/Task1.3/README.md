# COP290 Task 1.3- A Deep Neural Network

## Features

- Sample audios provided in the audios directory
- A python script `compute_mfcc.py` which takes audio clips and generates a feature vector of size 250 from the same. (Stores the features in a txt file in the mfcc_features directory)
- A header file `dnn_weights.h` which contains pre-trained weights and biases for the neural network.
- The file `dnn.cpp` takes a feature vector as input (from a txt file) and using the weights and biases, returns the 3 most heard sounds in the audio clip.

## Running Instructions

```bash
make
./yourcode.out inputfile.txt outputfile.txt
```

- The command `make` compiles the `dnn.cpp` file into an executable `yourcode.out`.
- `inputfile.txt` is the location of the file which contains the feature vector (length 250) in row major order.
- `outputfile.txt` is the location of the file in which the output will be written. If the file does not exist it will be created else a line will be appended to the file.

## Output

The output will be of the form:

### inputfile.txt sound1 sound2 sound3 prob1 prob2 prob3

Where sound1,sound2,sound3 are the 3 most heard sounds in the audio and prob1,prob2,prob3 are their probabilities respectively.

## Note

- Available sounds- silence, unknown, yes, no, up, down, left, right, on, off, stop, go.
- The names of the txt files given in the `.txt` files given here are not binding.
- The intel mkl library has been used in `dnn.cpp` for matrix multiplication.
- The command `make clean` is also provided to delete the executable.
