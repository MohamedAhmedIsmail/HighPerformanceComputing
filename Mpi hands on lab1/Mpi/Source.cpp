#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
int main(int argc, char **argv)
{
	MPI::Init(argc, argv);
	int myrank, size, sender, reciever, x;
	size = MPI::COMM_WORLD.Get_size();
	myrank = MPI::COMM_WORLD.Get_rank();
	if (myrank == 0)
	{
		x = 5;
		cout << x << " myrank-->" << myrank << endl;
		MPI::COMM_WORLD.Send(&x, 1, MPI::INT, 1, 0);
		MPI::COMM_WORLD.Recv(&x, 1, MPI::INT, 3, 0);

	}
	else if (myrank == 1)
	{

		MPI::COMM_WORLD.Recv(&x, 1, MPI::INT, 0, 0);
		x += 1;
		cout << x << " myrank-->" << myrank << endl;
		MPI::COMM_WORLD.Send(&x, 1, MPI::INT, 2, 0);


	}
	else if (myrank == 2)
	{

		MPI::COMM_WORLD.Recv(&x, 1, MPI::INT, 1, 0);
		x += 1;
		cout << x << " myrank-->" << myrank << endl;
		MPI::COMM_WORLD.Send(&x, 1, MPI::INT, 3, 0);

	}
	else if (myrank == 3)
	{

		MPI::COMM_WORLD.Recv(&x, 1, MPI::INT, 2, 0);
		x += 1;
		cout << x << " myrank-->" << myrank << endl;
		MPI::COMM_WORLD.Send(&x, 1, MPI::INT, 0, 0);

	}
	MPI_Finalize();
	return 0;
}
