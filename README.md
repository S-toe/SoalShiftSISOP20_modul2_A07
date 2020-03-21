# SoalShiftSISOP20_modul2_A07

## Daemon dan Proses

## 1. Soal 1
```
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.
```
Dalam pengerjaannya saya membuat sebuah file script .c yang akan membuat daemon proses sebagai berikut :

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <regex.h>


int main(int argc,char* argv[]) {

	time_t now;//variabel untuk waktu
  struct tm* local;
  char** argu = argv;
  // argu[4]="pant";
  regex_t banding;//membuat variabel banding dengan tipe data regex_t
  int flag=0;
  int return1,return2;
regcomp(&banding,"/home/stoe/",0);//menyimpan path kedalam variabel banding
  // printf("%s %d\n",argu[4],return1);
  return1=regexec(&banding,argu[4],0,NULL,0);//membandingkan argument path dengan isi dari banding
  // printf("%s %d\n",argu[4],return1);
regcomp(&banding,".sh",0);//menyimpan path kedalam variabel banding
  // printf("%s %d\n",argu[4],return2);
  return2=regexec(&banding,argu[4],0,NULL,0);//membandingkan argument path dengan isi dari banding
  // printf("%s %d\n",argu[4],return2);

  // int z=strcmp(13,"0");
  // printf("%d %d %d\n",a,b,c);
  //cek apakah argument yang diinputkan sesuai dengan perintah soal.
  if (((strcmp(argu[1],"0")>=0) && (strcmp(argu[1],"59")<=0)) || (strcmp(argu[1],"*")==0)){
    if(((strcmp(argu[2],"0")>=0) && (strcmp(argu[2],"59")<=0)) || (strcmp(argu[2],"*")==0)){
      if(((strcmp(argu[3],"0")>=0) && (strcmp(argu[3],"23")<=0)) || (strcmp(argu[3],"*")==0)){
        if(return1==0 && return2==0) 
          flag=1;
      }
    }
  }

  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal1")) < 0) {
//chdir dibuat full path agar dapat mengakses file diary.txt
    exit(EXIT_FAILURE);
  }

 close(STDIN_FILENO);
 close(STDOUT_FILENO);
 close(STDERR_FILENO);
