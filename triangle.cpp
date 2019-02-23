#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include "triangle.h"
#include "shape.h"
using namespace std;

namespace Triangle{
Triangle::Triangle() throw(std::domain_error):Shape(0, 0), m_side(0), m_p1(0), m_p2(0), m_p3(0), m_p4(0), m_p5(0), m_p6(0){}
Triangle::Triangle(double side, double initial_x, double initial_y, double p1, double p2, double p3, double p4, double p5, double p6) throw(std::domain_error): Shape(initial_x, initial_y), m_side(side), m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_p5(p5), m_p6(p6){//Constructor for triangle object
		if(side < 0)
			throw std::domain_error("Check the side lenght\n");
		if(initial_x < 0)
			throw std::domain_error("Check triangle x coordinate.\n");
		if(initial_y < 0)
			throw std::domain_error("Check triangle y coordinate.\n");
		setHeight();
	}
Triangle::Triangle(double operate) throw():Shape(0, 0), m_side(operate), m_p1(1), m_p2(1), m_p3(1), m_p4(1), m_p5(1), m_p6(1){
		setHeight();
	}

/*-------GETTER FUNCTIONS OF Triangle MEMBER VARIABLES-----------*/
double Triangle::getSide() const throw() {return m_side;}
double Triangle::getHeight() const throw() {return m_height;}
double Triangle::getP1() const throw() { return m_p1; }
double Triangle::getP2() const throw() { return m_p2; }
double Triangle::getP3() const throw() { return m_p3; }
double Triangle::getP4() const throw() { return m_p4; }
double Triangle::getP5() const throw() { return m_p5; }
double Triangle::getP6() const throw() { return m_p6; }
double Triangle::getArea() const throw() { return (m_side * m_side)*(sqrt(3)/4);} //Overrided area function
double Triangle::getPerimeter() const throw() { return 3 * m_side;} //Overrided perimeter function
/*-------SETTER FUNCTIONS OF Triangle MEMBER VARIABLES-----------*/
void Triangle::input() throw(){
	cout << "Please enter the side lenght:";
	cin >> m_side;
	setHeight();
}
void Triangle::setHeight() throw(){
	m_height = (m_side/2)*sqrt(3);
}


void Triangle::print(ostream& outputStream) const throw(){ //Overrided print function
	outputStream << "<polygon points=\"" << getP1() << " " << getP2() << ", "  << getP3() << " " << getP4() << ", " << getP5() << " " << getP6()<< "\" " << "fill=\"red\" stroke=\"white\"/>" << endl;
}



const Triangle Triangle::operator +(const Triangle& triang) const throw(){
	double newSide = m_side + triang.getSide();
	return Triangle(newSide, getInitX(), getInitY(), m_p1, m_p2, m_p3, m_p4, m_p5, m_p6);
}
const Triangle Triangle::operator -(const Triangle& triang) const throw(){
	double newSide = m_side + triang.getSide();
	return Triangle(newSide, getInitX(), getInitY(), m_p1, m_p2, m_p3, m_p4, m_p5, m_p6);
}

}
