#ifndef POLYGONVECT_H
#define POLYGONVECT_H
#include "polygon.h"
#include <iostream>
using namespace std;

namespace PolygonVect{
  using GeneralShape::Shape;
  using Triangle::Triangle;
  using Rectangle::Rectangle;
  using Circle::Circle;
  using Polygon::Polygon;
  class PolygonVect: public Polygon{
    public:
      PolygonVect() throw(std::domain_error);//No parameter
      PolygonVect(const PolygonVect& copyPoly) throw(std::domain_error);//Copy constructor
      PolygonVect(vector<Polygon::Point2D> &pointVec) throw();
      PolygonVect(Point2D& pointObj) throw();//From a two 2D point
      PolygonVect(Rectangle& rect) throw(std::domain_error);//From Rectangle
      PolygonVect(Triangle& triang) throw(std::domain_error);//From Triangle
      PolygonVect(Circle& circ) throw(std::domain_error);//From Circle
      PolygonVect& operator =(const PolygonVect& assingPol) throw(std::domain_error);//Assigment
      virtual ~PolygonVect() throw();
      Point2D& operator [](int index) throw(std::out_of_range);
      const Point2D& operator [](int index) const throw(std::out_of_range);//[] overoading
      bool operator ==(const PolygonVect& otherPoly) const throw();
      bool operator !=(const PolygonVect& otherPoly) const throw();
      const PolygonVect operator +(const PolygonVect& otherPoly) const throw();
      virtual void print(ostream& outputStream) const throw(); //Override
    private:
      vector<Point2D> points;
  };
}


#endif
