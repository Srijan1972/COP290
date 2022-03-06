#include "mkl.h"
#include<bits/stdc++.h>
#include "dnn_weights.h"
typedef struct{
    int label; 
    float prob;
} pred_t;
using namespace std;
int p,q,r;

void top3(float* mat,int n){
    float first=-1*FLT_MAX,second=-1*FLT_MAX,third=-1*FLT_MAX;
    p=0,q=0,r=0;
    for(int i=0;i<n;i++){
        if(mat[i]>first){
            third=second;
            r=q;
            second=first;
            q=p;
            first=mat[i];
            p=i;
        }
        else if(mat[i]>second){
            third=second;
            r=q;
            second=mat[i];
            q=i;
        }
        else if(mat[i]>third){
            third=mat[i];
            r=i;
        }
    }
}

void relu(float* mat,int n){
    for(int i=0;i<n;i++) mat[i]=max(float(0),mat[i]);
}

void softmax(float* mat,int n){
    float sum=0.0;
    for(int i=0;i<n;i++) mat[i]=exp(mat[i]);
    for(int i=0;i<n;i++) sum+=mat[i];
    for(int i=0;i<n;i++) mat[i]/=sum;
}

pred_t* libaudioAPI(const char* audiofeatures,pred_t* pred){
    string audioclip(audiofeatures);
    int a=1,b=250,c=144;
    ifstream inpin(audioclip);
    if(!inpin) throw std::invalid_argument("File not found");
    float* inp=new float[a*b];
    for(int i=0;i<a*b;i++) inpin>>inp[i];
    float weight1[b*c]=IP1_WT;
    float bias1[c*a]=IP1_BIAS;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,inp,b,weight1,c,1.0,bias1,b); //FC1
    relu(bias1,c*a);
    a=1,b=144,c=144;
    float weight2[b*c]=IP2_WT;
    float bias2[c*a]=IP2_BIAS;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,bias1,b,weight2,c,1.0,bias2,b); //FC2
    relu(bias2,c*a);
    a=1,b=144,c=144;
    float weight3[b*c]=IP3_WT;
    float bias3[c*a]=IP3_BIAS;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,bias2,b,weight3,c,1.0,bias3,b); //FC3
    relu(bias3,c*a);
    a=1,b=144,c=12;
    float weight4[b*c]=IP4_WT;
    float bias4[c*a]=IP4_BIAS;
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,bias3,b,weight4,c,1.0,bias4,b); //FC4
    softmax(bias4,c*a);
    top3(bias4,c*a);
    pred=new pred_t[3];
    pred[0].label=p;
    pred[0].prob=bias4[p];
    pred[1].label=q;
    pred[1].prob=bias4[q];
    pred[2].label=r;
    pred[2].prob=bias4[r];
    return pred;
}