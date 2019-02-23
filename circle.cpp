#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <exception>
#include "circle.h"

using namespace std;

namespace Circle{
Circle::Circle() throw(std::domain_error):Shape(), m_radius(0){}//Defaul Constructur

Circle::Circle(double radius, double initial_x, double initial_y) throw(std::domain_error)://Constructor for circle object
	Shape(initial_x, initial_y), m_radius(radius){//Throw exception if values outside of range.
		if( initial_x < 0)
			throw std::domain_error("Object cannot be construct because of x.\n");
		if( initial_y < 0)
			throw std::domain_error("Object cannot be construct because of y.\n");
		if( radius < 0)
			throw std::domain_error("Object cannot be construct because of radius.\n");
	}
	Circle::Circle(double operate) throw(std::domain_error)://Constructor for circle object
		Shape(0 ,0), m_radius(operate){
		}
/*-------GETTER FUNCTIONS OF CIRCLE MEMBER VARIABLES-----------*/
double Circle::getRadius() const throw(){return m_radius;}
double Circle::getDiameter() const throw(){return m_diameter;}
double Circle::getArea() const throw(){ return M_PI * m_radius * m_radius; } //Overrided area function
double Circle::getPerimeter() const throw() {return 2 * M_PI * m_radius; } //Overrided perimeter function
void Circle::input() throw(){//Input Function
	cout << "Please enter the radius:";
	cin >> m_radius;
	setDiameter();
}
/*-------SETTER FUNCTIONS OF CIRCLE MEMBER VARIABLES-----------*/
void Circle::setDiameter() throw(){
	m_diameter = m_radius * 2;
}
void Circle::setRadius(double newRadius) throw(std::domain_error){
	if(newRadius < 0)
		throw std::domain_error("Check radius value.\n");
	m_radius = newRadius;
	setDiameter();
}

void Circle::print(ostream& outputStream) const throw(){//Override print function for circle class
	outputStream << "<circle cx=\"" << getInitX() << "\"" << " cy=\"" << getInitY() << "\" "<< "r=\"" << getRadius() << "\" " << "fill=\"red\" stroke=\"white\"/>" << endl;
}

const Circle Circle::operator +(const Circle& circ) const throw(){
	double newRadius = m_radius + circ.getRadius();
	return Circle(newRadius, getInitX(), getInitY());
}
const Circle Circle::operator -(const Circle& circ) const throw(){
	double newRadius = abs(m_radius - circ.getRadius());
	return Circle(newRadius, getInitX(), getInitY());
}


}
