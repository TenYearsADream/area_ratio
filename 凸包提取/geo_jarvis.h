#ifndef GEO_JARVIS_H_
#define GEO_JARVIS_H_

#include "geo_vector.h"
static int FindMinPolarAngle(Point arrInPt[],const int nInPtCount,const int nIndex);
// ����:������arrInPt,����nInPtCount,�������е�
// ���:������arrOutPt,����nOutPtCount,��ʱ��˳�����δ��͹���ϵĵ�
static void Jarvis(Point arrInPt[],const int nInPtCount,Point arrOutPt[],int & nOutPtCount)
{
	// step 1:�ҵ�������½ǵĵ�,�ŵ�p[0]λ��
	// ��֤p[0]��yֵ��С,������yֵ��ͬ,ȡxֵ��С��
	nOutPtCount = 0;
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
	// step : Ѱ����p[nIndex]������С���Ǹ���
	nIndex = 0;
	do 
	{
		arrOutPt[nOutPtCount++] = arrInPt[nIndex];
		nIndex = FindMinPolarAngle(arrInPt,nInPtCount,nIndex);
	} while (arrInPt[0] != arrInPt[nIndex]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}

static int FindMinPolarAngle(Point arrInPt[],const int nInPtCount,const int nIndex)
{
	// ��nIndex��һ���㿪ʼ
	int nAim = nIndex + 1;
	for(int i = 0;i < nInPtCount;++i)
	{
		// ���p[nIndex],p[nAim],p[i]����ת,˵��p[i]��p[nIndex]�ļ��Ǹ�С
		if( i != nIndex && i != nAim && IfTurnRight(arrInPt[nIndex],arrInPt[nAim],arrInPt[i]) == true)
		{
			nAim = i;
		}
	}
	return nAim;
}

#endif