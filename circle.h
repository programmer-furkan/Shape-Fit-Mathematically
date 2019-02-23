#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "shape.h"
using namespace std;

namespace Circle{
	using GeneralShape::Shape;
class Circle: public Shape{
	double m_radius;
	double m_diameter;
public:
	Circle() throw(std::domain_error);//Default Constructur
	Circle(double radius, double initial_x, double initial_y) throw(std::domain_error);//Constructor
	Circle(double operate) throw(std::domain_error);
	/*-------GETTER FUNCTIONS OF CIRCLE MEMBER VARIABLES-----------*/
	double getRadius() const throw();
	double getDiameter() const throw();
	double getArea() const throw();
	double getPerimeter() const throw();
	/*-------SETTER FUNCTIONS OF CIRCLE MEMBER VARIABLES-----------*/
	void input() throw();
	void setDiameter() throw();
	void setRadius(double newRadius) throw(std::domain_error);
	//Draw Function
	void print(ostream& outputStream) const throw(); //Overrided
	const Circle operator +(const Circle& circ) const throw();
	const Circle operator -(const Circle& circ) const throw();
	//void draw(ofstream &myFile);
};

}
#endif
