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
         char *argv[] = {"unzip","-d", "jpg", "jpg.zip", NULL};
         execv("/usr/bin/unzip", argv);
        }
        else{
            while ((wait(&status4)) > 0);
        int status3;
        cid2=fork();
        if(cid2==0){
         char *argv[] = {"find1", "./jpg/","-type", "f", "-exec", "mv", "-f", "{}", "/home/stoe/PRAKTIKUM/MODUL2/soal3/sedaap/", ";", NULL};
         execv("/usr/bin/find", argv);
        }
        else{
         while ((wait(&status3)) > 0);
        char *argv[] = {"find2", "./jpg/", "-mindepth", "1", "-depth", "-type", "d", "-exec", "mv", "{}", "/home/stoe/PRAKTIKUM/MODUL2/soal3/indomie/", ";", NULL};
         execv("/usr/bin/find", argv);

    printf("pertama3");
        }
    }
    }
  } 
  
  else {
    // this is parent
    while ((wait(&status)) > 0);
    printf("pertamaparent");
    char *argv[] = {"find3", "./indomie/", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba1.txt", "{}/coba2.txt", ";", NULL};
    execv("/usr/bin/find", argv);
  }
}