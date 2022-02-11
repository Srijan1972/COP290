#include "mkl.h"

void fullyConnectedMKL(float* inp,float* weight,float* bias,int a,int b,int c){
    cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,inp,a,weight,b,1.0,bias,a);
}