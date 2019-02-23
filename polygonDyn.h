#ifndef POLYGONDYN_H
#define POLYGONDYN_H
#include "polygon.h"
#include "polygonVect.h"
#include <iostream>
using namespace std;

namespace PolygonDyn{
  using GeneralShape::Shape;
  using Triangle::Triangle;
  using Rectangle::Rectangle;
  using Circle::Circle;
  using Polygon::Polygon;
  using PolygonVect::PolygonVect;
  class PolygonDyn: public Polygon{
    public:
      PolygonDyn() throw(std::bad_alloc);//No parameter
      PolygonDyn(const PolygonDyn& copyPoly) throw(std::bad_alloc, std::domain_error);//Copy constructor
      PolygonDyn(vector<Polygon::Point2D> &pointVec) throw(std::bad_alloc);
      PolygonDyn(Point2D& pointObj) throw(std::bad_alloc);//From a two 2D point
      PolygonDyn(Rectangle& rect) throw(std::bad_alloc, std::domain_error);//From Rectangle
      PolygonDyn(Triangle& triang) throw(std::bad_alloc, std::domain_error);//From Triangle
      PolygonDyn(Circle& circ) throw(std::bad_alloc, std::domain_error);//From Circle
      PolygonDyn(PolygonVect& vect) throw(std::bad_alloc, std::domain_error);
      PolygonDyn& operator =(const PolygonDyn& assingPol) throw(std::bad_alloc, std::domain_error);//Assigment
      virtual ~PolygonDyn() throw();
      Point2D& operator [](int index) throw(std::out_of_range);
      const Point2D& operator [](int index) const throw(std::out_of_range);//[] overoading
      bool operator ==(const PolygonDyn& otherPoly) const throw();
      bool operator !=(const PolygonDyn& otherPoly) const throw();
      const PolygonDyn operator +(const PolygonDyn& otherPoly) const throw(std::bad_alloc);
      virtual void print(ostream& outputStream) const throw(); //Override
    private:
      Point2D* points;
  };
}


#endif
