#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<sys/stat.h>

#define SIZE 200

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

void* makefile(void *ext){

} 

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

    char save[argc];
    //get argument
    if ( strcmp(argv[1],"-f")== 0)
    {
        /* code */
        printf("oyi\n");
    }
    else if (strcmp(argv[1],"-d")== 0)
    {
        /* code */
    }
    else if (strcmp(argv[1],"*")== 0)
    {
        /* code */
    }
    
    pthread_t tid[argc-2];
    
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
        printf("%s\n",save_ext);
        pthread_create(&tid[i],NULL,makefile,(void*) ext+1);
        
        /*
        int start,last;
        start = cek_slash(argv[i]);
        last = cek_dot(argv[i]);
        printf("%s")
        */

       
    }
    

}




void _print(){



}