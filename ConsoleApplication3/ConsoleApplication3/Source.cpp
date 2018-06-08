#include <stdio.h>
#include<iostream>
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
		cout << "pixel value( " << i << " ) has intesities frequency = " << localHistogramResult[i] << endl;
	}

	return 0;
}
