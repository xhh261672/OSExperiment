#include <windows.h>
#include <stdio.h>

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

DWORD WINAPI cal(LPVOID param)
{
	data *loc = (data *)malloc(sizeof(data));
	loc = (data *)param;
	int i = loc->i;
	int j = loc->j;
	int n;
	for (n = 0; n< N; n++)
		m3[i][j] += m1[i][n] * m2[n][j];
	return 0;
}

int main(int argc, char const *argv[])
{
	int i, j;
	DWORD ThreadId;
	HANDLE ThreadHandle[M*T];
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
	for (i = 0; i< M; i++){
		for (j = 0; j<T; j++){
			data *param = (data *)malloc(sizeof(data));
			param->i = i;
			param->j = j;
			ThreadHandle[i*T + j] = CreateThread(
				NULL,
				0,
				cal,
				param,
				0,
				&ThreadId);
		}
	}
	WaitForMultipleObjects(M*T, ThreadHandle, TRUE, INFINITE);
	for (i = 0; i< M*T; i++)
		CloseHandle(ThreadHandle[i]);
	printf("%s\n", "m3=m1*m2:");

	for (i = 0; i<M; i++){
		for (j = 0; j<T; j++){
			printf("%d\t", m3[i][j]);
		}
		printf("\n");
	}

	return 0;
}
