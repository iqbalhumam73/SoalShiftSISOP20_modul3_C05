# SoalShiftSISOP20_modul3_c05

---
### NO.3
Berdasarkan soal nomer 3 kita dituntut untuk membuat sebuah program dari C untuk mengkategiirikan sebuah file. Program ini akan           memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.
Dalam program tersebut terdapat sebuah opsi yang terdiri dari `-f` `-d` `*` 
● Semisal program dijalankan:
```  
  # File kategori terletak di /home/izone/kategori
  $ ./kategori -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
    
  #Hasilnya adalah sebagai berikut
  /home/izone
  |-jpg
  |--file1.jpg
  |-c
  |--file2.c
  |-zip
  |--file3.zi
    
  ● Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa
    dikategorikan sebanyak yang user inginkan seperti contoh di atas.
  ● Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual,
    melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,
    maka dia akan disimpan dalam folder “Unknown”.
  ● Program kategori ini juga menerima perintah (*) seperti di bawah;
  
  $ ./kategori \*
    
  ● Artinya mengkategori seluruh file yang ada di working directory ketika
    menjalankan program C tersebut.
  ● Selain hal itu program C ini juga menerima opsi -d untuk melakukan kategori
    pada suatu directory. Untuk opsi -d ini, user hanya bisa menginput 1 directory
    saja, tidak seperti file yang bebas menginput file sebanyak mungkin.

  $ ./kategori -d /path/to/directory/
  
  ● Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan
    hasilnya akan disimpan di working directory di mana program C tersebut
    berjalan (hasil kategori filenya bukan di /path/to/directory).
  ● Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau
    menggunakan (*) terdapat folder yang berisi file, maka file dalam folder
    tersebut tidak dihiraukan, cukup file pada 1 level saja.
  ● Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan
    secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang
    juga menggunakan fork-exec dan system.
 ```
 
> Pembahasan -f

**Source code**
```
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
```
- pada argumen -f maka setiap file yang di inputkan pada argumen maka akan membuat thread bagi masing2 file dan menjalankannya

> pembahasan -d

**Source code**
```
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
```

`DIR *dir;` adalah pointer yang menunjuk ke direktori
 
`dir = opendir(current_dir)` untuk membuka direktori yang sekarang.
 
`while( (de=readdir(dir)) )` adalah looping ketika dalam direktori tersebut ada file/folder didalamnya
 
`strcpy(path1,argv[2]);` merupakan peng-copy-an string argumen kedua (direktori) ke variabel path1

`if(de->d_type == 8)` adalah pengecekan apakah typenya termasuk file atau bukan (tipe file =8, folder=4). Jika benar, maka dibuatkan thread menuju fungsi makeit

>pembahasan "*"

**Source code**
```
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
```
`strcpy(path1,curr_dir);` untuk copy string cwd ke variabel path1

`if(de->d_type == 8)` adalah pengecekan apakah typenya termasuk file atau bukan (tipe file =8, folder=4). Jika benar, maka dibuatkan thread menuju makeit

**Pembahasan fungsi _makeit_**

```
Source code
void* makeit(void *arg){
    //copy string ke variabel huruf
    // int a = 0, b = 0;
    int i=0;
    strcpy(huruf,arg);
    char *tanda, *tanda1;
    tanda1 = strtok(huruf, "/"); //memisahkan string dari karakter (huruf) dengan / sebagai titik pemisahan
    while( tanda1 != NULL ) {
        //membaca string
        arr2[b] = tanda1; b++;
        tanda1 = strtok(NULL, "/"); //mendapatkan nama file
    }
    strcpy(arr3, arr2[b-1]);
    tanda = strtok(arr2[b-1], "."); //memisahkan string dari karakter (arr) dengan . sebagai titik pemisahan
    while( tanda != NULL ) {
        //membaca string
        arr[a] = tanda; a++;
        tanda = strtok(NULL, "."); //memisahkan string dengan . sebagai titik pemisahan dan mendapatkna ekstensi file
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

```

```
strcpy(huruf,arg);
    char *tanda, *tanda1;
    tanda1 = strtok(huruf, "/"); //memisahkan string dari karakter (huruf) dengan / sebagai titik pemisahan
    while( tanda1 != NULL ) {
        //membaca string
        arr2[b] = tanda1; b++;
        tanda1 = strtok(NULL, "/");
    }
```
- code diatas berfungsi untuk mendapatkan nama file

```
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
```
- source code diatas guna mendapatkna ekstensi dari file yang ada dan mengatasi case sensitif misal terdapat ekstensi dengan huruf besar atau kecil akan dianggap sama misal .jpg == .JPG

```
  while( (de1=readdir(fold)) )
        { 
            if(strcmp(de1->d_name,abc) == 0 && de1->d_type == 4){
                test = 1;
                break;
            }
        }
```
adalah untuk memeriksa bahwa apakah file tersebut sudah benar ada di folder terkait atau apakah tipenya adalah folder. Jika iya, maka tandai test = 1 dan lewati.

```
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
```
adalah apabila file tersebut berekstensi, maka nantinya juga akan dibuatkan folder sesuai ekstensi file tersebut. 

```
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

```
adalah untuk file tanpa ekstensi, nantinya akan dimasukkan di folder Unknown.

`curr_dir` dicopy ke variabel `place1` untuk disusun direktorinya

`0777` menandakan file permission 

`abc` adalah ekstensi dan `place1` letak file tersebut secara lengkap 


- Kemudian untuk move file, praktikan menggunakan fungsi rename. Dengan code seperti dibawah ini.

```
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
```
---
