#ifndef GEO_VECTOR_H_
#define GEO_VECTOR_H_
#include <math.h>

#define MIN(x,y) (x>y?y:x)
#define MAX(x,y) (x>y?x:y)

struct Point 
{
	float x,y;
	Point()
	{
		x=0;
		y=0;
	}
	Point(float px,float py)
	{
		x = px;
		y = py;
	}
	//叉乘,返回一个数值
	float CrossMulti(Point v)
	{
		return x*v.y - v.x*y;
	}
	// 减法
	Point operator-(Point b)
	{
		return Point(x-b.x,y-b.y);
	}
	// 加法
	Point operator+(Point b)
	{
		return Point(x+b.x,y+b.y);
	}
	// == 
	bool operator!=(Point b)
	{
		return x != b.x || y != b.y;
	}
};

#define Vector Point;

// 判断点(pAim)与直线(pStart--pEnd)的关系
// >0 pAim在顺时针
// <0 pAmi在逆时针
// =0 三点共线
static float Direction(Point pStart,Point pEnd,Point pAim)
{
	return (pAim-pStart).CrossMulti(pEnd-pStart);
}

// 判断点(pAim)是否在线段(pStart--pEnd)上
static bool OnSegment(Point pStart,Point pEnd,Point pAim)
{
	if( MIN(pStart.x,pEnd.x) <= pAim.x && pAim.x <= MAX(pStart.x,pEnd.x)
		&& MIN(pStart.y,pEnd.y) <= pAim.y && pAim.y <= MAX(pStart.y,pEnd.y))
		return true;
	return false;
}

// 判断线段(p1-p2)和线段(p3-p4)是否相交
static bool SegmentIntersect(Point p1,Point p2,Point p3,Point p4)
{
	float d1 = Direction(p3,p4,p1);
	float d2 = Direction(p3,p4,p2);
	float d3 = Direction(p1,p2,p3);
	float d4 = Direction(p1,p2,p4);
	// 如果互相分隔,一定相交
	if( (d1 < 0 && d2 > 0 || d1 >0 && d2 < 0 )
		&& ( d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0))
		return true;
	// 若有三点共线,需判断点是否在线段内
	else if( d1 == 0 && OnSegment(p3,p4,p1))
		return true;
	else if( d2 == 0 && OnSegment(p3,p4,p2))
		return true;
	else if( d3 == 0 && OnSegment(p1,p2,p3))
		return true;
	else if( d4 == 0 && OnSegment(p1,p2,p4))
		return true;
	else
		return false;
}

// 判断p0,p1,p2依次连接形成的两条线段是否左转
// 用于求凸包
// 利用上述性质,我们可以判断连续线段P0P1和P1P2是左拐还是右拐,
// 不需要计算角度,我们只需要判断向量P0P2在向量P0P1的顺时针方向还是逆时针方向就好了
// 设m=(P2-P0)×(P1-P0)
// 如果m>0说明,则在顺时针方向,在P1处右拐,若m<0,则在逆时针方向,在P1处左拐
static bool IfTurnLeft(Point p0,Point p1,Point p2)
{
	return (p2-p0).CrossMulti(p1-p0) < 0;
}

// 判断p0,p1,p2依次连接形成的两条线段是否右转
static bool IfTurnRight(Point p0,Point p1,Point p2)
{
	return (p2-p0).CrossMulti(p1-p0) > 0;
}
#endif