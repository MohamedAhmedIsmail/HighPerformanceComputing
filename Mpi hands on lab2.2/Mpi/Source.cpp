#include<mpi.h>
#include <stdio.h>
#include<iostream>
#define N 15
#define M 10
using namespace std;

void master(void)
{
	int array[N];
	int len = N / 3;
	int mysum1 = 0,mysum2=0,mysum3=0, tmpsum=0;
	for (int i = 0; i < N; i++)
	{
		array[i] = i + 1;
	}
	cout << "The elements of the array:" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	MPI::COMM_WORLD.Send(&array[len * 0], N / 3, MPI::INT, 1, 0);
	MPI::COMM_WORLD.Send(&array[len * 1], N / 3, MPI::INT, 2, 0);
	MPI::COMM_WORLD.Send(&array[len * 2], N / 3, MPI::INT, 3, 0);
	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 1, 1);
	mysum1 = tmpsum;
	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 2, 1);
	mysum2 = tmpsum;
	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 3, 1);
	mysum3 = tmpsum;
	if (mysum1 > 0 || mysum2 > 0 || mysum3 > 0)
		cout << "The Number "<<M<<" "<< "Exist" << endl;
	else
		cout << "The Number "<<M<<" "<<"Not Exist" << endl;
}

void slave(void)
{
	int array[N];
	int sum=0;
	unsigned long long i;
	MPI::COMM_WORLD.Recv(array, N / 3, MPI::INT, 0, 0);
	for (i = 0; i < N / 3; i++)
	{
		if (array[i] == M)
		{
			sum = 1;
		}
	}
	MPI::COMM_WORLD.Send(&sum, 1, MPI::INT, 0, 1);
}
int main(int argc, char **argv)
{
	int myrank;
	MPI_Init(&argc, &argv);
	myrank= MPI::COMM_WORLD.Get_rank();
	if (myrank == 0)
		master();
	else
		slave();
	MPI_Finalize();
	return 0;
}
