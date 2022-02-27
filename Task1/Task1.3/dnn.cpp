#include "mkl.h"
#include<bits/stdc++.h>
#include "dnn_weights.h"
using namespace std;

string arr[12]={"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};
int p,q,r;

void top3(float* mat,int n){
    float first=-1*FLT_MAX,second=-1*FLT_MAX,third=-1*FLT_MAX;
    for(int i=0;i<n;i++){
        if(mat[i]>first){
            third=second;
            second=first;
            first=mat[i];
        }
        else if(mat[i]>second){
            third=second;
            second=mat[i];
        }
        else if(mat[i]>third){
            third=mat[i];
        }
    }
    for(int i=0;i<n;i++){
        if(mat[i]==first) p=i;
        if(mat[i]==second) q=i;
        if(mat[i]==third) r=i;
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

int main(int argc,char** argv){
    if(argc!=3){
        cout<<"Invalid number of arguments"<<endl;
        return 1;
    }
    string* args=new string[argc];
    for(int i=0;i<argc;i++){
        string temp(argv[i]);
        args[i]=temp;
    }
    int a=1,b=250,c=144;
    ifstream inpin(args[1]);
    if(!inpin){
        cout<<"File not found"<<endl;
        return 1;
    }
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
    ofstream resout;
    resout.open(args[2],ios_base::app);
    resout<<args[1]<<' '<<arr[p]<<' '<<arr[q]<<' '<<arr[r]<<' '<<bias4[p]<<' '<<bias4[q]<<' '<<bias4[r]<<endl;
    return 0;
}