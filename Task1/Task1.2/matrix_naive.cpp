#include<bits/stdc++.h>

float tanhOverload(float x){
    float t=exp(2.0*x);
    return (t-1.0)/(t+1.0);
}

std::vector<std::vector<float>> fullyConnected(std::vector<std::vector<float>> inp,std::vector<std::vector<float>> weight,std::vector<std::vector<float>> bias){
    int a=inp.size();
    int b=inp[0].size();
    if(b!=weight.size()) throw std::length_error("Input and weight matrices cannot be multiplied");
    int c=weight[0].size();
    if(bias.size()!=a || bias[0].size()!=c) throw std::length_error("Bias and output matrices cannot be added");
    std::vector<std::vector<float>> res(a,std::vector<float>(c,0.0));
    for(int i=0;i<a;i++){
        for(int j=0;j<c;j++){
            for(int k=0;k<b;k++){
                res[i][j]+=(inp[i][k]*weight[k][j]);
            }
            res[i][j]+=bias[i][j];
        }
    }
    return res;
}

void reluActivate(std::vector<std::vector<float>> &inp){
    for(std::vector<float> &vec:inp){
        for(int i=0;i<vec.size();i++){
            float t=fmax(0.0,vec[i]);
            vec[i]=t;
        }
    }
}

void tanhActivate(std::vector<std::vector<float>> &inp){
    for(std::vector<float> &vec:inp){
        for(int i=0;i<vec.size();i++){
            float t=tanhOverload(vec[i]);
            vec[i]=t;
        }
    }
}

std::vector<std::vector<float>> maxPool(std::vector<std::vector<float>> inp,int sub){
    if(inp.size()!=inp[0].size()) throw std::length_error("Not a square matrix");
    int n=inp.size();
    std::vector<std::vector<float>> res(n/sub,std::vector<float>(n/sub,(-1.0)*FLT_MAX));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i/sub][j/sub]=fmax(res[i/sub][j/sub],inp[i][j]);
        }
    }
    return res;
}

std::vector<std::vector<float>> avgPool(std::vector<std::vector<float>> inp,int sub){
    if(inp.size()!=inp[0].size()) throw std::length_error("Not a square matrix");
    int n=inp.size();
    std::vector<std::vector<float>> res(n/sub,std::vector<float>(n/sub,0.0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            res[i/sub][j/sub]+=inp[i][j];
        }
    }
    for(int i=0;i*sub<n;i++){
        for(int j=0;j*sub<n;j++){
            res[i][j]/=(sub*sub);
        }
    }
    return res;
}


void softmaxProb(std::vector<float> &inp){
    float sum=0.0;
    for(int i=0;i<inp.size();i++){
        inp[i]=exp(inp[i]);
        sum+=inp[i];
    }
    for(int i=0;i<inp.size();i++){
        inp[i]/=sum;
    }
}

void sigmoidProb(std::vector<float> &inp){
    for(int i=0;i<inp.size();i++){
        float t=exp(inp[i]);
        inp[i]=t/(t+1);
    }
}

int main(int argc,char** argv){
    std::string* args=new std::string[argc];
    for(int i=0;i<argc;i++){
        std::string temp(argv[i]);
        args[i]=temp;
    }
    try{
        switch (argc){
            case 1:
                std::cout<<"Nothing to execute\n";
                break;
            case 5:{
                if(args[1]=="activation"){
                    std::ifstream inpin(args[3]);
                    std::ofstream resout(args[4]);
                    if(!inpin) throw std::invalid_argument("File not found");
                    int b,a; inpin>>b>>a;
                    std::vector<std::vector<float>> inp(a,std::vector<float>(b));
                    for(int i=0;i<b;i++){
                        for(int j=0;j<a;j++) inpin>>inp[j][i];
                    }
                    if(args[2]=="relu") reluActivate(inp);
                    else if(args[2]=="tanh") tanhActivate(inp);
                    else throw std::invalid_argument("Invalid activation type");
                    resout<<inp[0].size()<<"\n";
                    resout<<inp.size()<<"\n";
                    for(int i=0;i<inp[0].size();i++){
                        for(int j=0;j<inp.size();j++) resout<<inp[j][i]<<"\n";
                    }
                }
                else if(args[1]=="probability"){
                    std::ifstream inpin(args[3]);
                    std::ofstream resout(args[4]);
                    if(!inpin) throw std::invalid_argument("File not found");
                    int n; inpin>>n;
                    std::vector<float> inp(n);
                    for(int i=0;i<n;i++) inpin>>inp[i];
                    if(args[2]=="softmax") softmaxProb(inp);
                    else if(args[2]=="sigmoid") sigmoidProb(inp);
                    else throw std::invalid_argument("Invalid probability type");
                    resout<<inp.size()<<"\n";
                    for(int i=0;i<n;i++) resout<<inp[i]<<"\n";
                }
                else throw std::invalid_argument("No valid function for this parameter length");
                break;
            }
            case 6:{
                if(args[1]=="fullyconnected"){
                    std::ifstream inpin(args[2]);
                    std::ifstream weightin(args[3]);
                    std::ifstream biasin(args[4]);
                    std::ofstream resout(args[5]);
                    if(!inpin || !weightin || !biasin) throw std::invalid_argument("File not found");
                    int b,a; inpin>>b>>a;
                    std::vector<std::vector<float>> inp(a,std::vector<float>(b));
                    for(int i=0;i<b;i++){
                        for(int j=0;j<a;j++) inpin>>inp[j][i];
                    }
                    weightin>>b>>a;
                    std::vector<std::vector<float>> weight(a,std::vector<float>(b));
                    for(int i=0;i<b;i++){
                        for(int j=0;j<a;j++) weightin>>weight[j][i];
                    }
                    biasin>>b>>a;
                    std::vector<std::vector<float>> bias(a,std::vector<float>(b));
                    for(int i=0;i<b;i++){
                        for(int j=0;j<a;j++) biasin>>bias[j][i];
                    }
                    std::vector<std::vector<float>> res=fullyConnected(inp,weight,bias);
                    resout<<res[0].size()<<"\n";
                    resout<<res.size()<<"\n";
                    for(int i=0;i<res[0].size();i++){
                        for(int j=0;j<res.size();j++) resout<<res[j][i]<<"\n";
                    }
                }
                else if(args[1]=="pooling"){
                    std::ifstream inpin(args[3]);
                    std::ofstream resout(args[5]);
                    int sub=std::stoi(args[4]);
                    if(!inpin) throw std::invalid_argument("File not found");
                    int b,a;
                    inpin>>b>>a;
                    std::vector<std::vector<float>> inp(a,std::vector<float>(b));
                    for(int i=0;i<b;i++){
                        for(int j=0;j<a;j++) inpin>>inp[j][i];
                    }
                    std::vector<std::vector<float>> res;
                    if(args[2]=="max") res=maxPool(inp,sub);
                    else if(args[2]=="average") res=avgPool(inp,sub);
                    else throw std::invalid_argument("Invalid pooling type");
                    resout<<res[0].size()<<"\n";
                    resout<<res.size()<<"\n";
                    for(int i=0;i<res[0].size();i++){
                        for(int j=0;j<res.size();j++) resout<<res[j][i]<<"\n";
                    }
                }
                else throw std::invalid_argument("No valid function for this parameter length");
                break;
            }
            default:
                std::cout<<"Invalid number of arguments\n";
                break;
        }
    }
    catch(const std::exception &e){
        std::cerr<<"Error: "<<e.what()<<std::endl;
    }
    return 0;
}