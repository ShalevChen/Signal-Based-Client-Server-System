//יובל חגבי - 207797424
//חן שלו- 313584906
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/random.h>
void ReadLine(char* buffer, int fd)
{
    int r;
    int i = 0;
    while (1) {
        r = read(fd, &buffer[i], 1);
        if (r < 0) {
            printf("ERROR_FROM_EX2\n");
            exit(-1);
        }
        else if (buffer[i] == ' ') {
            buffer[i] == '\0';break;
        }
        else if (buffer[i] == '\n') {
            buffer[i] = '\0';break;
        }
        else if (r == 0) {
            buffer[i] = '\0';break;
        }
        i++;
    }
}
void handler(){
    int pid= getpid();
    char file[50]="";
    strcat(file,"to_client_");
    int num=pid;
    int counter=0;
    while(num!=0){
        num=num/10;
        counter++;
    }
    char result[counter];
    for(int j=counter-1; j>=0; j--){
        int digit=pid%10;
        pid=pid/10;
        char d = digit +'0';
        result[j]=d;
    }
    result[counter]='\0';
    strcat(file,result);
    strcat(file,".txt");
    int fd=open(file,O_RDONLY);
    if(fd<0){
        printf("ERROR_FROM_EX2\n");
		exit(-1);
    }
    char solution[50]="";
    ReadLine(solution,fd);
    printf("The solution is: %s\n",solution);
    close(fd);

   int exam=fork();//close all the txtfies
   if(exam==0){
     char* bf[]={"rm",file,NULL};
     execvp("rm",bf);
   }
   else wait(NULL);
}

void error(){
  printf("Cannot divide by zero\n");
  return;
}

void main(int argc, char* argv[]) {
    int i,fd1;
    if(argc!=5){
        printf("ERROR_FROM_EX2\n");
		exit(-1);
    }
	if (atoi(argv[3])<1 || atoi(argv[3])>4) {
        printf("ERROR_FROM_EX2\n");
		exit(-1);
	}
    signal(3,error);
    signal(2,handler);
    int *buf;
    for(i=0; i<10; i++){
        fd1=open("to_srv.txt",O_CREAT | O_RDONLY | O_WRONLY, 0777);
        if(fd1<0){
            int x=getrandom(buf,sizeof(buf),0);
            sleep(x%6);
        }
        else break;
    }
    if(i==10){
        printf("Cannot connect to server.exe");
    }
    int pid= getpid();
    int num=pid;
    int counter=0;
    while(num!=0){
        num=num/10;
        counter++;
    }
    char result[counter];
    for(int j=counter-1; j>=0; j--){
        int digit=pid%10;
        pid=pid/10;
        char d = digit +'0';
        result[j]=d;
    }
    write(fd1,result,counter);
    write(fd1,"\n",strlen("\n"));
    write(fd1, argv[2],strlen(argv[2]));
    write(fd1,"\n",strlen("\n"));
    write(fd1, argv[3],strlen(argv[3]));
    write(fd1,"\n",strlen("\n"));
    write(fd1, argv[4],strlen(argv[4]));
    close(fd1);
    kill(atoi(argv[1]),1);
    pause();
}
