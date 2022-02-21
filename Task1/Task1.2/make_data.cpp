#include<bits/stdc++.h>
using namespace std;

void calculateSD(float data[]) {
    ofstream resout;
resout.open("individualplots.txt",std::ios_base::app);
  float sum = 0.0, mean, standardDeviation = 0.0;
  int i;

  for(i = 0; i < 100; ++i) {
    sum += data[i];
  }

  mean = sum / 100;
  resout<<mean<<' ';
  for(i = 0; i < 100; ++i) {
    standardDeviation += pow(data[i] - mean, 2);
  }

  resout<<sqrt(standardDeviation / 100)<<"\n";
}

int main(){
    ifstream mkl("mkl_times.txt");
    ifstream openblas("openblas_times.txt");
    ifstream pthread_if("pthread_times.txt");
    ofstream resout;
resout.open("individualplots.txt",std::ios_base::app);
    float* arr=new float[100];
    int a,b,c;
    for(int i=0;i<100;i++){
        mkl>>arr[i];
    }
    calculateSD(arr);
    for(int i=0;i<100;i++){
        openblas>>arr[i];
    }
    calculateSD(arr);
    for(int i=0;i<100;i++){
        pthread_if>>arr[i];
    }
    calculateSD(arr);
    return 0;
}