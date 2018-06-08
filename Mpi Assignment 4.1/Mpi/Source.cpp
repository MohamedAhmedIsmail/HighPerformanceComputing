#include <stdio.h>
#include<iostream>
#include <ctime>
using namespace std;
#define ImageWidth 128
#define ImageHeight 128
#define HistogramLength 256
int main()
{
	int imgData[ImageWidth*ImageHeight];
	int localHistogramResult[HistogramLength];
	int globalHistogramResult[HistogramLength];
	double startTime, endTime;
	startTime = clock();
	for (int i = 0; i < ImageWidth*ImageHeight; i++)
	{
		imgData[i] = rand() % (HistogramLength - 1);
	}
	int imgSubDataLength = (ImageWidth*ImageHeight);
	for (int i = 0; i < HistogramLength; i++)
	{
		localHistogramResult[i] = 0;
	}
	int* imgSubData = new int[imgSubDataLength];
	for (int i = 0; i < imgSubDataLength; i++)
	{
		localHistogramResult[imgData[i]]++;
	}
	for (int i = 0; i < HistogramLength; i++)
	{
		globalHistogramResult[i] = localHistogramResult[i];
	}
	for (int i = 0; i < HistogramLength; i++)
	{
		cout << "pixel value( " << i << " ) has intesities frequency = " << globalHistogramResult[i] << endl;
	}
	endTime = clock();
	cout << "time: " << (endTime - startTime) / double(CLOCKS_PER_SEC)<< endl;
	system("pause");
	return 0;
}
