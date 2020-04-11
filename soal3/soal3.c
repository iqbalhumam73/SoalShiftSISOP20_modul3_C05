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

pthread_t tid[3];

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
    else if (strcmp(argv[1],"-d")== 0){

        printf("Masuk ke -d\n");
        
        char path1[200],path2[200];
        DIR *dir; //pointer yang menunjuk ke direktori
        struct dirent *de;  //membaca file yang terdapat pada direktori
        dir = opendir(argv[2]); 
        int test = 0, i =0;
        if(dir == NULL) printf("Error!\n");
        else if(!dir) printf("Periksa lagi, apakah direktori tersebut ada?\n");
         // loop ketika sebuah direktori ada file/folder didalamnya
        while( (de=readdir(dir)) )
        {
            if ( !strcmp(de->d_name, ".") || !strcmp(de->d_name, "..") ); 
		//namafile
            printf("%s\n",de->d_name);
            strcpy(path1,argv[2]); //copy string ke variabel path1
            strcat(path1,"/"); //menyambungkan perargumennya
            strcat(path1,de->d_name); 
            if(de->d_type == 8){
            pthread_create(&(tid[i]),NULL,makeit,path1); //membuat thread
            pthread_join(tid[i],NULL);
            i++;
            }
        }
         printf("SELESAI\n");
    }
    else if (strcmp(argv[1],"*")== 0){

        printf("Masuk ke *\n");
        DIR *dir;
        struct dirent *de; //membaca file yang terdapat pada direktori
        char path1[100],path2[100];
        dir = opendir(current_dir); //membuka direktori yang sekarang
        int test = 0, i =0;
        if(dir == NULL) printf("Error!\n");
       else if(!dir) printf("Periksa lagi, apakah direktori tersebut ada?\n");
        // loop ketika sebuah direktori ada file/folder didalamnya
        while ((de=readdir(dir)) )
        {
            if ( !strcmp(de->d_name, ".") || !strcmp(de->d_name, ".."));
             //lanjutkan
            printf("%s \n",de->d_name); //nama file
            strcpy(path1,current_dir); //copy string ke variabel path1
            strcat(path1,"/"); 
            strcat(path1,de->d_name);
            if(de->d_type == 8){
                //membuat thread
            pthread_create(&(tid[i]),NULL,makeit,path1); 
            pthread_join(tid[i],NULL);
            i++;
            }
        }
        
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

    DIR *fold; //pointer yang menunjuk ke folder/direktori
    struct dirent *de1;
    char place1[100],place2[100];
    fold = opendir(current_dir); //open direktori saat ini
    int test = 0;
    //printf("a = %d\n", a);
    if(a>1){

        if(fold == NULL) printf("Error!\n");
           else if(!fold)
            printf("Periksa lagi, apakah direktori tersebut ada?\n");
        // loop ketika sebuah direktori ada file/folder didalamnya
        while( (de1=readdir(fold)) )
        { 
            if(strcmp(de1->d_name,abc) == 0 && de1->d_type == 4){
                test = 1;
                break;
            }
        }

        if(test == 0){
            //menyusun direktori lokasi file
            strcpy(place1,current_dir);
            strcat(place1,"/");
            strcat(place1,abc);
            //memberitahu lokasi file
            printf("Berada di = %s\n%s\n",abc,place1);
            printf("SELESAI\n");
            mkdir(place1, 0777);
        }
    }

    else{
        //apabila file tidak ada ekstensi 
        //memberitahu lokasi file 
        strcpy(place1, current_dir); //direktori sekarang
        strcat(place1,"/");
        strcat(place1,"Unknown"); 
        printf("Berada di = %s\n%s\n",abc,place1);
        printf("SELESAI\n");
        mkdir(place1, 0777);
    }


   char sumber[1024], tujuan[1024];
    //lokasi file
    strcpy(sumber,arg);
    strcpy(tujuan,current_dir);
    strcat(tujuan,"/");
    //jika tidak ada ekstensi
    if(a== 1) strcat(tujuan,"Unknown");
    //memiliki ekstensi 
    else strcat(tujuan, abc);
    strcat(tujuan,"/");
    strcat(tujuan,arr3);
    rename(sumber,tujuan);
    a = 0;
    b = 0;
	return NULL;
}

