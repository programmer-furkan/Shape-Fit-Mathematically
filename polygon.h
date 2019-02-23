#ifndef POLYGON_H
#define POLYGON_H
#include "shape.h"
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
namespace Polygon{
    using GeneralShape::Shape;
    using Triangle::Triangle;
    using Rectangle::Rectangle;
    using Circle::Circle;
    class Polygon: public Shape{
    public:
        //-----------POINT CLASS----------
      class Point2D{
      public:
        Point2D(double param_x = 0, double param_y = 0) throw(std::domain_error);
        double getX() const throw();
        double getY() const throw();
      private:
        double x;
        double y;
      };
      Polygon() throw(std::domain_error);//No parameter
      Polygon(const Polygon& copyPoly) throw(std::domain_error);//Copy constructor
      Polygon(vector<Polygon::Point2D> &pointVec) throw();
      Polygon(Point2D& pointObj) throw();//From a two 2D point
      Polygon(Rectangle& rect) throw(std::domain_error);//From Rectangle
      Polygon(Triangle& triang) throw(std::domain_error);//From Triangle
      Polygon(Circle& circ) throw(std::domain_error);//From Circle
      //-----------------------------------
      void setCapacity(int num) throw(std::domain_error); //Setting capacity for shape or point for dynamic array;
      int getCapacity() const throw();
      virtual void print(ostream& outputStream) const = 0;
      virtual double getArea() const throw(); //Override
      virtual double getPerimeter() const throw();//Override
    private:
      int capacity;
      double m_area;
      double m_perimeter;
      };
}

#endif
