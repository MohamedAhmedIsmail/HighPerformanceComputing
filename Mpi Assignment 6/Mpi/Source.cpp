#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
const int MAX = 16;
int main(int argc, char **argv)
{
	int rank, size, arr[MAX], count, value[1];
	MPI_Init(&argc, &argv);
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	if (rank == 0)
	{
		cout << "The Initial array" << endl;
		for (int i = 0; i < size; i++)
		{
			arr[i] = rand() % 100;
			cout << arr[i] << " ";
		}
		cout << endl;
	}
	MPI_Scatter(&arr, 1, MPI_INT, &value, 1, MPI_INT, 0, MPI_COMM_WORLD);
	//cout << "Rank: " << rank << " " << "Recieved: " << value[0] << endl;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0)
		{
			if (rank % 2 == 0)
			{
				MPI::COMM_WORLD.Send(&value[0], 1, MPI_INT, rank + 1, 0);
				MPI::COMM_WORLD.Recv(&value[1], 1, MPI_INT, rank + 1, 0);
				if (value[1] < value[0])
				{
					value[0] = value[1];
				}
				//cout << "Rank: " << rank << " i= " << i << " " << value[0] << endl;
			}
			else
			{
				MPI::COMM_WORLD.Recv(&value[1], 1, MPI_INT, rank - 1, 0);
				MPI::COMM_WORLD.Send(&value[0], 1, MPI_INT, rank - 1, 0);
				if (value[1]>value[0])
				{
					value[0] = value[1];
				}
				//cout << "Rank: " << rank << " i= " << i << " " << value[0] << endl;
			}
		}
		else
		{
			if ((rank % 2 == 1) && (rank != (size - 1)))
			{
				MPI::COMM_WORLD.Send(&value[0], 1, MPI_INT, rank + 1, 0);
				MPI::COMM_WORLD.Recv(&value[1], 1, MPI_INT, rank + 1, 0);
				if (value[1]<value[0])
				{
					value[0] = value[1];
				}
				//cout << "Rank: " << rank << " i= " << i << " " << value[0] << endl;
			}
			else if (rank != 0 && rank != (size - 1))
			{
				MPI::COMM_WORLD.Recv(&value[1], 1, MPI_INT, rank - 1, 0);
				MPI::COMM_WORLD.Send(&value[0], 1, MPI_INT, rank - 1, 0);
				if (value[1]>value[0])
				{
					value[0] = value[1];
				}
				//cout << "Rank: " << rank << " i= " << i << " " << value[0] << endl;
			}
		}
	}
		MPI_Gather(&value[0], 1, MPI_INT, &arr[0], 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (rank == 0)
		{
			cout << "Sorted array: " << endl;
			for (int i = 0; i < size; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
		}
		MPI_Finalize();
		return 0;
}