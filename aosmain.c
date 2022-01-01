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
#include "createchilds.c"
#include "inorder.c"
int main(int argc, char *argv[]) {
	queue = mmap(NULL, 10000*sizeof(queue), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);   /* Queue Using Shared Memory */
	cnt1 = mmap(NULL, sizeof *cnt1, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);           /* cnt1 indictaes front of the queue and shared variable too */
	cnt = mmap(NULL, sizeof *cnt, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);	      /* cnt indicates Rear of the queue */
	i = mmap(NULL, sizeof *i, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);		      /* i is made shared one because we have to make sure that siblings are created in level wise */
	*cnt = 0;											      /* initially rear is 0 */
	*cnt1 = 0;											      /* initially front is 0 */
	*i = 0;												   /* i becomes 0 for every new level */
	int oddChild = atoi(argv[1]) , evenChild = atoi(argv[2]) , maxLevel = atoi(argv[3]) ;
	int level,childs;
	int pid,stat,k,mainpid = getpid();
	printf("Main Process PID:%d and Its Parent Id:%d \n",getpid(),getppid());
	 level = createChilds( oddChild, evenChild , 0, maxLevel, false , false );
	if(*cnt1<=*cnt){                                      /* when childs are pushed into queue and after parent creates all childs for a particular level,then we execute These childs in the queue */
		if(level>atoi(argv[3])){		      /*This is Executed for the last level only i.e leaves because Before the child stops, its siblings signals SIGCONT, */
			usleep(8000);			      /*Therefore The child will be in block state indefenitely,We use sleep for very short time to prevent this...usleep means sleep in microseconds */
		}
		kill(queue[*cnt1] , SIGCONT); 		     /*Resuming child Execution from the queue */
		*cnt1 = *cnt1 + 1;			     /*incrementing the front pointer of the queue */
	}

	int status,pid1;
	while(pid1=waitpid(0,&status,WUNTRACED | WCONTINUED)!=-1);  /*parent waiting for its child termination */
  	if(getpid()==mainpid){ 					    /* It executes only it is Main Process and executes at the last i.e only if Main Process is remaining */
  		printf("Exit Status: Main Process :%d Exitted \n",getpid());     /*It Indicates Parent is the last process that is exitting. */
  		createNaryTree(queue,*cnt1,*cnt,oddChild,evenChild);
  		munmap(cnt1, sizeof *cnt1);			    /* Unmapping Every Shared Memory Variables */
  		munmap(cnt, sizeof *cnt);
  		munmap(i, sizeof *i);
  		
	}
	else{
		printf("Exit Status: Process: %d Exitted \n",getpid());
	}

	if(cnt1>cnt)
 		exit(0);

return 0;
}

