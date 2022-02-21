#include <bits/stdc++.h>
using namespace std;

int da,db,dc;
float Ip[1000][1000]={0};
float Wp[1000][1000]={0};
float Bp[1000][1000]={0};
int r = 0;
int th;
void* thrfunc(void* arg){
    if(r < da){
        int i = r++;
        while(i < da){
            for (int j = 0; j < dc; j++){
                // cout << i<<","<<j << endl;
                for (int k = 0; k < db; k++){
                    Bp[i][j] += Ip[i][k] * Wp[k][j];
                }
            }
            i = i+th;
        }
    }
}
void fullyConnectedPthread(float* inp,float* weight,float* bias,int a,int b,int c){
	da = a;
	db = b;
	dc = c;
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            Ip[i][j] = inp[a*j + i];
        }
    }

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < c; j++) {
            Wp[i][j] = weight[b*j + i];
        }
    }

    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            Bp[i][j] = bias[a*j + i];
        }
    }
    th = 4;
    pthread_t threads[th];
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    for (int i = 0; i < th; i++) {
        int* k;
        pthread_create(&threads[i], NULL, thrfunc, (void*)(k));
    }
    for (int i = 0; i < th; i++) {
        pthread_join(threads[i], NULL);  
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            bias[a*j + i] = Bp[i][j];
        }
    }
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
    if(args[6]=="pthread"){
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
        // std::ofstream times;
        // times.open("pthread_times.txt",std::ios_base::app);
        // auto start=std::chrono::high_resolution_clock::now();
        fullyConnectedPthread(inp,weight,bias,a,b,c);
        // auto end=std::chrono::high_resolution_clock::now();
        // times<<std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()<<std::endl;
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