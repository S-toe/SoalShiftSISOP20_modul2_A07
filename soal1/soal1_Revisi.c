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
