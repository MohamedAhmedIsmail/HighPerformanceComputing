#include<mpi.h>
#include <stdio.h>
#include<iostream>

using namespace std;
int main(int argc, char **argv)
{
	int myrank, size;
	int n;
	double localarr[5] = { 0 };
	double finalResult = 0.0;
	MPI_Init(&argc, &argv);
	myrank= MPI::COMM_WORLD.Get_rank();
	size = MPI::COMM_WORLD.Get_size();
	MPI::COMM_WORLD.Bcast(&n, 1, MPI::INT, 0);
	if (myrank == 0)
	{
		n = 100000;
		for (int i = 0; i < 5; i++)
		{
			finalResult += localarr[i];
		}
		cout << "The Final Result is:" << endl;
		cout << finalResult << endl;
	}
	
		double res = 0;
		for (int j = 0; j < 5; j++)
		{
			for (int i = 1; i <= n / 5; i+=size)
			{
				res += (1) / (1 + ((i - 0.5) / n)*((1 - 0.5) / n));
			
			}
			localarr[j] = res;
		}
	MPI::COMM_WORLD.Gather(&finalResult, 1, MPI::DOUBLE, &localarr, 5, MPI::DOUBLE, 0);
	MPI_Finalize();
	return 0;
}
