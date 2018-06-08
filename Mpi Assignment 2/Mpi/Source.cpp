#include<mpi.h>
#include <stdio.h>
#include<iostream>
#include <time.h>
using namespace std;
#define N 3
#define Max_Values 10
MPI_Status status;
int a[N][N], b[N][N], c[N][N];
int main(int argc, char **argv)
{
	int numtasks, taskid, numworkers, source, rows, offset;
	MPI_Init(&argc, &argv);
	taskid = MPI::COMM_WORLD.Get_rank();
	numtasks = MPI::COMM_WORLD.Get_size();
	numworkers = numtasks - 1;
	if (taskid == 0) 
	{
		srand(time(NULL));
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				a[i][j] = rand()%Max_Values;
				b[i][j] = rand() % Max_Values;
			}
		}
		cout << "The First Matrix:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << "The Second Matrix:" << endl;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				cout << b[i][j] << " ";
			}
			cout << endl;
		}
		rows = N / numworkers;
		offset = 0;
		for (int i= 1; i <= numworkers; i++)
		{
			MPI::COMM_WORLD.Send(&offset, 1, MPI::INT, i, 1);
			MPI::COMM_WORLD.Send(&rows, 1, MPI::INT, i, 1);
			MPI::COMM_WORLD.Send(&a[offset][0], rows*N, MPI::INT, i, 1);
			MPI::COMM_WORLD.Send(&b, N*N, MPI::INT, i, 1);
			offset = offset + rows;
		}
		for (int i = 1; i <= numworkers; i++)
		{
			source = i;
			MPI::COMM_WORLD.Recv(&offset, 1, MPI::INT, source, 2);
			MPI::COMM_WORLD.Recv(&rows, 1, MPI::INT, source, 2);
			MPI::COMM_WORLD.Recv(&c[offset][0], rows*N, MPI::INT, source, 2);
		}
		cout<<"The result matrix:" << endl;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
			{
				cout << c[i][j] << " ";
			}
			cout << endl;
		}
	}
	if (taskid > 0) 
	{
		source = 0;
		MPI::COMM_WORLD.Recv(&offset, 1, MPI::INT, source, 1);
		MPI::COMM_WORLD.Recv(&rows, 1, MPI::INT, source, 1);
		MPI::COMM_WORLD.Recv(&a, rows*N, MPI::INT, source, 1);
		MPI::COMM_WORLD.Recv(&b, N*N, MPI::INT, source, 1);
		for (int k = 0; k < N; k++)
		{
			for (int i = 0; i < rows; i++)
			{
				c[i][k] = 0;
				for (int j = 0; j < N; j++)
				{
					c[i][k] = c[i][k] + a[i][j] * b[j][k];
				}
			}
		}
		MPI::COMM_WORLD.Send(&offset, 1, MPI::INT, 0, 2);
		MPI::COMM_WORLD.Send(&rows, 1, MPI::INT, 0, 2);
		MPI::COMM_WORLD.Send(&c, rows*N, MPI::INT, 0, 2);
	}
	MPI_Finalize();
}