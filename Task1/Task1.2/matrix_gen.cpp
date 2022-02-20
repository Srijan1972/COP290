#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>

using std::cout;
using std::endl;
using std::setprecision;

constexpr int FLOAT_MIN = -100;
constexpr int FLOAT_MAX = 100;
const int n=100;
const int m=117;
const int k=115;

int main()
{
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_MAX);
    std::ofstream inpout("input.txt");
    std::ofstream weightout("weight.txt");
    std::ofstream biasout("bias.txt");
    float** inp= new float*[n];
    for(int i=0;i<n;i++){
        inp[i]=new float[m];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) inp[i][j]=distr(eng);
    }
    inpout<<m<<"\n";
    inpout<<n<<"\n";
    for(int j=0;j<m;j++){
        for(int i=0;i<n;i++) inpout<<inp[i][j]<<"\n";
    }
    float** weight= new float*[m];
    for(int i=0;i<m;i++){
        weight[i]=new float[k];
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<k;j++) weight[i][j]=distr(eng);
    }
    weightout<<k<<"\n";
    weightout<<m<<"\n";
    for(int j=0;j<k;j++){
        for(int i=0;i<m;i++) weightout<<weight[i][j]<<"\n";
    }
    float** bias= new float*[n];
    for(int i=0;i<n;i++){
        bias[i]=new float[k];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++) bias[i][j]=distr(eng);
    }
    biasout<<k<<"\n";
    biasout<<n<<"\n";
    for(int j=0;j<k;j++){
        for(int i=0;i<n;i++) biasout<<bias[i][j]<<"\n";
    }
    return 0;
}