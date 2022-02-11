#include<bits/stdc++.h>
namespace mklmult{
    #include "matrix_mkl.cpp"
}
namespace openblasmult{
    #include "matrix_openblas.cpp"
}


int main(int argc,char** argv){
    std::string* args=new std::string[argc];
    for(int i=0;i<argc;i++){
        std::string temp(argv[i]);
        args[i]=temp;
    }
    if(argc!=7){
        std::cout<<"Invalid number of arguments"<<std::endl;
        return 1;
    }
    if(args[1]!="fullyconnected"){
        std::cout<<"Invalid operation to be performed"<<std::endl;
        return 1;
    }
    std::ifstream inpin(args[2]);
    std::ifstream weightin(args[3]);
    std::ifstream biasin(args[4]);
    std::ofstream resout(args[5]);
    if(!inpin || !weightin || !biasin){
        std::cout<<"File not found"<<std::endl;
        return 1;
    }
    if(args[6]=="mkl"){
        int b,a,c;
        inpin>>b>>a;
        float* inp=new float[a*b];
        for(int i=0;i<a*b;i++) inpin>>inp[i];
        weightin>>c>>b;
        float* weight=new float[b*c];
        for(int i=0;i<b*c;i++) weightin>>weight[i];
        biasin>>c>>a;
        float* bias=new float[c*a];
        for(int i=0;i<c*a;i++) biasin>>bias[i];
        mklmult::fullyConnectedMKL(inp,weight,bias,a,b,c);
        resout<<c<<"\n";
        resout<<a<<"\n";
        for(int i=0;i<c*a;i++) resout<<bias[i]<<"\n";
    }
    else if(args[6]=="openblas"){
        int b,a,c;
        inpin>>b>>a;
        float* inp=new float[a*b];
        for(int i=0;i<a*b;i++) inpin>>inp[i];
        weightin>>c>>b;
        float* weight=new float[b*c];
        for(int i=0;i<b*c;i++) weightin>>weight[i];
        biasin>>c>>a;
        float* bias=new float[c*a];
        for(int i=0;i<c*a;i++) biasin>>bias[i];
        openblasmult::fullyConnectedOpen(inp,weight,bias,a,b,c);
        resout<<c<<"\n";
        resout<<a<<"\n";
        for(int i=0;i<c*a;i++) resout<<bias[i]<<"\n";
    }
    else if(args[6]=="pthread"){}
    else{
        std::cout<<"Invalid operation"<<std::endl;
        return 1;
    }
    return 0;
}