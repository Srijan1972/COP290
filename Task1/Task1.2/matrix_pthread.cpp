#include <bits/stdc++.h>
using namespace std;

int da,db,dc;
float Ip[1000][1000];
float Wp[1000][1000];
float Bp[1000][1000];
int r = 0;

void* thrfunc(void* arg)
{
    int i = r++;
    for (int j = 0; j < dc; j++)
      for (int k = 0; k < db; k++)
        Bp[i][j] += Ip[i][k] * Wp[k][j];
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

    pthread_t threads[a];
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    for (int i = 0; i < a; i++) {
        int* p;
        pthread_create(&threads[i], NULL, thrfunc, (void*)(p));
    }
    for (int i = 0; i < a; i++) {
        pthread_join(threads[i], NULL);  
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < c; j++) {
            bias[a*j + i] = Bp[i][j];
        }
    }
}