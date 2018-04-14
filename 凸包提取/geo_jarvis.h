#ifndef GEO_JARVIS_H_
#define GEO_JARVIS_H_

#include "geo_vector.h"
static int FindMinPolarAngle(Point arrInPt[],const int nInPtCount,const int nIndex);
// 输入:点数组arrInPt,个数nInPtCount,包含所有点
// 输出:点数组arrOutPt,个数nOutPtCount,逆时针顺序依次存放凸包上的点
static void Jarvis(Point arrInPt[],const int nInPtCount,Point arrOutPt[],int & nOutPtCount)
{
	// step 1:找到最靠近坐下角的点,放到p[0]位置
	// 保证p[0]的y值最小,若两点y值相同,取x值较小者
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
	// step : 寻找与p[nIndex]极角最小的那个点
	nIndex = 0;
	do 
	{
		arrOutPt[nOutPtCount++] = arrInPt[nIndex];
		nIndex = FindMinPolarAngle(arrInPt,nInPtCount,nIndex);
	} while (arrInPt[0] != arrInPt[nIndex]);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
}

static int FindMinPolarAngle(Point arrInPt[],const int nInPtCount,const int nIndex)
{
	// 从nIndex下一个点开始
	int nAim = nIndex + 1;
	for(int i = 0;i < nInPtCount;++i)
	{
		// 如果p[nIndex],p[nAim],p[i]向右转,说明p[i]与p[nIndex]的极角更小
		if( i != nIndex && i != nAim && IfTurnRight(arrInPt[nIndex],arrInPt[nAim],arrInPt[i]) == true)
		{
			nAim = i;
		}
	}
	return nAim;
}

#endif