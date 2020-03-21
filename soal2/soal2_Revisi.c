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
    printf("anak1\n");
      int status;
      if(fork()==0){
    printf("anak2\n");
        char *argu[] = {"mkdir", "-p", pathname, NULL};//membuat array yang menyimpan perintah membuat direktori
        execv("/bin/mkdir", argu);//mengeksekusi layaknya diterminal
      }
      while ((wait(&status)) > 0);
    printf("anak3\n");
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
         printf("anak4 %s\n",path1);
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