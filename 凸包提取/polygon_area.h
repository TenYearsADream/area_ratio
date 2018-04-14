/*

  计算任意多边形面积

 */
#ifndef POLYGON_AREA_H
#define POLYGON_AREA_H

#include "geo_vector.h"

#include <vector>
using namespace std;

class PolygonArea
{
public:
	PolygonArea(Point *arrInput, unsigned int nodenum);
	~PolygonArea();
	float getArea();

private:
	void calculateArea();

	float cross(const Point &a, const Point &b);

	Point *m_arrInput;
	unsigned int m_nodenum;
	float m_poly_area;
};


#endif