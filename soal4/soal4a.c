#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main () {
    int Aa[4][2], Bb[2][5], Cc[10][10], total, i, j, k;
    
    Aa[0][0]=2;
    Aa[0][1]=3;
    Aa[1][0]=1;
    Aa[1][1]=3;
    Aa[2][0]=4;
    Aa[2][1]=1;
    Aa[3][0]=4;
    Aa[3][1]=5;
    Bb[0][0]=3;
    Bb[0][1]=4;
    Bb[0][2]=1;
    Bb[0][3]=2;
    Bb[0][4]=3;
    Bb[1][0]=2;
    Bb[1][1]=1;
    Bb[1][2]=1;
    Bb[1][3]=2;
    Bb[1][4]=4;

    key_t key = 1234;
    int *value;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    
    for(i=0;i<4;i++){
        for(j=0;j<5;j++){
            for(k=0;k<2;k++){
                total+=Aa[i][k]*Bb[k][j];
            }
            Cc[i][j]=total;
            total=0;
        }
    }
    
    for(i = 0; i < 4; i++){
        for (j = 0; j< 5; j++){
            *value = Cc[i][j];
            sleep(1);
            printf("%d\t", Cc[i][j]);
        }
        printf("\n");
    }
    
    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
    
    return 0;
}