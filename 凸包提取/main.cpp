#include <iostream>
#include <vector>
#include <cstdio>
#include <sstream>
#include <string>
#include "geo_vector.h"
#include "glut.h"
#include "geo_test_data.h"
#include "geo_graham.h"
#include "geo_jarvis.h"

#include "polygon_area.h"

using namespace std;
#pragma comment( lib, "glut32.lib" )

//设置读入的文件 ***configure***
#define FILE_NAME "wars/wars_8"
const int cur_index = 8;
#define OUTLINE_FILE_NAME "wars_modoutline.txt"
#define FILE_OUT "result"

int nRange = 1000,nOutPtCount = 0;
Point *arrInPt = new Point[MAX_POINT_COUNT];
Point *arrOutPt = new Point[MAX_POINT_COUNT];

//边框节点容器
vector<Point*> outlineVec;
vector<unsigned int> outlinesize;

//读取边框节点数据并计算面积
float calcuOutlineArea();

float calcuOutlineArea()
{
	outlineVec.clear();
	outlinesize.clear();

	fstream inf("wars_modoutline.txt", ios::in);
	string line;
	float x, y;
	unsigned int cur_size = 0;
	//统计需要生成的边框容器各子容器大小
	while(inf)
	{
		cur_size = 0;
		while(inf)
		{
			getline(inf, line);
			if(line.empty())
				break;
			cur_size++;
		}
		Point* t_outline = new Point[cur_size];
		outlineVec.push_back(t_outline);	
		outlinesize.push_back(cur_size);
	}
	inf.close();

	fstream oinf(OUTLINE_FILE_NAME, ios::in);
	//将边框节点坐标读入内存
	unsigned int i = 0;
	while(oinf)
	{
		cur_size = 0;
		while(oinf)
		{
			getline(oinf, line);
			if(line.empty())
			{
				break;
			}
			stringstream ss(line);
			ss>>x;
			ss>>y;
			outlineVec[i][cur_size].x = x;
			outlineVec[i][cur_size++].y = y;
		}
		i++;
	}

	oinf.close();

	//测试，看看是否都写入
	/*cout<<"边框数据："<<endl;
	for(size_t j = 0;j < outlineVec.size();j++)
	{
		for(unsigned int k = 0;k < outlinesize[j];k++)
		{
			cout<<outlineVec[j][k].x<<" "<<outlineVec[j][k].y<<endl;
		}
		cout<<endl;
	}
	cout<<"-------------------"<<endl;*/

	//计算当前边框面积
	//计算凸包面积 ***configure***
	PolygonArea t_area(outlineVec[cur_index], outlinesize[cur_index]);
	float area = t_area.getArea();

	return area;
}

void GenerateSomeData()
{
	Point *arrPt = new Point[MAX_POINT_COUNT];
	int nRange = 1;
	for(int i = 0;i < 6;i++)
	{
		nRange *= 10;
		GeneratePointData(arrPt,nRange,0,nRange);
		WritePointData(FILE_NAME,arrPt,nRange);
	}
	delete[] arrPt;
}

void TestGraham()
{
	time_t nStart = 0,nEnd = 0;
	//nRange = 1;
	//for(int i= 0;i <6;i++)
	//{
		//nRange *= 10;
	
		ReadPointData(FILE_NAME,arrInPt,&nRange);
		cout<<"Range = "<<nRange<<endl;
		nStart = clock();
		//Graham(arrInPt,nRange,arrOutPt,nOutPtCount);
		Jarvis(arrInPt,nRange,arrOutPt,nOutPtCount);

		cout<<"out points: "<<nOutPtCount<<endl;


		nEnd = clock();
		cout<<"Use time:"<<nEnd - nStart<<" ms"<<endl;
		cout<<"__________________"<<endl;

		//计算凸包面积
		PolygonArea t_area(arrOutPt, nOutPtCount);
		/*cout<<"凸包点："<<endl;
		for(unsigned int i = 0;i < nOutPtCount;i++)
		{
			cout<<arrOutPt[i].x<<","<<arrOutPt[i].y<<endl;
		}*/
		float area = t_area.getArea();
        cout<<"凸包面积： "<<area<<endl;

		//读取边框节点数据并计算面积
		float outline_area = calcuOutlineArea();
		cout<<"边框面积： "<<outline_area<<endl;
		cout<<"面积占比： "<<area/outline_area<<endl;
	//}
	//cout<<"test finish!"<<endl;
}

void DrawPoints(Point arrPt[],const int nPtCount,int nGLType)
{
	glPointSize(5);
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(nGLType);
	for(int i = 0;i < nPtCount;++i)
	{
		glVertex3f(arrPt[i].x,arrPt[i].y,0.0);
	}
	glEnd(); 
}

void GlutDisplay()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	DrawPoints(arrInPt,nRange,GL_POINTS);
	DrawPoints(arrOutPt,nOutPtCount,GL_LINE_LOOP);
	glutSwapBuffers();
}

void GlutReshape(int w,int h)
{
	if(h == 0)h = 1;
	float ratio = 1.0* w / h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float nEdge = nRange/10;
	gluOrtho2D(- nEdge, (GLfloat) nRange + nEdge, -nEdge, (GLfloat) nRange + nEdge);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();  
}

void DrawData(int argc,char *argv[])
{
	TestGraham();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB |GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(800,800);
	glutCreateWindow("PointData");
	glutDisplayFunc(GlutDisplay);
	glutReshapeFunc(GlutReshape);
	glutMainLoop();
}

int main(int argc,char *argv[])
{
	DrawData(argc,argv);
	//TestGraham();
	system("pause");
	return 0;
}