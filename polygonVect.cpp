#include "polygonVect.h"
#include <iostream>
using namespace std;
namespace PolygonVect{

  PolygonVect::PolygonVect() throw(std::domain_error):Polygon(){
    points.push_back(Polygon::Point2D(0,0));
  }//No parameter
  PolygonVect::PolygonVect(const PolygonVect& copyPoly) throw(std::domain_error): Polygon(copyPoly){
    for(int i = 0; i < getCapacity(); i++){
      points.push_back(copyPoly.points[i]);
    }
  }//Copy constructor
  PolygonVect::PolygonVect(vector<Polygon::Point2D> &pointVec) throw(): Polygon(pointVec){
    for(int i = 0; i < getCapacity(); i++)
      points.push_back(pointVec[i]);
  }
  PolygonVect::PolygonVect(Point2D& pointObj) throw(): Polygon(pointObj){
    points.push_back(pointObj);
  }//From a two 2D point
  PolygonVect::PolygonVect(Rectangle& rect) throw(std::domain_error):Polygon(rect){
    points.push_back(Polygon::Point2D(rect.getInitX(), rect.getInitY()));
    points.push_back(Polygon::Point2D(rect.getInitX(), rect.getInitY() + rect.getHeight()));
    points.push_back(Polygon::Point2D(rect.getInitX() + rect.getWidth(), rect.getInitY() + rect.getHeight()));
    points.push_back(Polygon::Point2D(rect.getInitX() + rect.getWidth(), rect.getInitY()));
  }//From Rectangle
  PolygonVect::PolygonVect(Triangle& triang) throw(std::domain_error):Polygon(triang){
    points.push_back(Polygon::Point2D(triang.getP1(), triang.getP2()));
    points.push_back(Polygon::Point2D(triang.getP3(), triang.getP4()));
    points.push_back(Polygon::Point2D(triang.getP5(), triang.getP6()));
  }//From Triangle
  PolygonVect::PolygonVect(Circle& circ) throw(std::domain_error):Polygon(circ){
    double angle = (2 * M_PI) / 100;
    double init_angle = 0;
    for(int i = 0; i < getCapacity(); i++){
      points.push_back(Polygon::Point2D((circ.getRadius() * cos(init_angle)) + circ.getInitX(), (circ.getRadius() * sin(init_angle)) + circ.getInitY()));
      init_angle += angle;
    }
  }//From Circle
  PolygonVect& PolygonVect::operator =(const PolygonVect& assingPol) throw(std::domain_error){
    setCapacity(assingPol.getCapacity());
    for(int i=0; i < getCapacity(); i++){
      points.push_back(assingPol[i]);
    }
    return *this;
  }

  PolygonVect::~PolygonVect() throw(){
    points.clear();
  }
  Polygon::Point2D& PolygonVect::operator [](int index) throw(std::out_of_range){
    if(index >= getCapacity()){
      throw std::out_of_range("Index out of range.\n");
    }
    return points[index];
  }
  const Polygon::Point2D& PolygonVect::operator [](int index) const throw(std::out_of_range){
    if(index >= getCapacity()){
      throw std::out_of_range("Index out of range.\n");
    }
    return points[index];
  }//[] overoading
  bool PolygonVect::operator ==(const PolygonVect& otherPoly) const throw(){
    if(getCapacity() != otherPoly.getCapacity()){
      return false;
    }
    for(int i = 0; i < getCapacity(); i++){
      if((points[i].getX() != otherPoly[i].getX()) && (points[i].getY() != otherPoly[i].getY())){
        return false;
      }
    }
    return true;
  }

  bool PolygonVect::operator !=(const PolygonVect& otherPoly) const throw(){
    if(getCapacity() != otherPoly.getCapacity()){
      return true;
    }
    for(int i = 0; i < getCapacity(); i++){
      if((points[i].getX() == otherPoly[i].getX()) && (points[i].getY() == otherPoly[i].getY())){
        return false;
      }
    }
    return true;
  }
  const PolygonVect PolygonVect::operator +(const PolygonVect& otherPoly) const throw(){
    vector<Polygon::Point2D> newObj;
    if(getCapacity() > otherPoly.getCapacity()){
      for(int i = 0; i < otherPoly.getCapacity(); i++){
        Point2D obj(points[i].getX() + otherPoly[i].getX(), points[i].getY() + otherPoly[i].getY());
        newObj.push_back(obj);
      }
      for(int j = otherPoly.getCapacity() + 1; j < getCapacity(); j++){
        Point2D obj_2(points[j].getX() + otherPoly[j].getX(), points[j].getY() + otherPoly[j].getY());
        newObj.push_back(obj_2);
      }

      return PolygonVect{newObj};

    } else if(getCapacity() < otherPoly.getCapacity()){
      for(int i = 0; i < getCapacity(); i++){
        Polygon::Point2D obj(points[i].getX() + otherPoly[i].getX(), points[i].getY() + otherPoly[i].getY());
        newObj.push_back(obj);
      }
      for(int j = getCapacity() + 1; j < otherPoly.getCapacity(); j++){
        Polygon::Point2D obj_2(points[j].getX() + otherPoly[j].getX(), points[j].getY() + otherPoly[j].getY());
        newObj.push_back(obj_2);
      }

      return PolygonVect{newObj};

    } else{
      for(int i = 0; i < getCapacity(); i++){
        Polygon::Point2D obj(points[i].getX() + otherPoly[i].getX(), points[i].getY() + otherPoly[i].getY());
        newObj.push_back(obj);
      }

      return PolygonVect{newObj};
    }
  }
  void PolygonVect::print(ostream& outputStream) const throw(){//Overrided print function
    outputStream << "<polygon points=\"";
    for(int i = 0; i < getCapacity(); i++){
      outputStream << points[i].getX() << "," << points[i].getY() << " ";
    }
    outputStream << "\" fill=\"red\" stroke=\"black\"/>\n";
  }

}
