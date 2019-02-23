#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

namespace GeneralShape{
  class Shape{
  public:
    Shape() throw();
    Shape(double x, double y) throw(std::domain_error);
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    double getInitX() const throw();
    double getInitY() const throw();
    void setInitX(double newInitX) throw();
    void setInitY(double newInitY) throw();
    Shape& operator++() throw();//Prefix
    Shape& operator++(int) throw();//PostFix
    Shape& operator--() throw(std::domain_error);//Prefix
    Shape& operator--(int) throw(std::domain_error);//PostFix
    virtual void print(ostream& outputStream) const = 0;
	  friend ostream &operator <<(ostream& outputStream, const Shape* shapeObj) throw();
    private:
    double m_initial_x;
    double m_initial_y;
  };
  bool operator ==(const Shape &shapeOne, const Shape &shapeTwo) throw();
  bool operator !=(const Shape &shapeOne, const Shape &shapeTwo) throw();
  bool operator <(const Shape &shapeOne, const Shape &shapeTwo) throw();
  bool operator <=(const Shape &shapeOne, const Shape &shapeTwo) throw();
  bool operator >(const Shape &shapeOne, const Shape &shapeTwo) throw();
  bool operator >=(const Shape &shapeOne, const Shape &shapeTwo) throw();
}


#endif
