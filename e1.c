#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_SEQUENCE 10

int main(int argc, char const *argv[])
{
	typedef struct 
	{
		long fib_sequence [MAX_SEQUENCE];
		int sequence_size;
	} share_data;

	share_data *shdat ;
	int segment_id = shmget(IPC_PRIVATE,sizeof(shdat),S_IRUSR | S_IWUSR);
	char *shmaddr = (char*)shmat(segment_id,NULL,0);
	int sq_size;

	shdat = (share_data *)shmaddr;

	printf("%s\n","input your sequence size\(no more than 10\):  " );
	scanf("%d",&(shdat->sequence_size));
	if(shdat->sequence_size > MAX_SEQUENCE){
		printf("%s\n","your sequence size is too large" );
		return  0;
	}
	// printf("%d\n", sq_size);
	// sprintf(&shdat.sequence_size,&sq_size);
	int pid;

	pid = fork();

	if(pid == 0){
		shdat->fib_sequence[0] = 0;
		shdat->fib_sequence[1] = 1;
		int prev = shdat->fib_sequence[0];
		int succ = shdat->fib_sequence[1];
		int i;
		for(i = 2 ;i < shdat->sequence_size;i++){
			shdat->fib_sequence[i] = prev + succ;
			prev = succ;
			succ = shdat->fib_sequence[i];
			// printf("%d\n",shdat->fib_sequence[i] );
		}
		i = 0;
//		shmdt(shmaddr);
		return 0;

	}

	else if(pid > 0){
		wait(NULL);
		int fib_count;
		fib_count = shdat->sequence_size;
		int i;
		for(i = 0; i< fib_count;i++){
			printf("%d\t", shdat->fib_sequence[i]);
		}
		printf("\n");
		shmdt(shmaddr);
		shmctl(segment_id,IPC_RMID,NULL);
	}


	return 0;
}