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
	//���,����һ����ֵ
	float CrossMulti(Point v)
	{
		return x*v.y - v.x*y;
	}
	// ����
	Point operator-(Point b)
	{
		return Point(x-b.x,y-b.y);
	}
	// �ӷ�
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

// �жϵ�(pAim)��ֱ��(pStart--pEnd)�Ĺ�ϵ
// >0 pAim��˳ʱ��
// <0 pAmi����ʱ��
// =0 ���㹲��
static float Direction(Point pStart,Point pEnd,Point pAim)
{
	return (pAim-pStart).CrossMulti(pEnd-pStart);
}

// �жϵ�(pAim)�Ƿ����߶�(pStart--pEnd)��
static bool OnSegment(Point pStart,Point pEnd,Point pAim)
{
	if( MIN(pStart.x,pEnd.x) <= pAim.x && pAim.x <= MAX(pStart.x,pEnd.x)
		&& MIN(pStart.y,pEnd.y) <= pAim.y && pAim.y <= MAX(pStart.y,pEnd.y))
		return true;
	return false;
}

// �ж��߶�(p1-p2)���߶�(p3-p4)�Ƿ��ཻ
static bool SegmentIntersect(Point p1,Point p2,Point p3,Point p4)
{
	float d1 = Direction(p3,p4,p1);
	float d2 = Direction(p3,p4,p2);
	float d3 = Direction(p1,p2,p3);
	float d4 = Direction(p1,p2,p4);
	// �������ָ�,һ���ཻ
	if( (d1 < 0 && d2 > 0 || d1 >0 && d2 < 0 )
		&& ( d3 > 0 && d4 < 0 || d3 < 0 && d4 > 0))
		return true;
	// �������㹲��,���жϵ��Ƿ����߶���
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

// �ж�p0,p1,p2���������γɵ������߶��Ƿ���ת
// ������͹��
// ������������,���ǿ����ж������߶�P0P1��P1P2����ջ����ҹ�,
// ����Ҫ����Ƕ�,����ֻ��Ҫ�ж�����P0P2������P0P1��˳ʱ�뷽������ʱ�뷽��ͺ���
// ��m=(P2-P0)��(P1-P0)
// ���m>0˵��,����˳ʱ�뷽��,��P1���ҹ�,��m<0,������ʱ�뷽��,��P1�����
static bool IfTurnLeft(Point p0,Point p1,Point p2)
{
	return (p2-p0).CrossMulti(p1-p0) < 0;
}

// �ж�p0,p1,p2���������γɵ������߶��Ƿ���ת
static bool IfTurnRight(Point p0,Point p1,Point p2)
{
	return (p2-p0).CrossMulti(p1-p0) > 0;
}
#endif