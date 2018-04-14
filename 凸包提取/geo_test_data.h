#ifndef GEO_TEST_DATA_H_
#define GEO_TEST_DATA_H_

#include "geo_vector.h"
#include <fstream>
#include <time.h>
#include <stdlib.h>
using namespace std;

#define MAX_FILENAME_LEN 256
#define MAX_POINT_COUNT (1e6)
#define RANDOM(x,y) ((rand()%int(y-x) + int(x)))

// 生成随机点数据
void GeneratePointData(Point arrPt[],const int nPtCount,float fMinRange,float fMaxRange)
{
	srand(time(NULL));
	for(int i = 0;i < nPtCount;i++)
	{
		float x = (float)RANDOM(fMinRange,fMaxRange);
		float y = (float)RANDOM(fMinRange,fMaxRange);
		arrPt[i].x = x;
		arrPt[i].y = y;
	}
}

void ReadPointData(const char *szFileName,Point arrPt[],int *nPtSize)
{
	char szName[MAX_FILENAME_LEN] = {0};
	sprintf_s(szName,"%s.txt",szFileName);

	int nPtCount = 0;
	fstream inff(szName, ios::in);
	string line;
	while(inff)
	{
		getline(inff, line);
		if(line.empty())
			break;
		nPtCount++;
	}

	*nPtSize = nPtCount;

	ifstream inf(szName);
	if(!inf)return;
	for(int i = 0;i < nPtCount;i++)
	{
		inf>>arrPt[i].x>>arrPt[i].y;
	}
	inf.close();
}

void WritePointData(const char *szFileName,Point arrPt[],const int nPtCount)
{
	char szName[MAX_FILENAME_LEN] = {0};
	sprintf_s(szName,"%s.txt",szFileName);
	ofstream of(szName,ios::out);
	if(!of)
	{
		cout<<"open "<<szName<<" error!"<<endl;
		return;
	}
	for(int i = 0;i < nPtCount;i++)
	{
		of<<arrPt[i].x<<" "<<arrPt[i].y<<endl;
	}
	of.close();
}
#endif