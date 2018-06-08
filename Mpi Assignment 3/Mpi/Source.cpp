#include<mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include <time.h>
using namespace std;

void merge(int *a, int *b, int l, int m, int r) {

	int h, i, j, k;
	h = l;
	i = l;
	j = m + 1;

	while ((h <= m) && (j <= r)) {

		if (a[h] <= a[j]) {

			b[i] = a[h];
			h++;

		}

		else {

			b[i] = a[j];
			j++;

		}

		i++;

	}

	if (m < h) {

		for (k = j; k <= r; k++) {

			b[i] = a[k];
			i++;

		}

	}

	else {

		for (k = h; k <= m; k++) {

			b[i] = a[k];
			i++;

		}

	}

	for (k = l; k <= r; k++) {

		a[k] = b[k];

	}

}


void mergeSort(int *a, int *b, int l, int r)
{

	int m;

	if (l < r) {

		m = (l + r) / 2;

		mergeSort(a, b, l, m);
		mergeSort(a, b, (m + 1), r);
		merge(a, b, l, m, r);

	}

}
int main(int argc, char **argv)
{

	
	int world_rank;
	int world_size;
	MPI_Init(&argc, &argv);
	world_rank=MPI::COMM_WORLD.Get_rank();
	world_size = MPI::COMM_WORLD.Get_size();
	int n = 15;
	int *OriginalArr;
	OriginalArr = (int*)malloc(n * sizeof(int));
	srand(time(NULL));
	cout << "This is the unsorted array: " << endl;
	for (int i = 0; i < n; i++)
	{
		OriginalArr[i] = rand() % n;
		cout << OriginalArr[i] << " ";
	}
	cout << endl;
	
	int size = n / world_size;
	int *SubArr;
	SubArr= (int*)malloc(size * sizeof(int));
	MPI::COMM_WORLD.Scatter(OriginalArr, size, MPI_INT, SubArr, size, MPI_INT, 0);
	/********** Perform the mergesort on each process **********/
	int *TmpArr;
	TmpArr=(int*) malloc(size * sizeof(int));
	mergeSort(SubArr, TmpArr, 0, (size - 1));
	/********** Gather the sorted subarrays into one **********/
	int *sorted=NULL;
	if (world_rank == 0) 
	{
		sorted = (int*)malloc(n * sizeof(int));
	}
	MPI::COMM_WORLD.Gather(SubArr, size, MPI_INT, sorted, size, MPI_INT, 0);
	/********** Make the final mergeSort call **********/
	if (world_rank == 0) 
	{
		int *other_array =(int*) malloc(n * sizeof(int));
		mergeSort(sorted, other_array, 0, (n - 1));
		
		cout<<"This is the sorted array: "<<endl;
		for (int i = 0; i < n; i++)
		{
			cout<<sorted[i]<<" ";
		}
		printf("\n");
		printf("\n");

	}

	
	
	MPI_Finalize();
}