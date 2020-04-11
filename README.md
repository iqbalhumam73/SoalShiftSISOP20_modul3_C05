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



### no 4
## 4a
```
#define NUM_THREADS 4 * 5


int (*value)[10];

int Aa[4][2] = {{2,1},
               {3,1},
               {1,4},
               {2,1}
              };
int Bb[2][5] = {{2,2,1,3,1}, 
               {2,1,3,1,2}
              };
```
deklarasi matriks yang selanjutnya akan dipakai

```
struct v
{
	int i; /* row */
	int j; /* column */
};
```
Pembuatan struct untuk melkaukan passing data ke thread

```
key_t key = 1234;
    int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
```
Inisiasi shared memory menggunakan template dari modul

```
for (i=0; i < 4; i++)
	{
		for (j = 0; j < 5; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			pthread_create(&workers[thread_counter], NULL, runner, data);
			pthread_join(workers[thread_counter], NULL);
			thread_counter++;
		}
	}
```
Pembuatan thread dengan looping sebanyak 20x mengikuti jumlah elemen pada array hasil (Cc)

```
void *runner(void *ptr)
{	
	struct v *data = ptr;
	int i, sum = 0;
	
	for(i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	value[data->i][data->j] = sum;
	pthread_exit(0);
}
```
Thread nya berguna untuk casting parameter ke struck v dan juga melakukan perhitungan perkalian matriks.


### 4b
```
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
pthread_t thread1;
```
Membuat terminasi thread dan juga melakukan join thread sehingga thread berjaan sampai selesai

```
 key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
```
inisiasi shared memory dengan template yang ada di modul

```
int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", value[i][j]);
		}
		printf("\n");
	}
```
Melakukan print matriks yang diambil dari soal 4a

```
int buat_thread;
	buat_thread = pthread_create(&thread1, NULL, buat_factorial, NULL);
	pthread_join(thread1,NULL);
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%llu\t", hasil_factorial[i][j]);
		}
		printf("\n");
	}

```
Melakukan print matriks hasil pertambahan menurut soal 4b

```
void *buat_factorial()
{
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);

	int i,j,k;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			unsigned long long f=1;
			for(k=1;k<=value[i][j];k++)
			{
				f= f+k;
				hasil_factorial[i][j] = f-1;
			}
		}
	}
}
```
Pembuatan fungsi thread untuk melakukan penambahan masing masing elemen

### 4c
```
int p[2];
  pipe(p);
  int pid = fork();
```
Deklarasi fork dan pipe yang akan digunakan

```
if (pid == 0)
    {
      // p[0] read
      dup2(p[0], 0);
      close(p[1]);
      char *argv[] = {"wc", "-l", NULL};
      execv("/usr/bin/wc", argv);
    }
```
Pada Fork, parent process menerima inputan dari child process yang dihubungkan dengan pipe

```
 else //child
    { 
      //p[0] write
      dup2(p[1], 1);
      close(p[0]);
      char *argv[] = {"ls", NULL};
      execv("/bin/ls", argv);
    }
```
Child process menampilkan ls 
