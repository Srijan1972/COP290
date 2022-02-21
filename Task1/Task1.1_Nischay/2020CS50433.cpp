#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <exception>
using namespace std;

void fullyconnected(string infile, string wtfile, string biasfile, string outfile){

	int r,c; // r is rows and c is columns in matrices

	ifstream F1(infile);
	if(!F1){
		throw runtime_error("FileNotFound");
	}
	F1 >> c >> r;
	float in[r][c]; // parsing input matrix
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F1 >> in[j][i];
		}
	}
	F1.close();

	ifstream F2(wtfile);
	if(!F2){
		throw runtime_error("FileNotFound");
	}
	F2 >> c >> r;
	float wt[r][c]; // parsing weight matrix
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F2 >> wt[j][i];
		}
	}
	F2.close();

	ifstream F3(biasfile);
	if(!F3){
		throw runtime_error("FileNotFound");
	}
	F3 >> c >> r;
	float bias[r][c]; // parsing bias matrix
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F3 >> bias[j][i];
		}
	}
	F3.close();

	float out[r][c]; // calculating output matrix
	for(int i = 0;i<r;i++){
		for(int j=0;j<c;j++){
			out[i][j] = bias[i][j];
			for(int k=0;k < (sizeof(in[0])/sizeof(in[0][0]));k++){
				out[i][j] = out[i][j] + (in[i][k] * wt[k][j]);
			}
		}
	}

	ofstream F4(outfile); // printing output matrix
	F4 << c << endl << r << endl;
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F4 << out[j][i] << endl;
		}
	}
	F4.close();
}

float relu(float x){ // relu function 
	if(x < 0.0){
		return 0.0;
	}else{
		return x;
	}
}

float tanH(float x){ // tanh function
	float num = exp(x) * exp(x) -1;
	float denum = exp(x) * exp(x) +1;
	return num/denum;
}

void activation(string m, string infile,string outfile){
	int r,c; // rows and columns
	ifstream F1(infile);
	if(!F1){
		throw runtime_error("FileNotFound");
	}
	F1 >> c >> r; // parsing input
	float in[r][c];
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F1 >> in[j][i];
		}
	}
	F1.close();

	float out[r][c]; // calculating output
	for(int i = 0;i<r;i++){
		for(int j=0;j<c;j++){
			if(m == "relu"){
				out[i][j] = relu(in[i][j]); // relu
			}else if(m == "tanh"){
				out[i][j] = tanH(in[i][j]); // tanh
			}
		}
	}

	ofstream F4(outfile); // printing output
	F4 << c << endl << r << endl;
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F4 << out[j][i] << endl;
		}
	}
	F4.close();
}

void pooling(string m, string infile,int s,string outfile){
	// rows and columns
	int r,c;
	ifstream F1(infile);
	if(!F1){
		throw runtime_error("FileNotFound");
	}
	F1 >> c >> r; // input matrix
	float in[r][c];
	for(int i = 0; i < c; i++){
		for(int j =0;j<r;j++){
			F1 >> in[j][i];
		}
	}
	F1.close();

	float out[r/s][c/s];
	for(int i = 0;i<(r/s);i++){
		for(int j=0;j<(c/s);j++){
			if(m == "max"){ // performing max pooling
				out[i][j] = in[2*i][2*j];
				for(int a = 0;a< s;a++){
					for(int b=0;b<s;b++){
						if(in[a+2*i][b+2*j] > out[i][j]){
							out[i][j] = in[a+2*i][b+2*j];
						}
					}
				}
			}else if(m == "average"){ // average pooling
				out[i][j] = 0.0;
				for(int a = 0;a< s;a++){
					for(int b=0;b<s;b++){
						out[i][j] = out[i][j] + (in[a+2*i][b+2*j]/(s*s));
					}
				}
			}
		}
	}

	ofstream F4(outfile); // printing output
	F4 << (c/s) << endl << (r/s) << endl;
	for(int i = 0; i < (c/s); i++){
		for(int j =0;j<(r/s);j++){
			F4 << out[j][i] << endl;
		}
	}
	F4.close();
}

void probability(string m, string infile,string outfile){

	int c; // input matrix dimension
	ifstream F1(infile);
	if(!F1){
		throw runtime_error("FileNotFound");
	}
	F1 >> c;
	float in[c];
	for(int i = 0; i < c; i++){
		F1 >> in[i];
	}
	F1.close();

	float out[c];
	for(int i = 0;i<c;i++){
		if(m == "softmax"){ // softmax func
			out[i] = exp(in[i]);
			float den = 0.0;
			for(int k =0;k<c;k++){
				den = den + exp(in[k]);
			}
			out[i] = out[i] / den;
		}else if(m == "sigmoid"){ // sigmoid func
			out[i] = 1.0 / (exp(-(in[i]))+1.0);
		}
	}

	ofstream F4(outfile);
	F4 << c << endl; // printing out matrix
	for(int i = 0; i < c; i++){
		F4 << out[i] << endl;
	}
	F4.close();
}

int main(int argc, char* argv[]){
	// different cases for each function given input
	try{
		if(argc == 1){
			return 0;
		}
		if(string(argv[1]) == "fullyconnected"){
			string a = string(argv[2]);
			string b = string(argv[3]);
			string c = string(argv[4]);
			string d = string(argv[5]);
			fullyconnected(a,b,c,d);
		}else if(string(argv[1]) == "activation"){
			string a = string(argv[2]);
			string b = string(argv[3]);
			string c = string(argv[4]);
			activation(a,b,c);
		}else if(string(argv[1]) == "pooling"){
			string a = string(argv[2]);
			string b = string(argv[3]);
			int c = stoi(argv[4]);
			string d = string(argv[5]);
			pooling(a,b,c,d);
		}else if(string(argv[1]) == "probability"){
			string a = string(argv[2]);
			string b = string(argv[3]);
			string c = string(argv[4]);
			probability(a,b,c);
		}else{
			int x;
			throw x;
		}
	}catch(int x){
		cout << "invalid called parameters\n";
	}catch(runtime_error& e){
		cerr << e.what() << "\n";
	}
	return 0;
}