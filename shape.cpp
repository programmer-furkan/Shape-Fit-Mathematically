#include <iostream>
#include "shape.h"

namespace GeneralShape{
  Shape::Shape() throw(): m_initial_x(0), m_initial_y(0){
  }
  Shape::Shape(double x, double y) throw(std::domain_error): m_initial_x(x), m_initial_y(y){
    if(x < 0)
     throw std::domain_error("Check shape x coordinate.\n");
    if(y < 0)
     throw std::domain_error("Check shape y coordinate.\n");
  }
  double Shape::getInitX() const throw(){
    return m_initial_x;
  }
  double Shape::getInitY() const throw(){
    return m_initial_y;
  }
  void Shape::setInitX(double newInitX) throw(){
    m_initial_x = newInitX;
  }
  void Shape::setInitY(double newInitY) throw(){
    m_initial_y = newInitY;
  }
  Shape& Shape::operator++() throw(){//Return reference because of abstract class
    m_initial_y++;
  	m_initial_x++;
  	return *this;
  }//Prefix
  Shape& Shape::operator++(int) throw(){//Return reference because of abstract class
    Shape& temp = *this;
    ++m_initial_y;
    ++m_initial_x;
    return temp;
  }//PostFix
  Shape& Shape::operator--() throw(std::domain_error){//Return reference because of abstract class
    m_initial_y--;
    m_initial_x--;
    if(m_initial_y < 0)
      throw std::domain_error("Check y coordinate");
    if(m_initial_x < 0)
      throw std::domain_error("Check x coordinate");
    return *this;
  }//Prefix
  Shape& Shape::operator--(int) throw(std::domain_error){//Return reference because of abstract class
    Shape& temp = *this;
    --m_initial_y;
    --m_initial_x;
    if(m_initial_y < 0)
      throw std::domain_error("Check y coordinate");
    if(m_initial_x < 0)
      throw std::domain_error("Check x coordinate");
    return temp;
  }//PostFix

  ostream &operator <<(ostream& outputStream, const Shape* shapeObj) throw(){// << overload for don't corrupt the order of << operator
    shapeObj->print(outputStream);
    return outputStream;
  }

//Logical operations
  bool operator ==(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) == (shapeTwo.getArea()));
  }
  bool operator !=(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) != (shapeTwo.getArea()));
  }
  bool operator <(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) < (shapeTwo.getArea()));
  }
  bool operator <=(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) <= (shapeTwo.getArea()));
  }
  bool operator >(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) > (shapeTwo.getArea()));
  }
  bool operator >=(const Shape &shapeOne, const Shape &shapeTwo) throw(){
    return ((shapeOne.getArea()) >= (shapeTwo.getArea()));
  }
}
