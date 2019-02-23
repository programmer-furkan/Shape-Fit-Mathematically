#include "polygon.h"
#include <iostream>
using namespace std;
namespace Polygon{
  Polygon::Polygon() throw(std::domain_error): Shape(0,0), capacity(1), m_area(0), m_perimeter(0){
  }//No parameter
  Polygon::Polygon(const Polygon& copyPoly) throw(std::domain_error): Shape(copyPoly.getInitX(), copyPoly.getInitY()), capacity(copyPoly.getCapacity()), m_area(copyPoly.getArea()), m_perimeter(copyPoly.getPerimeter()){
  }//Copy constructor
  Polygon::Polygon(vector<Polygon::Point2D>& pointVec) throw(): Shape(), capacity(pointVec.size()), m_area(0), m_perimeter(0){
  }//Vector of 2D points
  Polygon::Polygon(Polygon::Point2D& pointObj) throw(): Shape(), capacity(1), m_area(0), m_perimeter(0){
  }//From a 2D point
  Polygon::Polygon(Rectangle& rect) throw(std::domain_error): Shape(rect.getInitX(), rect.getInitY()), capacity(4), m_area(rect.getArea()), m_perimeter(rect.getPerimeter()){
  }//From Rectangle
  Polygon::Polygon(Triangle& triang) throw(std::domain_error): Shape(triang.getInitX(),triang.getInitY()), capacity(3), m_area(triang.getArea()), m_perimeter(triang.getPerimeter()){
  }//From Triangle
  Polygon::Polygon(Circle& circ) throw(std::domain_error): Shape(circ.getInitX(), circ.getInitY()), capacity(101), m_area(circ.getArea()), m_perimeter(circ.getPerimeter()){
  }//From Circle
  void Polygon::setCapacity(int num) throw(std::domain_error){
    if(num < 0)
      throw std::domain_error("Check capacity.\n");
    capacity = num;
  } //Setting capacity for shape or point for dynamic array;
  int Polygon::getCapacity() const throw(){
    return capacity;
  }
  Polygon::Point2D::Point2D(double param_x, double param_y) throw(std::domain_error): x(param_x), y(param_y){
    if(param_x < 0 || param_y < 0)
      throw std::domain_error("Check parameters.\n");
  }
  double Polygon::Point2D::getX() const throw(){
    return x;
  }
  double Polygon::Point2D::getY() const throw(){
    return y;
  }
  double Polygon::getArea() const throw(){ return m_area; } //Overrided area function
  double Polygon::getPerimeter() const throw(){ return m_perimeter; } //Overrided perimeter function
}
