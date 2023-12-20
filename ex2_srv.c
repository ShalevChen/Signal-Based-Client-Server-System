
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
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
    char pidclient[50]="";
    char num1[50]="";
    char num2[50]="";
    char action[50]="";
    //printf("num1: %s, num2: %s, action: %s", num1,num2, action);
    int result=0, status, num;
    int fd=open("to_srv.txt",O_RDONLY);
    if(fd<0){
        printf("ERROR_FROM_EX2\n");
        exit(-1);
    }
    ReadLine(pidclient,fd);    //printf("\nThe pid: %s", pidclient);
    ReadLine(num1,fd);
    ReadLine(action,fd);
    ReadLine(num2,fd);
    int exam=fork();
    if(exam < 0){
        printf("ERROR_FROM_EX2\n");
		exit(-1);
    }
    if(exam==0){// son
        char* command = "rm";
        char* arg[] = {"rm", "to_srv.txt", NULL};
        int exe = execvp(command, arg);
        if (exe == -1) {
            printf("ERROR_FROM_EX2\n");
            exit(-1);
        }
    }
    else{
        wait(&status);
    }
    if(atoi(action)==4 && atoi(num2)==0){
       kill(atoi(pidclient),3);
    }
    else{
    switch(atoi(action)){
        case 1: {result=(atoi(num1) + atoi(num2));break;}
        case 2: {result=(atoi(num1) - atoi(num2));break;}
        case 3: {result=(atoi(num1) * atoi(num2));break;}
        case 4: {result=(atoi(num1) / atoi(num2));break;}
    }
    //printf("the result is:%d ",result);*/
    char fileto[50]="";
    strcat(fileto,"to_client_");
    strcat(fileto,pidclient);
    strcat(fileto,".txt");
    int fd1=open(fileto, O_CREAT | O_RDONLY | O_WRONLY, 0777);
    if(fd1<0){
        printf("ERROR_FROM_EX2\n");
        exit(-1);
    }
   char insert[50];
   sprintf(insert,"%d",result);
   write(fd1,insert,strlen(insert));
    //printf("\nThe file name: %s", fileto);*/
/*
    num=result;
    int counter=0;
    while(num!=0){
        num=num/10;
        counter++;
    }

    //printf("\nthe counter:%d ",counter);
    char result1[counter];
    for(int j=counter-1; j>=0; j--){
        int digit=result%10;
        result=result/10;
        char d = digit +'0';
        result1[j]=d;
    }
    result1[counter]='\0';
    //printf("\nthe result:%s ",result1);
    //itoa (result,result1,10);
    write(fd1,result1,counter);
    */
    close(fd1);
    kill(atoi(pidclient),2);
}
}
int main(){
    signal(1,handler);
    while(1){
        pause();
    }
    /*char * argv[4];
    argv[0]="123";
    argv[1]="70";
    argv[2]="1";
    argv[3]="50";*/
    //handler();
   return 0;
}
