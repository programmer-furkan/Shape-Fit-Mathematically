#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "rectangle.h"

using namespace std;

namespace Rectangle{
Rectangle::Rectangle() throw(std::domain_error): Shape(), m_width(0), m_height(0){}
Rectangle::Rectangle(double width, double height, double initial_x, double initial_y) throw(std::domain_error)://Constructor for Rectangle object
	Shape(initial_x, initial_y), m_width(width), m_height(height){
		if(width < 0)
			throw std::domain_error("Check the width.\n");
		if(height < 0)
			throw std::domain_error("Check the height.\n");
		if(initial_x < 0)
			throw std::domain_error("Check rect x coordinate.\n");
		if(initial_y < 0)
			throw std::domain_error("Check rect y coordinate.\n");
	}
Rectangle::Rectangle(double operate1, double operate2) throw()://Constructor for + and - overload
	Shape(0 ,0), m_width(operate1), m_height(operate2){
	}
/*-------GETTER FUNCTIONS OF Rectangle MEMBER VARIABLES-----------*/
double Rectangle::getWidth() const throw(){return m_width;}
double Rectangle::getHeight() const throw(){return m_height;}
double Rectangle::getArea() const throw(){ return m_height * m_width; } //Overrided ara function
double Rectangle::getPerimeter() const throw(){return 2*(m_width + m_height); } //Overrided perimeter function
/*-------SETTER FUNCTIONS OF Rectangle MEMBER VARIABLES-----------*/
void Rectangle::setWidth(double newWidth) throw(std::domain_error){
	if( newWidth < 0)
		throw std::domain_error("Check the width.\n");
	m_width = newWidth;
}
void Rectangle::setHeight(double newHeight) throw(std::domain_error){
	if(newHeight < 0)
		throw std::domain_error("Check the width.\n");
	m_height = newHeight;
}
void Rectangle::input() throw(){
	cout << "Please enter the width:";
	cin >> m_width;
	cout << "Please enter the height:";
	cin >> m_height;
}

void Rectangle::print(ostream& outputStream) const throw(){ //Overrided print function
	outputStream << "<rect x=\"" << getInitX() << "\"" << " y=\"" << getInitY() << "\" "<< "width=\"" << getWidth() << "\" " << "height=\"" << getHeight() << "\" " << "fill=\"red\" stroke=\"white\"/>" << endl;
}



const Rectangle Rectangle::operator +(const Rectangle& rect) const throw(){
	double newWidth = m_width + rect.getWidth();
	double newHeight = m_height + rect.getHeight();
	double newX = getInitX() + rect.getInitX();
	double newY= getInitY() + rect.getInitY();
	return Rectangle(newWidth, newHeight, newX, newY);
}
const Rectangle Rectangle::operator -(const Rectangle& rect) const throw(){
	double newWidth = m_width - rect.getWidth();
	double newHeight = m_height - rect.getHeight();
	double newX = getInitX() - rect.getInitX();
	double newY = getInitY() - rect.getInitY();
	return Rectangle(newWidth, newHeight, newX, newY);
}

}
