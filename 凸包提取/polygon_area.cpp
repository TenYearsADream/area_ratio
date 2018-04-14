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
	//���ղ�˵ķ�ʽ������ʱ���˳ʱ��ڵ�˳�����������ηָ�ɶ�������κ�������������������ͬʱҲ�����ڰ�����Σ�
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