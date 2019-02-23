#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "shape.h"
using namespace std;


namespace Triangle{
	using GeneralShape::Shape;
class Triangle: public Shape{
private:
	double m_side;
	double m_height;
	double m_p1, m_p2, m_p3, m_p4, m_p5, m_p6;
public:
	Triangle() throw(std::domain_error);
	Triangle(double side, double initial_x, double initial_y, double p1, double p2, double p3, double p4, double p5, double p6) throw(std::domain_error);//Constructor
	Triangle(double operate) throw();
	/*-------GETTER FUNCTIONS OF Triangle MEMBER VARIABLES-----------*/
	double getSide() const throw();
	double getHeight() const throw();
	double getP1() const throw();
	double getP2() const throw();
	double getP3() const throw();
	double getP4() const throw();
	double getP5() const throw();
	double getP6() const throw();
	double getArea() const throw(); //Override
	double getPerimeter() const throw(); //Override
	/*-------SETTER FUNCTIONS OF Triangle MEMBER VARIABLES-----------*/
	void input() throw();
	void setHeight() throw();
	//Draw Function
	void print(ostream& outputStream) const throw(); //Override
	//void draw(ofstream &myFile);
	const Triangle operator +(const Triangle& triang) const throw();
	const Triangle operator -(const Triangle& triang) const throw();
};

}

#endif
