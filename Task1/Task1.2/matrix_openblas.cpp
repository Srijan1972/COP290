#include <bits/stdc++.h>
#include<cblas.h>

void fullyConnectedOpen(float* inp,float* weight,float* bias,int a,int b,int c){
    cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,a,b,c,1.0,inp,b,weight,c,1.0,bias,c);
}