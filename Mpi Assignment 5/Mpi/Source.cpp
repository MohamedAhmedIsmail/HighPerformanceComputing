#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
#define ArraySize 40
#define sizeSubArray 20
double outputArray[ArraySize] = { 0.0 };
MPI_Datatype oddNumbers;
MPI_Datatype evenNumbers;
double avgOddNumbers = 0.0, avgEvenNumbers = 0.0;
void Boss()
{
		double inputArray[ArraySize];
		MPI_Type_vector(20, 1, 2, MPI_DOUBLE, &oddNumbers);
		MPI_Type_vector(20, 1, 2, MPI_DOUBLE, &evenNumbers);
		MPI_Type_commit(&oddNumbers);
		MPI_Type_commit(&evenNumbers);
		for (int i = 0; i < ArraySize; i++)
		{
			inputArray[i] = pow(i + 1, 2.5);
		}
		MPI::COMM_WORLD.Send(&inputArray[0], 1, oddNumbers, 1, 0);
		MPI::COMM_WORLD.Send(&inputArray[1], 1, evenNumbers, 2, 0);
		for (int i = 0; i < ArraySize; i++)
		{
			cout << inputArray[i] << " ";
		}
		cout << endl;
		MPI::COMM_WORLD.Recv(&avgOddNumbers, 1, MPI_DOUBLE, 1, 1);
		MPI::COMM_WORLD.Recv(&avgEvenNumbers, 1, MPI_DOUBLE, 2, 1);
		cout << "The Average of processor1(odd indexed): ";
		cout << avgOddNumbers << endl;
		cout << "The Average of processor2(even indexed): ";
		cout << avgEvenNumbers << endl;
}
void Worker1()
{
		MPI::COMM_WORLD.Recv(&outputArray[0], 1, oddNumbers, 0, 0);
		for (int i = 0; i < ArraySize; i++)
		{
			avgOddNumbers += outputArray[i];
		}
		avgOddNumbers /= sizeSubArray;
		MPI::COMM_WORLD.Send(&avgOddNumbers, 1, MPI_DOUBLE, 0, 1);		
}
void Worker2()
{
	MPI::COMM_WORLD.Recv(&outputArray[1], 1, evenNumbers, 0, 0);
	for (int i = 0; i < ArraySize; i++)
	{
		avgEvenNumbers += outputArray[i];
	}
	avgEvenNumbers /= sizeSubArray;
	MPI::COMM_WORLD.Send(&avgEvenNumbers, 1, MPI_DOUBLE, 0, 1);
}
int main(int argc, char **argv)
{
	/*int rank;
	MPI_Status status;
	struct
	{
		int x; int y; int z;
	}point;
	MPI_Datatype ptype;
	MPI::Init(argc, argv);
	rank = MPI::COMM_WORLD.Get_rank();
	MPI_Type_contiguous(3, MPI_INT, &ptype);
	MPI_Type_commit(&ptype);
	if (rank == 3)
	{
		point.x = 15;
		point.y = 23;
		point.z = 6;
		MPI_Send(&point, 1, ptype,1, 52, MPI_COMM_WORLD);
	}
	else if (rank == 1)
	{
		MPI_Recv(&point, 1, ptype, 3, 52, MPI_COMM_WORLD, &status);
		cout << "The Recieved Coordinates are:" << endl;
		cout << "The rank: " << rank << endl;
		cout << point.x << " " << point.y << " " << point.z << endl;
	}
	MPI_Finalize();*/
	/*int rank, size;
	int arr[40];
	MPI_Status status;
	MPI::Init(argc, argv);
	rank = MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	if (rank == 0)
	{
		MPI_Recv(arr, 20, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
		for (int i = 0; i < 20; i++)
		{
			cout << arr[i] << endl;
		}
		MPI_Recv(arr, 20, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
		for (int i = 0; i < 20; i++)
		{
			cout << arr[i] << endl;
		}
	}
	else if (rank == 1)
	{
		int c = 0;
		for (int i = 0; i < 40; i+=2)
		{
			arr[c] = i;
			c++;
		}
		MPI_Send(arr, 20, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else if (rank == 2)
	{
		int c = 0;
		for (int i = 1; i <= 40; i += 2)
		{
			arr[c] = i;
			c++;
		}
		MPI_Send(arr, 20, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}*/
	MPI::Init(argc, argv);
	int rank = MPI::COMM_WORLD.Get_rank();
	double inputArray[40], outputArray[40] = { 0 };
	double avgOddNumbers = 0.0, avgEvenNumbers = 0.0;
	MPI_Datatype oddNumbers;
	MPI_Datatype evenNumbers;
	MPI_Type_vector(20, 1, 2, MPI_DOUBLE, &oddNumbers);
	MPI_Type_vector(20, 1, 2, MPI_DOUBLE, &evenNumbers);
	MPI_Type_commit(&oddNumbers);
	MPI_Type_commit(&evenNumbers);
	if (rank == 0)
	{
		for (int i = 0; i < 40; i++)
		{
			inputArray[i] = i;
		}
		MPI::COMM_WORLD.Send(&inputArray[0], 1, oddNumbers, 1, 0);
		MPI::COMM_WORLD.Send(&inputArray[1], 1, evenNumbers, 2, 0);
		for (int i = 0; i < 40; i++)
		{
			cout << inputArray[i] << " ";
		}
		cout << endl;
		MPI::COMM_WORLD.Recv(&avgOddNumbers, 1, MPI_DOUBLE, 1, 1);
		MPI::COMM_WORLD.Recv(&avgEvenNumbers, 1, MPI_DOUBLE, 2, 1);
		cout << "The Average of processor1(odd indexed): ";
		cout << avgOddNumbers << endl;
		cout << "The Average of processor2(even indexed): ";
		cout << avgEvenNumbers << endl;
	}
	else if (rank == 1)
	{
		MPI::COMM_WORLD.Recv(&outputArray[0], 1, oddNumbers, 0, 0);
		for (int i = 0; i < 40; i++)
		{
			cout << outputArray[i] << " ";
		}
		for (int i = 0; i < 40; i++)
		{
			avgOddNumbers += outputArray[i];
		}
		avgOddNumbers /= 20;
		MPI::COMM_WORLD.Send(&avgOddNumbers, 1, MPI_DOUBLE, 0, 1);
	}
	else if (rank == 2)
	{
		MPI::COMM_WORLD.Recv(&outputArray[1], 1, evenNumbers, 0, 0);
		for (int i = 0; i < 40; i++)
		{
			cout << outputArray[i] << " ";
		}
		for (int i = 0; i < 40; i++)
		{
			avgEvenNumbers += outputArray[i];
		}
		avgEvenNumbers /= 20;
		MPI::COMM_WORLD.Send(&avgEvenNumbers, 1, MPI_DOUBLE, 0, 1);
	}
	/*if (rank == 0)
	{
		Boss();
	}
	else if (rank==1)
	{
		Worker1();
	}
	else if (rank == 2)
	{
		Worker2();
	}*/
	MPI_Finalize();
	return 0;
}
