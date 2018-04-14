#include "polygon_area.h"

PolygonArea::PolygonArea(Point *arrInput, unsigned int nodenum)
	:m_arrInput(arrInput), m_nodenum(nodenum)
{
	calculateArea();
}

PolygonArea::~PolygonArea()
{

}

float PolygonArea::cross(const Point &a, const Point &b)
{
    return a.x * b.y - a.y * b.x;	
}

void PolygonArea::calculateArea()
{
	float area = 0.0;
	//按照叉乘的方式按照逆时针或顺时针节点顺序来计算多边形分割成多个三角形后的有向面积求得总面积（同时也适用于凹多边形）
	for(unsigned int i = 1;i < m_nodenum-1;i++)
	{
		area += cross(m_arrInput[i] - m_arrInput[0], m_arrInput[i+1] - m_arrInput[0]) / 2.0;
	}

	if(area < 0)
		area = -area;

	m_poly_area = area;
}

float PolygonArea::getArea()
{
	return m_poly_area;
}