#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
int main(int argc, char **argv)
{
	MPI::Init(argc, argv);

	//MPI::COMM_WORLD.Bcast(void*Buffer, int count, MPI::INT, int root);
	//MPI::COMM_WORLD.Scatter(void *send_data, int send_count, MPI::INT, void*recv_data, MPI_Datatype recv_data, int root);
	//MPI::COMM_WORLD.Reduce(void*sendbuf, void*recvbuf, int count, MPI::INT, MPI::Max,Min,Sum, int root);
	int rank, size, n;
	double pi = 0.0, sum = 0.0, resultofpi = 0.0;
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();
	if (rank == 0)
	{
		cin >> n;
	}
	MPI::COMM_WORLD.Bcast(&n, 1, MPI::INT, 0);
	double h = 1 / double(n*size);
	for (int i = rank*n; i < (rank + 1)*n; i++)
	{
		sum += 4 / (1 + (h*((double)i - 0.5))*(h*((double)i - 0.5)));
	}
	resultofpi = h*sum;
	MPI::COMM_WORLD.Reduce(&resultofpi, &pi, 1, MPI::DOUBLE, MPI::SUM, 0);
	if (rank == 0)
		cout << "PI = " << pi << endl;
	MPI_Finalize();
	return 0;
}
