#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


#define M 5
#define N 6
#define T 3

int m1[M][N];
int m2[N][T];
int m3[M][T];

typedef struct 
{
	int i;
	int j;
} data;


void * runner(void * param);

int main(int argc, char *argv[])
{
	int i,j;
	printf("%s\n", "m1:");
	for (i = 0; i < M; i++){
		for (j = 0; j<N; j++){
			m1[i][j] = 1;
			printf("%d\t", m1[i][j]);
		}
		printf("\n");

	}
	printf("%s\n", "m2:");
	for (i = 0; i < N; i++){
		for (j = 0; j<T; j++){
			m2[i][j] = 1;
			printf("%d\t", m2[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < M; i++){
		for (j = 0; j<T; j++){
			m3[i][j] = 0;
		}
	}
	pthread_t tid[M*T];
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	for(i = 0; i<M;i++){
		for(j = 0;j<T;j++){
			data *param = (data *)malloc(sizeof(data));
			param->i = i;
			param->j = j;
			pthread_create(&tid[i*T+j],&attr,runner,param);
//			printf("%s\n", "b2");
			pthread_join(tid[i*T+j],NULL);
		}
	}
	printf("%s\n", "m3=m1*m2:");

	for (i = 0; i<M; i++){
		for (j = 0; j<T; j++){
			printf("%d\t", m3[i][j]);
		}
		printf("\n");
	}	return 0;
}

void *runner(void *param)
{
	data *loc = (data *)malloc(sizeof(data));
	loc = (data *) param;
	int i = loc->i;
	int j = loc->j;
	int n;
	for(n=0;n<N;n++)
		m3[i][j] += m1[i][n]*m2[n][j];
	pthread_exit(0);
}