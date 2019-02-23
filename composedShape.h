#ifndef COMPOSED_H
#define COMPOSED_H
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "shape.h"
using namespace std;
//namespace declerations
namespace Triangle { class Triangle; }
namespace Circle { class Circle; }
namespace Rectangle { class Rectangle; }
namespace GeneralShape{ class Shape; }

namespace ComposedShape{
	//Using directives
	using Rectangle::Rectangle;
	using Circle::Circle;
	using Triangle::Triangle;
	using GeneralShape::Shape;
class ComposedShape : public Shape{
private:
	Rectangle big_rect;
	Circle big_circ;
	Triangle big_triang;
	Rectangle small_rect;
	Circle small_circ;
	Triangle small_triang;
	char container, inside;
	vector<Shape*> shapes;
public:
	vector<Shape*>& getShape() throw();
	double getArea() const throw();
	double getPerimeter() const throw();
	void print(ostream& outputStream) const throw();
	/*Constructors according to given shapes*/
	ComposedShape() throw() ;
	ComposedShape(Rectangle big_r, Rectangle small_r) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Rectangle big_r, Circle small_c) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Rectangle big_r, Triangle small_t) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Circle big_c, Rectangle small_r) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Circle big_c, Circle small_c) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Circle big_c, Triangle small_t) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Triangle big_t, Rectangle small_r) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Triangle big_t, Circle small_c) throw(std::bad_alloc, std::domain_error);
	ComposedShape(Triangle big_t, Triangle small_t) throw(std::bad_alloc, std::domain_error);


	void optimalFit() throw(std::bad_alloc, std::domain_error);
	//Optimal Fit's according to given constructor
	void optimalFitRectAndRect(Rectangle big_rect, Rectangle small_rect) throw(std::bad_alloc, std::domain_error);

	void optimalFitRectAndCirc(Rectangle big_rect, Circle small_circ) throw(std::bad_alloc, std::domain_error);

	void optimalFitRectAndTriang(Rectangle big_rect, Triangle small_triang) throw(std::bad_alloc, std::domain_error);

	void optimalFitCircAndCirc(Circle big_circ, Circle small_circ) throw(std::bad_alloc, std::domain_error);

	void optimalFitCircAndRect(Circle big_circ, Rectangle small_rect) throw(std::bad_alloc, std::domain_error);

	void optimalFitCircAndTriang(Circle big_circ, Triangle small_triang) throw(std::bad_alloc, std::domain_error);

	void optimalFitTriangAndRect(Triangle big_triang, Rectangle small_rect) throw(std::bad_alloc, std::domain_error);

	void optimalFitTriangAndCirc(Triangle big_triang, Circle small_circ) throw(std::bad_alloc, std::domain_error);

	void optimalFitTriangAndTriang(Triangle big_triang, Triangle small_triang) throw(std::bad_alloc, std::domain_error);
};

}

#endif
