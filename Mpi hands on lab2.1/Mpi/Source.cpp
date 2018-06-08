#include<mpi.h>
#include <stdio.h>
#include<iostream>
#include <time.h>
using namespace std;
#define ROW 3
#define COL 3
#define MAX_VALUE 10
//mappingToProcessors map to each task to which process to do it.
int mappingToProcessors(int i, int size)
{
	size = size - 1;
	int r = (int)ceil((double)ROW / (double)size);
	int proc = i / r;
	return proc + 1;
}
int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	int size, rank;
	rank=MPI::COMM_WORLD.Get_rank();
	size=MPI::COMM_WORLD.Get_size();
	if (rank == 0)
	{
		int a[ROW][COL];
		int b[COL];
		int c[ROW];
		/* Generating Random Values for A & B Array*/
		srand(time(NULL));
		for (int i = 0; i<ROW; i++)
		{
			for (int j = 0; j<COL; j++)
			{
				if (i == 0) 
					b[j] = rand() % MAX_VALUE;
				a[i][j] = rand() % MAX_VALUE;
			}
		}
		/* Printing the Matrix*/
		cout << "Matrix A:" << endl;
		for (int i = 0; i<ROW; i++)
		{
			for (int j = 0; j<COL; j++)
			{
				cout << a[i][j] << " ";
			}
			cout << endl;
		}
		cout << "Matrix B:" << endl;
		for (int i = 0; i<COL; i++)
		{
			cout << b[i] << " ";
		}
		cout << endl;
		/* (1) Sending B Values to other processes */
		for (int j = 1; j<size; j++)
		{
			MPI::COMM_WORLD.Send(b, COL, MPI::INT, j, 0);
		}

		/* (2) Sending Required A Values to specific process */
		for (int i = 0; i<ROW; i++)
		{
			int processor = mappingToProcessors(i, size);
			MPI::COMM_WORLD.Send(a[i], COL, MPI::INT, processor, 1);
		}
		cout << "The Result:" << endl;
		/* (3) Gathering the result from other processes*/
		for (int i = 0; i<ROW; i++)
		{
			int source_process = mappingToProcessors(i, size);
			MPI::COMM_WORLD.Recv(&c[i], 1, MPI::INT, source_process, i);
			cout << c[i] << endl;
		}
	}
	else
	{
		int b[COL];
		/* (1) Each process get B Values from Master */
		MPI::COMM_WORLD.Recv(b, COL, MPI::INT, 0, 0);
		/* (2) Get Required A Values from Master then Compute the result */
		for (int i = 0; i<ROW; i++)
		{
			int processor = mappingToProcessors(i, size);
			if (rank == processor)
			{
				int res[COL];
				MPI::COMM_WORLD.Recv(res, COL, MPI::INT, 0, 1);
				int sum = 0;
				for (int j = 0; j<COL; j++)
				{
					sum = sum + (res[j] * b[j]);
				}
				MPI::COMM_WORLD.Send(&sum, 1, MPI::INT, 0, i);
			}
		}
	}
	MPI_Finalize();
	return 0;
}