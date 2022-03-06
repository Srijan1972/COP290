#include<bits/stdc++.h>
#include "audioAPI.h"
using namespace std;

string arr[12]={"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};

int main(int argc,char** argv){
    if(argc!=3){
        std::cout<<"Invalid number of arguments"<<std::endl;
        return 1;
    }
    pred_t* pred=NULL;
    try{
        pred=libaudioAPI(argv[1],pred);
    }
    catch(const std::exception& e){
        std::cerr<<"Error: "<<e.what()<<'\n';
    }
    string outfile(argv[2]);
    ofstream resout;
    resout.open(outfile,ios_base::app);
    resout<<argv[1]<<' '<<arr[pred[0].label]<<' '<<arr[pred[1].label]<<arr[pred[2].label]<<' '<<pred[0].prob<<' '<<pred[1].prob<<' '<<pred[2].prob<<'\n';
    return 0;
}