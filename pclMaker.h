#pragma once
#include "includes.h"
#define PI 3.14159265

pcl::PointCloud<pcl::PointXYZ>::Ptr makeCircle(float diamiter, int sugestedPoints)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	float radious, height, master;
	master =diamiter/2;
	
	int thetaInc,phiInc;
	
	phiInc= (int) (180/sqrt(sugestedPoints));
	if(phiInc < 5){phiInc = 5;}

	thetaInc = phiInc*2;
	
	for(int phi=90; phi<270; phi+=phiInc)
	{
		height= master*sin(phi*PI/180);
		radious= master*cos(phi*PI/180);
		for(int theta=0; theta <360; theta+=thetaInc)
		{
			pcl::PointXYZ point;
			point.z= height;
			point.y= radious*sin(theta*PI/180);
			point.x=radious*cos(theta*PI/180);
			cloud->points.push_back(point);
		}
	}
	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	
	return cloud;
}


pcl::PointCloud<pcl::PointXYZ>::Ptr makeBranch(float diamiter, float length, int ringDencity ,int sugestedPoints)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	float pointsPerRing, distInc;
	int phiInc, ringNum, thetaInc;
	
	ringNum=(length*ringDencity);
	pointsPerRing = sugestedPoints/ringNum;
	distInc= length/ringNum;
	
	thetaInc= (int) (360/(sugestedPoints/ringNum));
	if(thetaInc<1){thetaInc=1;}

	for(float z=0; z<=length; z+= distInc)
	{
		for(int theta=0; theta <360; theta+=thetaInc)
		{
			float height = (float)(rand()%(int)(distInc*100));
			height = (height/100)+z;
			int Theta= int(theta+z)%360;
			pcl::PointXYZ point;
			point.z= height;
			point.y= (diamiter/2)*sin(Theta*PI/180);
			point.x= (diamiter/2)*cos(Theta*PI/180);
			cloud->points.push_back(point);
		}
		cout <<z<<endl;
	}
	
	
	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	
	return cloud;	
}



pcl::PointCloud<pcl::PointXYZ>::Ptr makeUnitCircle()
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	float radious=1;

	for(int theta=0; theta <360; theta++)
	{
		pcl::PointXYZ point;
		point.z= 0;
		point.y= radious*sin(theta*PI/180);
		point.x=radious*cos(theta*PI/180);
		cloud->points.push_back(point);
	}
	
	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	
	return cloud;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr fillField(pcl::PointCloud<pcl::PointXYZ>::Ptr field)
{
	int	fieldSize = field->points.size();
	for(int i=0; i<fieldSize; i++)
	{
		for(float height=0; height<field->points[i].z ; height+=7)
		{
			pcl::PointXYZ point;
			point.z=height;
			point.y=field->points[i].y;
			point.x=field->points[i].x;
			field->points.push_back(point);
		}
	}
	return field;
}

pcl::PointCloud<pcl::PointXYZ>::Ptr makeSlantField(float size)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	

	for(float xMark =0; xMark <size; xMark+= .5)
	{
		for(float yMark =0; yMark <size; yMark+= .5)
		{
			pcl::PointXYZ point;
			point.z= xMark;
			point.y= yMark;
			point.x= xMark;
			cloud->points.push_back(point);
		}
	}

	//cloud = fillField(cloud);

	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	
	return cloud;
}


pcl::PointCloud<pcl::PointXYZ>::Ptr makePlane(double lowerX, double lowerY, double upperX, double upperY, double height, double density)
{
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	density = 1/density;

	for(double i=lowerX; i<upperX; i+=density){
		for(double k=lowerY; k<upperY; k+=density){
			pcl::PointXYZ point;
			point.z= height;
			point.y= k;
			point.x= i;
			cloud->points.push_back(point);
		}
	}

	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	return cloud;
}


pcl::PointCloud<pcl::PointXYZ>::Ptr makeStepPlane(std::vector<double> bounds, double density)
{
	int max=0;
	int count=0;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
	
	for(int i=0; i<bounds.size(); i++){if(max<bounds[i]){max=bounds[i];}}
	
	for(int i=0; i<bounds.size()-1; i++)
	{
		pcl::PointCloud<pcl::PointXYZ>::Ptr temp(new pcl::PointCloud<pcl::PointXYZ>);
		temp=makePlane(bounds[i],0, bounds[i+1], max, i, density);
		for(int k=0; k<temp->points.size(); k++)
		{
			cloud->points.push_back(temp->points[k]);
			count++;
		}
		cout<<count<<endl;
	}

	cloud->width = cloud->points.size();
	cloud->height =1;
	cloud->is_dense=true;
	return cloud;
}