// if(argu[1]>=0 && argu
  if(flag==0) printf("error");
  // int C=1;
  while (flag==1) {

    pid_t id;
  //   id = fork();
  //   if (id < 0) {
  //   exit(EXIT_FAILURE);
  // }

    time(&now);//menyimpan waktu kedalam variabel
	  local = localtime(&now);//menyimpan waktu kedalam struct local
	  int time_H=(local->tm_hour);//jam
	  int time_M=(local->tm_min);//mnt
	  int time_S=(local->tm_sec);//detik

    //mengubah argument char menjadi int
    int a=atoi(argu[1]);
    int b=atoi(argu[2]);
    int c=atoi(argu[3]);
    // C++;
    int flag2=0;
  
  if(strcmp(argu[1],"*")==0){
    // pid = fork();
    // if (pid < 0) {
    //   exit(EXIT_FAILURE);
    // }
    if(time_M==b){
      if(time_H==c){
        // printf("ini * M H\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
      else if(strcmp(argu[3],"*")==0){
        // printf("ini * M *\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
    }
    else if(strcmp(argu[2],"*")==0){
      if(time_H==c){
        printf("ini * * H\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
      else if(strcmp(argu[3],"*")==0){
        // printf("ini * * *\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
    }  
  }

  else if(time_S==a){
    if(time_M==b){
      if(time_H==c){
        // printf("ini S M H\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
      else if(strcmp(argu[3],"*")==0){
        // printf("ini S M *\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
    }
    else if(strcmp(argu[2],"*")==0){
      if(time_H==c){
        // printf("ini S * H\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
      else if(strcmp(argu[3],"*")==0){
        // printf("ini S * *\n");
         pid_t id;
         pid = fork();
         if (pid < 0) {
          exit(EXIT_FAILURE);
         }
        flag2=1;
      }
    }
  }
  

  //  printf("pp");
  if(flag2==1 && pid == 0){
    char *argv[3] = {"Bro", argu[4], NULL};
    execv("/bin/bash", argv);
  }
	// printf ("%s %s %s %s %d\n flag=%d\n", argu[2],argu[4], argu[1], argu[3], time_H, flag);
    sleep(1.0);//delay 1s
  }
  
}

```
Dalam script kita membuat sebuah daemon proses yang akan menjalankan bash script layaknya crontab. Argumen yang diinputkan saya cek dengan regex agar sesuai pada argumen 4. untuk argumen lainnya saya menggunakan command if biasa untuk mengeceknya.

didalam looping atau saat daemon berjalan, proses akan mengecek kembali argumen berupa * atau angka agar berjalan sesuai jadwalnya.

Berikut gambar ketika programnya dijalankan:


## 2. Soal 2

```
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].
b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah

detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk

menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()
```
Dalam pengerjaannya saya kembali membuat sebuah file script .c yang akan membuat daemon proses sebagai berikut :

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void Bunuh(char* kill){
  FILE *killer;
  printf("1%s\n",kill);
  killer = fopen("/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal2/killer","w+");
  if(strcmp(kill,"-a")==0){
    fprintf(killer,"#!/bin/bash\npkill -9 -P %d\nkill -9 %d\nrm -- \"$0\"", getpid(), getpid());
  printf("2%s\n",kill);
  }
  else if(strcmp(kill,"-b")==0){
  // printf("3%s\n",argv[1]);
    fprintf(killer,"#!/bin/bash\nkill -9 %d\nrm -- \"$0\"", getpid());
  }
  else{ 
  printf("%s5\n",kill);
    exit(1);
  }
  // printf("%s4\n",argv[1]);
  fclose(killer);
}

int main(int argc, char* argv[]) {
  int i,wkt;
  time_t now,waktu;
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
 
 
  Bunuh(argv[1]);
  while (1) {
    // Tulis program kalian di sini
    printf("parent\n");
    time(&now);
    struct tm *local = localtime(&now);
    char tmppath[100] = "/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal2/";// array untuk menyimpan path
    // char dir[100];//dibuat array untuk menyimpan waktu
    char dirname[100];//dibuat array untuk menyimpan waktu
    char dirname2[100];//dibuat array untuk menyimpan waktu
    strftime(dirname, 100, "%G-%m-%d_%H:%M:%S", local);//waktu disimpan kedalam array
    char *pathname = strcat(tmppath, dirname);// membuat variabel yang berisi gabungan array pertama dan kedua.
    char pathname2[1024];
    char zip[1024];
    strcpy(pathname2,pathname);
    strcpy(zip,dirname);
    strcat(pathname,"/");
    if(fork()==0){
    printf("anak proses1\n");
      int status;
      if(fork()==0){
    printf("anak proses2\n");
        char *argu[] = {"mkdir", "-p", pathname, NULL};//membuat array yang menyimpan perintah membuat direktori
        execv("/bin/mkdir", argu);//mengeksekusi layaknya diterminal
      }
      while ((wait(&status)) > 0);
    printf("anak proses3\n");
      for(i=0 ; i<=20 ; i++){
        // dirname2=dirname;
        if(i==20){
          int tunggu;
          if(fork()==0){
          pathname[strlen(pathname)-1]=0;
          // zipname[strlen(zipname)-1]=0;
          char *zipname=strcat(pathname2,".zip");
          // strcat(zipname,".zip");
          // printf("aaaaaaaaa %s %s\n",zipname,pathname);
          char *argu[] = {"ZIP","-rm" ,"-j", zipname, pathname, NULL};//membuat array yang menyimpan perintah membuat direktori
          execv("/usr/bin/zip", argu);//mengeksekusi layaknya diterminal
          }
          else{
            while ((wait(&tunggu)) > 0);
            char *argu[] = {"ZIP","-d",pathname, NULL};//membuat array yang menyimpan perintah membuat direktori
          execv("/bin/rm", argu);//mengeksekusi layaknya diterminal
          }
        }
        char arr[100];
        time(&waktu);
        wkt= waktu%1000 + 100;
        // printf("%s\n",dirname);
        local=localtime(&waktu);
        char tmppath[100] = "/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal2/";// array untuk menyimpan path
        strftime(dirname2, 100, "%G-%m-%d_%H:%M:%S", local);
        // char *path = strcat(dirname,dirname2);
        char *path1= strcat(tmppath,dirname);
        strcat(path1,"/");
        strcat(path1,dirname2);
        // path=strcat(path,dirname2);
        sprintf(arr,"https://picsum.photos/%d",wkt);
        // printf("%s\n",arr);
        if(fork()==0){
         printf("anak proses4 %s\n",path1);
          printf("p%s\n",path1);
          char *argu[] = {"wget", arr, "-O", path1, NULL};//membuat array yang menyimpan perintah membuat direktori
          execv("/usr/bin/wget", argu);//mengeksekusi layaknya diterminal

        }
        // memset(path, 0, sizeof path);
        // memset(path1, 0, sizeof path1);
        // path1=pathname;
        sleep(5);
      }
    }
    sleep(30);
  }
}
```

Dalam program c ini kita membuat daemon proses yang akan membuat folder, lalu mendownload gambar kedalamnya sampai 20 kemudian foldernya di zip dengan menghapus folder yang di zip. Prosesnya berjalan secara bersamaan, sehingga masing-masing folder memiliki fungsi downloadnya sendiri.

Disini parent akan di looping untuk melakukan hal berikut dengan delay 30s 
Membuat anak proses 1, lalu membuat anak proses 2 untuk membuat folder.. anak proses 1 diwait agar folder dibuat terlebih dahulu, kemudian anak proses 1 membuat anak proses lagi anak proses 3 yang tugasnya buat download nantinya.. Nah jadi saya buat looping sampai 20x kemudian setelah itu foldernya di zip dengan memanggil exec oleh anak proses 1.

Untuk membuat script killernya, saya membuat ketika argument yang diberikan diinput benar, sehingga akan membuat script killer yang dibuat sebelum memasuki looping daemon proses.

Berikut gambar ketika program dijalankan:



## 3. Soal 3

```
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.
c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.
d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk
```

Dalam pengerjaannya saya tidak menggunakan daemon, hanya menggunakan fork dan exec saja, kemudian ditambah fungsi find dengan program sebagai berikut:

```c
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>

int main() {
  pid_t child_id,cid,cid2;
  int status;

  child_id = fork();
  
  if (child_id < 0) {
    exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
  }

  if (child_id == 0) {
    // this is child
    if(fork()==0){
    char *argv[] = {"mkdir", "-p", "indomie", NULL};
    execv("/bin/mkdir", argv); 
    // printf("pertama");
    }
    int status2;
    cid=fork();
    if(cid==0){
    sleep(5);
    char *argv[] = {"mkdir", "-p", "sedaap", NULL};
    execv("/bin/mkdir", argv);
    printf("pertama2");
    }
    else{
     while ((wait(&status2)) > 0);
        int status4;
        if(fork()==0){
         char *argv[] = {"unzip", "jpg.zip", NULL};
         execv("/usr/bin/unzip", argv);
        }
        else{
            while ((wait(&status4)) > 0);
        int status3;
        cid2=fork();
        if(cid2==0){
         char *argv[] = {"find1", "./jpg/","-type", "f", "-exec", "mv", "-f", "{}", "/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal3/sedaap/", ";", NULL};
         execv("/usr/bin/find", argv);
        }
        else{
         while ((wait(&status3)) > 0);
        char *argv[] = {"find2", "./jpg/", "-mindepth", "1", "-depth", "-type", "d", "-exec", "mv", "{}", "/home/stoe/Downloads/SoalShiftSISOP20_modul2_A07-master/soal3/indomie/", ";", NULL};
         execv("/usr/bin/find", argv);

    printf("pertama3");
        }
    }
    }
  } 
  
  else {
    // this is parent
    int tunggu;
    while ((wait(&status)) > 0);
    printf("pertamaparent");
    if(fork()==0){
    char *argv[] = {"find3", "./indomie/", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba1.txt", ";", NULL};
    execv("/usr/bin/find", argv);
    }
    else{
      while ((wait(&tunggu)) > 0);
      sleep(3);
      char *argv[] = {"find3", "./indomie/", "-mindepth", "1", "-type", "d", "-exec", "touch","{}/coba2.txt", ";", NULL};
      execv("/usr/bin/find", argv);
    }
  }
}
```

Dalam pengerjaannya saya membuat anak proses yang akan membuat folder indomie dan sedaap yang berselang selama 5 detik, kemudian membuat anak proses lagi yang akan meng-unzip file zip yang telah diberikan

Setelah proses unzip selesai, saya membuat 2 anak proses lain yang akan mencari semua file dan folder dalam folder hasil unzip sebelumnya. Dengan menggunakan exec dan fungsi find saya dapat memisahkan sekaligus memindahkan file dan folder.

Setelah pemisahan selesai saya proses terakhir yang sedang berjalan membuat anak baru yang akan membuat file txt pertama dan proses yang berjalan terakhir akan membuat file txt yang kedua.

Berikut gambar saat proses dijalankan :