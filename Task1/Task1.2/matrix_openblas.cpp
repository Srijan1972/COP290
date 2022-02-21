#include<cblas.h>
#include<bits/stdc++.h>

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
    if(args[6]=="openblas"){
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
        std::ofstream times;
        times.open("openblas_times.txt",std::ios_base::app);
        auto start=std::chrono::high_resolution_clock::now();
        cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,a,c,b,1.0,inp,a,weight,b,1.0,bias,a);
        auto end=std::chrono::high_resolution_clock::now();
        times<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<std::endl;
        resout<<c<<"\n";
        resout<<a<<"\n";
        for(int i=0;i<c*a;i++) resout<<bias[i]<<"\n";
    }
    else{
        std::cout<<"Invalid operation"<<std::endl;
        return 1;
    }
    return 0;
}