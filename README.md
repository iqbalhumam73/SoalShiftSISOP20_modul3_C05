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

---
