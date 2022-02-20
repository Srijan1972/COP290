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
                cout << i<<","<<j << endl;
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
    th = 2;
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