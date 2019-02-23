#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "shape.h"
using namespace std;

namespace Rectangle{
	using GeneralShape::Shape;
class Rectangle: public Shape{
	double m_width;
	double m_height;
public:
	Rectangle() throw(std::domain_error);
	Rectangle(double width, double height, double initial_x, double initial_y) throw(std::domain_error);//Constructor
	Rectangle(double operate1, double operate2) throw();
	/*-------GETTER FUNCTIONS OF Rectangle MEMBER VARIABLES-----------*/
	double getWidth() const throw();
	double getHeight() const throw();
	double getArea() const throw(); //Override
	double getPerimeter() const throw(); //Override
	const Rectangle operator +(const Rectangle& rect) const throw();
	const Rectangle operator -(const Rectangle& rect) const throw();
	/*-------SETTER FUNCTIONS OF Rectangle MEMBER VARIABLES-----------*/
	void setWidth(double newWidth) throw(std::domain_error);
	void setHeight(double newHeight) throw(std::domain_error);
	void input() throw();
	//Draw
	void print(ostream& outputStream) const throw(); //Override
};
}
#endif
