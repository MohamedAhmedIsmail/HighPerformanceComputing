#include<mpi.h>
#include <stdio.h>
#include<iostream>
using namespace std;
#define ImageWidth 128
#define ImageHeight 128
#define HistogramLength 256
int main(int argc, char **argv)
{
	int rank, size;
	int imgData[ImageWidth*ImageHeight];
	int localHistogramResult[HistogramLength];
	int globalHistogramResult[HistogramLength];
	double startTime, endTime;
	MPI::Init(argc, argv);
	startTime = MPI_Wtime();
	size = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();
	if (rank == 0)
	{
		srand(size);
		for (int i = 0; i < ImageWidth*ImageHeight; i++)
		{
			imgData[i] = rand() % (HistogramLength - 1);
		}
	}
		int imgSubDataLength = (ImageWidth*ImageHeight) / size;
		for (int i = 0; i < HistogramLength; i++)
		{
			localHistogramResult[i] = 0;
		}
		int* imgSubData = new int[imgSubDataLength];
		MPI::COMM_WORLD.Scatter(imgData, imgSubDataLength, MPI::INT, imgSubData, imgSubDataLength, MPI::INT, 0);
		for (int i = 0; i < imgSubDataLength; i++)
		{
			localHistogramResult[imgSubData[i]]++;
		}
		MPI::COMM_WORLD.Reduce(&localHistogramResult, &globalHistogramResult, HistogramLength, MPI::INT, MPI::SUM, 0);
		if (rank == 0)
		{
			for (int i = 0; i < HistogramLength; i++)
			{
				cout << "pixel value( " << i << " ) has intesities frequency = " << globalHistogramResult[i] << endl;
			}
			endTime = MPI_Wtime();
			cout << "The time = "<<endTime - startTime << endl;

		}
		
	MPI_Finalize();
	return 0;
}
