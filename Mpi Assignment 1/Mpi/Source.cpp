#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
#define N 15

void master(void)
{
	int array[N];
	int len = N / 3;
	int mysum = 0, tmpsum;
	for (int i = 0; i < N; i++)
	{
		array[i] = i + 1;
	}
	MPI::COMM_WORLD.Send(&array[len * 0], N / 3, MPI::INT, 1, 0);
	MPI::COMM_WORLD.Send(&array[len * 1], N / 3, MPI::INT, 2, 0);
	MPI::COMM_WORLD.Send(&array[len * 2], N / 3, MPI::INT, 3, 0);

	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 1, 1);
	mysum += tmpsum;
	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 2, 1);
	mysum += tmpsum;
	MPI::COMM_WORLD.Recv(&tmpsum, 1, MPI::INT, 3, 1);
	mysum += tmpsum;
	cout << "The Sum = " << mysum << endl;
}
void slave(void)
{
	int array[N];
	int sum;
	unsigned long long i;
	MPI::COMM_WORLD.Recv(array, N / 3, MPI::INT, 0, 0);
	for (i = 0, sum = 0; i < N / 3; i++)
	{
		sum += array[i];
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
int main(int Argc, char **Argv)
{
	MPI::Init(Argc, Argv);
	int ID = MPI::COMM_WORLD.Get_rank();
	int Size = MPI::COMM_WORLD.Get_size();
	int Arr[1500];
	int iNumofele;
	if (ID == 0)
	{
		iNumofele = 1500 / Size;
		for (int i = 0; i<1500; i++)
		{
			Arr[i] = i;
		}

	}
	int* smallArr = new int[iNumofele];
	MPI::COMM_WORLD.Scatter(&Arr[0], iNumofele, MPI::INT, &smallArr[0], iNumofele, MPI::INT, 0);
	int Max = -1;
	for (int i = 0; i<iNumofele; i++)
	{
		if (smallArr[i] > Max)
			Max = smallArr[i];
	}
	int* maxArr = new int[Size];
	int maximum = -100;
	MPI::COMM_WORLD.Gather(&Max, 1, MPI::INT, maxArr, 1, MPI::INT, 0);
	if (ID == 0)
	{
		Max = -1;
		for (int i = 0; i<Size; ++i)
		if (maxArr[i] > maximum)
			Max = maxArr[i];
			cout << "Max Number is = " << Max << endl;
	}
	MPI::Finalize();
	return 0;
}

int main(int Argc, char **Argv)
{
	MPI::Init(Argc, Argv);
	int ID = MPI::COMM_WORLD.Get_rank();
	int Size = MPI::COMM_WORLD.Get_size();
	int iNumofele = 1500 / Size;
	int Arr[1500];
	if (ID == 0)
	{
		for (int i = 0; i<1500; i++)
		{
			Arr[i] = i;
		}

		for (int i = 1; i< iNumofele; i++)
		{
			MPI::COMM_WORLD.Send(&Arr[i*iNumofele], Size, MPI::INT, i, 0);
		}

		int localmaxP;
		int localMax = -10000;
		for (int i = 1; i<Size; i++)
		{
			MPI::COMM_WORLD.Recv(&localmaxP, 1, MPI::INT, i, 0);
			if (localmaxP >localMax)
			{
				localMax = localmaxP;
			}
		}
		cout << "Max Number is  = " << localMax << endl;
	}
	if (ID != 0)
	{
		int *smallArr = new int[iNumofele];
		MPI::COMM_WORLD.Recv(&smallArr[0], iNumofele, MPI::INT, 0, 0);
		int Max = -1;
		for (int i = 0; i<iNumofele; i++)
		{
			if (smallArr[i] > Max)
				Max = smallArr[i];
		}
		MPI::COMM_WORLD.Send(&Max, 1, MPI::INT, 0, 0);

	}

	MPI::Finalize();
	return 0;
}