#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h> 
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

void *thread(int temp) {
    int i, ans=0;
    for (i=0;i<=temp;i++) ans+=i;
    printf("%d", ans);
}

int main (int argc, char* argv[]) {
    int temp, i;
    pthread_t tid[20];
    key_t key = 1234;
    int *value;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);
    
    for(i=0;i<20;i++){
        temp=*value;
        pthread_create(&(tid[i]), NULL, &thread, (void*)temp);
        sleep(1);
        if(i%5==4){
            printf("\n");
        }
        else{
            printf("\t");
        }
    }
    
    for(i=0; i<20; i++){
        pthread_join(tid[i], NULL);
    }
    
    shmdt(value);
    shmctl(shmid, IPC_RMID, NULL);
}