#include "polygonDyn.h"
#include <iostream>
using namespace std;
namespace PolygonDyn{
  PolygonDyn::PolygonDyn() throw(std::bad_alloc):Polygon(){
    points = new Polygon::Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    points[0] = Polygon::Point2D(0, 0);
  }//No parameter
  PolygonDyn::PolygonDyn(const PolygonDyn& copyPoly) throw(std::bad_alloc, std::domain_error): Polygon(copyPoly){
    points = new Polygon::Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    for(int i = 0; i < getCapacity(); i++){
      points[i] = copyPoly[i];
    }
  }//Copy constructor
  PolygonDyn::PolygonDyn(vector<Polygon::Point2D> &pointVec) throw(std::bad_alloc): Polygon(pointVec){
    points = new Polygon::Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    for(int i = 0; i < getCapacity(); i++)
      points[i] = pointVec[i];
  }
  PolygonDyn::PolygonDyn(Point2D& pointObj) throw(std::bad_alloc): Polygon(pointObj){
    points = new Polygon::Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    points[0] = pointObj;
  }//From a two 2D point
  PolygonDyn::PolygonDyn(Rectangle& rect) throw(std::bad_alloc, std::domain_error):Polygon(rect){
    points = new Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    points[0] = Polygon::Point2D(rect.getInitX(), rect.getInitY());
    points[1] = Polygon::Point2D(rect.getInitX(), rect.getInitY() + rect.getHeight());
    points[2] = Polygon::Point2D(rect.getInitX() + rect.getWidth(), rect.getInitY() + rect.getHeight());
    points[3] = Polygon::Point2D(rect.getInitX() + rect.getWidth(), rect.getInitY());
  }//From Rectangle
  PolygonDyn::PolygonDyn(Triangle& triang) throw(std::bad_alloc, std::domain_error):Polygon(triang){
    points = new Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    points[0] = Polygon::Point2D(triang.getP1(), triang.getP2());
    points[1] = Polygon::Point2D(triang.getP3(), triang.getP4());
    points[2] = Polygon::Point2D(triang.getP5(), triang.getP6());
  }//From Triangle
  PolygonDyn::PolygonDyn(Circle& circ) throw(std::bad_alloc, std::domain_error):Polygon(circ){
    points = new Point2D[getCapacity()];
    if(points == NULL)
      throw std::bad_alloc();
    double angle = (2 * M_PI) / 100;
    double init_angle = 0;
    for(int i = 0; i < getCapacity(); i++){
      points[i] = Polygon::Point2D((circ.getRadius() * cos(init_angle)) + circ.getInitX(), (circ.getRadius() * sin(init_angle)) + circ.getInitY());
      init_angle += angle;
    }
  }//From Circle
  PolygonDyn::PolygonDyn(PolygonVect& vect) throw(std::bad_alloc, std::domain_error):Polygon(){
      points = new Point2D[vect.getCapacity()];
      if(points == NULL)
        throw std::bad_alloc();
      for(int i = 0; i < vect.getCapacity(); i++)
        points[i] = vect[i];
  }


  PolygonDyn& PolygonDyn::operator =(const PolygonDyn& assingPol) throw(std::bad_alloc, std::domain_error){
    if(getCapacity() != assingPol.getCapacity()){
      delete [] points;
      points = new Point2D[assingPol.getCapacity()];
      if(points == NULL)
        throw std::bad_alloc();
    }
    setCapacity(assingPol.getCapacity());
    for(int i=0; i < getCapacity(); i++){
      points[i] = assingPol[i];
    }
    return *this;
  }

  PolygonDyn::~PolygonDyn() throw(){
    delete [] points;
  }
  Polygon::Point2D& PolygonDyn::operator [](int index) throw(std::out_of_range){
    if(index >= getCapacity()){
      throw std::out_of_range("Index out of range.\n");
    }
    return points[index];
  }
  const Polygon::Point2D& PolygonDyn::operator [](int index) const throw(std::out_of_range){
    if(index >= getCapacity()){
      throw std::out_of_range("Index out of range.\n");
    }
    return points[index];
  }//[] overoading
  bool PolygonDyn::operator ==(const PolygonDyn& otherPoly) const throw(){
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

  bool PolygonDyn::operator !=(const PolygonDyn& otherPoly) const throw(){
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
  const PolygonDyn PolygonDyn::operator +(const PolygonDyn& otherPoly) const throw(std::bad_alloc){
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

      return PolygonDyn{newObj};

    } else if(getCapacity() < otherPoly.getCapacity()){
      for(int i = 0; i < getCapacity(); i++){
        Polygon::Point2D obj(points[i].getX() + otherPoly[i].getX(), points[i].getY() + otherPoly[i].getY());
        newObj.push_back(obj);
      }
      for(int j = getCapacity() + 1; j < otherPoly.getCapacity(); j++){
        Polygon::Point2D obj_2(points[j].getX() + otherPoly[j].getX(), points[j].getY() + otherPoly[j].getY());
        newObj.push_back(obj_2);
      }

      return PolygonDyn{newObj};

    } else{
      for(int i = 0; i < getCapacity(); i++){
        Polygon::Point2D obj(points[i].getX() + otherPoly[i].getX(), points[i].getY() + otherPoly[i].getY());
        newObj.push_back(obj);
      }

      return PolygonDyn{newObj};
    }
  }
  void PolygonDyn::print(ostream& outputStream) const throw(){ //Overrided print function
    outputStream << "<polygon points=\"";
    for(int i = 0; i < getCapacity(); i++){
      outputStream << points[i].getX() << "," << points[i].getY() << " ";
    }
    outputStream << "\" fill=\"red\" stroke=\"black\"/>\n";
  }

}
