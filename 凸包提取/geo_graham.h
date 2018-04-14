#ifndef GEO_GRAHAM_H_
#define GEO_GRAHAM_H_

#include "geo_vector.h"

static bool BigPolarAngle(Point p0,Point p1,Point p2);
static void SortByPolarAngle(Point arrInPt[],const int nInPtCount);
static void SortByPolarAngle(Point arrInPt[],int nStart,int nEnd);

// 输入:点数组arrInPt,个数nInPtCount,包含所有点
// 输出:点数组arrOutPt,个数nOutPtCount,逆时针顺序依次存放凸包上的点
static void Graham(Point arrInPt[],const int nInPtCount,Point arrOutPt[],int & nOutPtCount)
{
	// step 1:找到最靠近坐下角的点,放到p[0]位置
	// 保证p[0]的y值最小,若两点y值相同,取x值较小者
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

	// step 2:剩下的点p[1]--p[nInPtCount-1],按照与p[0]极角升序排序
	SortByPolarAngle(arrInPt,nInPtCount);

	// step 3:栈操作
	nOutPtCount = 0;
	// 前三个点入栈
	arrOutPt[nOutPtCount++] = arrInPt[0];
	arrOutPt[nOutPtCount++] = arrInPt[1];
	arrOutPt[nOutPtCount++] = arrInPt[2];
	for(int i = 3;i < nInPtCount;i++)
	{
		// 栈中最上面两个点如果不与arrInPt[i]形成左转,就进行出栈操作
		while(nOutPtCount > 1 && IfTurnLeft(arrOutPt[nOutPtCount-2],arrOutPt[nOutPtCount-1],arrInPt[i]) == false )
		{
			nOutPtCount--;
		}
		// arrInPt[i]入栈
		arrOutPt[nOutPtCount++] = arrInPt[i];
	}

}

// 判断p0p2的极角是不是大于p0p1的极角
// 就是判断p0-p1-p2是左拐还是右拐,左拐返回true
static bool BigPolarAngle(Point p0,Point p1,Point p2)
{
	return IfTurnLeft(p0,p1,p2);
}

static void SortByPolarAngle(Point arrInPt[],const int nInPtCount)
{
	SortByPolarAngle(arrInPt,1,nInPtCount-1);
}

// 快速排序
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