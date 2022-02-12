#include"x86_64-linux-gnu/openblas64-pthread/cblas.h"

void fullyConnectedOpen(float* inp,float* weight,float* bias,int a,int b,int c){
    cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,inp,a,weight,b,1.0,bias,a);
}