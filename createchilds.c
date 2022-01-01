#include "create.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include<sys/wait.h>
#include <stdio.h>
#include<signal.h>
#include <unistd.h>
#include<stdbool.h>
#include<stdlib.h>
int *queue;
int *cnt1;
int *cnt;
int *i;
int createChilds(int oddChild,int evenChild,int curLevel,int Maxlevel, int isMainChanged, int isChildChanged){   /*  isMainChanged isChildChanged returns 1 or 0 (boolean variables ) */
	if(curLevel < Maxlevel){
		int mainpid,pid,child,ppid = getpid();
		if(getpid()%2 == 0 ){
			child = evenChild;
		}else{
			child = oddChild;
		}
		*i = 0;
		for(*i ; *i < child; *i = *i + 1){
			mainpid = getpid();
			pid=fork();
			kill(mainpid,SIGSTOP);	        /*We are Stopping Parent for just a moment and push the child into queue and then start parent and stop that child */
			int count=0;
			if (pid < 0)                      	/* Pid negative indicates fork failure */
			{
				fprintf(stderr, "Fork Failed");
				return -1;
			}
			else if (pid == 0 )     		/* Child Enters here */
			{
				queue[*cnt] = getpid();    	/* Pushing Child Into the queue */
				*cnt = *cnt + 1;
			printf("PID=%d PPID=%d \n",getpid(),getppid());
				kill(mainpid,SIGCONT);      	/* After Pushing child into the queue, We Then continue parent and then stop this child */
				kill(getpid(),SIGSTOP);
				break;                  /* This break is used because to prevent siblings from changing the shared value of i so that it doesn't create extra child as i will be affected */
			}
			else
			{
			  // printf("PId=%d PPID=%d \n",getpid(),getppid());     /* This Generally is not required because every node except root becomes child to some node */
			}
		}
		if( getpid() == ppid ){
			isMainChanged = 1;       /* This variable is used to verify if the parent process has been changed i.e after Creating all childs in the next level then new parent becomes the next level one */
		}
		else{
			isMainChanged = 0;
		}
		if(!isMainChanged && !isChildChanged){ 	/* isChildchanged variable indicates if the executing child is finished and next child is about to execute */
			return createChilds(oddChild,evenChild,curLevel+1,Maxlevel,!isMainChanged,isChildChanged);
		}

	}
	return curLevel+1;
}
