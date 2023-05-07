/*
Operational Systems exam 1 (linux)
This was my solution.
17/20 was the evaluation
(C)2023 Giorgi Gvichiani
*/

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


#define KEY 123 // or wathever
#define SEM_NUM  1 // it is enough;

int main(int argc, char *argv[]){
	int pid = fork(),pid2;
	if(pid==0){
		pid2 = fork();
		int semid;
		struct sembuf sem_con;
		if(pid2 == 0){
			//child2
			printf("child 2 started \n");
			if ((semid = semget(KEY, SEM_NUM, IPC_CREAT|IPC_EXCL|0600)) == -1 ){
				printf ("Error");
				return 0;
			}
			sem_con.sem_num = 0;//we only have one semaphor
			sem_con.sem_op = -1;
			sem_con.sem_flg = SEM_UNDO;
			if((semop(semid,&sem_con,1))==-1){
				printf("EROR\n");
				return 0;
			}
			printf("child 2 started \n");
			exit(execlp("ps","ps",NULL));
			
		}else{
			//child1
			printf("child 1 started \n");
			sleep(10);
			if ((semid = semget(KEY, 0, 0)) == -1 ){
				printf ("Error");
				return 0;
			}
			sem_con.sem_num = 0;
			sem_con.sem_op = 1;
			sem_con.sem_flg = SEM_UNDO;
			if((semop(semid,&sem_con,1))==-1){
				printf("EROR\n");
				return 0;
			}
			sleep(5);
			printf("child 1 finished \n");
		}
		
	}else{
		int status;
		wait(&status);
		printf("parent finished \n");
	}
	
	//printf("Hi %d\n",pid);
}
