#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<dirent.h>
#include<unistd.h>
#include<math.h>
#include<ctype.h>
#include<errno.h>
#include<sys/stat.h>

#define SIZE 200


char huruf[SIZE], current_dir[SIZE];
char *arr[4] ,*arr2[20], arr3[SIZE]; //arr menyimpan ekxstensi arr2 menyimpan nama file
int a=0,b=0;

int cek_slash(char dir[]){
	int n = strlen(dir);
	int start=0;
	int i;
	for(i=0;i<n;i++){
		if(dir[i] == '/'){
			start = i;
		}
	}
	
	return start;
}

int cek_dot(char dir[]){
	int n = strlen(dir);
	int last=0;
	int i;
	for(i=0;i<n;i++){
		if(dir[i] == '.'){
			last = i;
		}
	}
	
	return last;
}

void* makedir(void *ext){
    char dir[SIZE] = "/home/dohan/sisop20/modul3/";
    strcat(dir,ext);
    printf("%s\n",dir);
    int result = mkdir(dir,0700);
}

void* makeit(void *);

// void* movefile()

int cekfile(char dir[]){

  FILE *file;
  if ( file = fopen(dir,"r")){
    fclose(file);
    return 1;
  }

  return 0;
}



int main(int argc, char **argv){
    
    const char ext[SIZE];
    pthread_t tid[argc-2];
    char save[argc];
    int i=0,j=0;

    if (getcwd(current_dir, sizeof(current_dir))!=NULL) printf("Directory sekarang : %s\n" , current_dir);

    
    //get argument
    if ( strcmp(argv[1],"-f")== 0)
    {
        printf("Masuk ke -f\n");
        for( j=2;j<argc;j++){
            pthread_create(&(tid[i]), NULL, makeit, argv[j]);
            pthread_join(tid[i], NULL);
            i++;
        }   
    }
    else if (strcmp(argv[1],"-d")== 0)
    {
        
    }
    else if (strcmp(argv[1],"*")== 0)
    {
        /* code */
    }
    
    
    //get file ext
    for (int i = 2; i < argc; i++)
    {   char save_ext[SIZE];
        // get ext
        char* ext;
        char* p;
        char str[SIZE];
        // char *strcpy(char *ext[argc],char *get_file_ext(char argv[i]);

        strcpy(str,argv[i]);

        ext = strchr(str,'.');
        strcpy(save_ext,ext+1);
        // printf("%s",save_ext);
        pthread_create(&tid[i],NULL,makedir,(void*) ext+1);
        pthread_join(tid[i],NULL);
       
    }
}


void* makeit(void *arg)
{
    //copy string ke variabel huruf
    // int a = 0, b = 0;
    int i=0;
    strcpy(huruf,arg);
    char *tanda, *tanda1;
    tanda1 = strtok(huruf, "/"); //memisahkan string dari karakter (huruf) dengan / sebagai titik pemisahan
    while( tanda1 != NULL ) {
        //membaca string
        arr2[b] = tanda1; b++;
        tanda1 = strtok(NULL, "/");
    }
    strcpy(arr3, arr2[b-1]);
    tanda = strtok(arr2[b-1], "."); //memisahkan string dari karakter (arr) dengan . sebagai titik pemisahan
    while( tanda != NULL ) {
        //membaca string
        arr[a] = tanda; a++;
        tanda = strtok(NULL, "."); //memisahkan string dengan . sebagai titik pemisahan
    }

    char abc[100];
    strcpy(abc,arr[a-1]);
    for(i = 0; abc[i]; i++) abc[i] = tolower(abc[i]); //convert menjadi lowercase letter

    char place1[100],place2[100];

    //menyusun direktori lokasi file
    strcpy(place1,current_dir);
    strcat(place1,"/");
    strcat(place1,abc);
    //memberitahu lokasi file
    printf("Berada di = %s\n%s\n",abc,place1);
    printf("SELESAI\n");
    mkdir(place1, 0777);
    
	

    char sumber[1024], tujuan[1024];
    //lokasi file
    strcpy(sumber,arg);
    strcpy(tujuan,current_dir);
    strcat(tujuan,"/");
    
    //untuk move file dengan rename
    strcat(tujuan, abc);
    strcat(tujuan,"/");
    strcat(tujuan,arr3);
    rename(sumber,tujuan);
    a = 0;
    b = 0;
	return NULL;
}

