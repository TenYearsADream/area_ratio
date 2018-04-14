#ifndef GEO_GRAHAM_H_
#define GEO_GRAHAM_H_

#include "geo_vector.h"

static bool BigPolarAngle(Point p0,Point p1,Point p2);
static void SortByPolarAngle(Point arrInPt[],const int nInPtCount);
static void SortByPolarAngle(Point arrInPt[],int nStart,int nEnd);

// ����:������arrInPt,����nInPtCount,�������е�
// ���:������arrOutPt,����nOutPtCount,��ʱ��˳�����δ��͹���ϵĵ�
static void Graham(Point arrInPt[],const int nInPtCount,Point arrOutPt[],int & nOutPtCount)
{
	// step 1:�ҵ�������½ǵĵ�,�ŵ�p[0]λ��
	// ��֤p[0]��yֵ��С,������yֵ��ͬ,ȡxֵ��С��
	int nIndex = 0;
	for(int i = 1;i < nInPtCount;++i)
	{
		if(arrInPt[i].y < arrInPt[nIndex].y ||
			(arrInPt[i].y == arrInPt[nIndex].y && arrInPt[i].x < arrInPt[nIndex].x))
		{
			nIndex = i;
		}
	}
	Point tmp = arrInPt[0];
	arrInPt[0] = arrInPt[nIndex];
	arrInPt[nIndex] = tmp;

	// step 2:ʣ�µĵ�p[1]--p[nInPtCount-1],������p[0]������������
	SortByPolarAngle(arrInPt,nInPtCount);

	// step 3:ջ����
	nOutPtCount = 0;
	// ǰ��������ջ
	arrOutPt[nOutPtCount++] = arrInPt[0];
	arrOutPt[nOutPtCount++] = arrInPt[1];
	arrOutPt[nOutPtCount++] = arrInPt[2];
	for(int i = 3;i < nInPtCount;i++)
	{
		// ջ���������������������arrInPt[i]�γ���ת,�ͽ��г�ջ����
		while(nOutPtCount > 1 && IfTurnLeft(arrOutPt[nOutPtCount-2],arrOutPt[nOutPtCount-1],arrInPt[i]) == false )
		{
			nOutPtCount--;
		}
		// arrInPt[i]��ջ
		arrOutPt[nOutPtCount++] = arrInPt[i];
	}

}

// �ж�p0p2�ļ����ǲ��Ǵ���p0p1�ļ���
// �����ж�p0-p1-p2����ջ����ҹ�,��շ���true
static bool BigPolarAngle(Point p0,Point p1,Point p2)
{
	return IfTurnLeft(p0,p1,p2);
}

static void SortByPolarAngle(Point arrInPt[],const int nInPtCount)
{
	SortByPolarAngle(arrInPt,1,nInPtCount-1);
}

// ��������
static void SortByPolarAngle(Point arrInPt[],int nStart,int nEnd)
{
	if(nStart >= nEnd)return;
	int i = nStart,j = nEnd;
	Point tmp = arrInPt[i];
	while(i < j)
	{
		while(i < j && BigPolarAngle(arrInPt[0],tmp,arrInPt[j]) == true)j--;
		if(i < j)
		{
			arrInPt[i] = arrInPt[j];
		}
		while(i < j && BigPolarAngle(arrInPt[0],tmp,arrInPt[i]) == false)i++;
		if(i < j)
		{
			arrInPt[j] = arrInPt[i];
		}
	}
	arrInPt[i] = tmp;
	SortByPolarAngle(arrInPt,nStart,i-1);
	SortByPolarAngle(arrInPt,i+1,nEnd);
}

#endif