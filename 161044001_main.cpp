#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <algorithm>
#include <exception>
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"
#include "composedShape.h"
#include "polygonDyn.h"
#include "polygonVect.h"
using namespace std;


//Namespace directives
using Triangle::Triangle;
using Circle::Circle;
using Rectangle::Rectangle;
using ComposedShape::ComposedShape;
using GeneralShape::Shape;
using Polygon::Polygon;
using PolygonDyn::PolygonDyn;
using PolygonVect::PolygonVect;

void printAll(vector<Shape*> shapes, ostream& file) throw(){//Takes pointer and writes to file
	for(unsigned int i = 0; i < shapes.size(); i++){
		file << shapes[i];
	}
}

void printPoly(vector<Shape*> shapes, ostream& file) throw (std::bad_cast){
	//First try to make cast. If cast is succesful downcast pointer and and make operations on derived object pointer. Otherwise throw bad_cast
	for(unsigned int i = 0; i < shapes.size(); i++){
		if(dynamic_cast<Rectangle::Rectangle* >(shapes[i])){
			Rectangle::Rectangle* rp = new Rectangle::Rectangle;
			rp = dynamic_cast<Rectangle::Rectangle* >(shapes[i]);
			PolygonVect::PolygonVect a(*rp);
			a.print(file);
		} else if(dynamic_cast<Triangle::Triangle* >(shapes[i])){
				Triangle::Triangle* tp = new Triangle::Triangle;
				tp = dynamic_cast<Triangle::Triangle* >(shapes[i]);
				PolygonVect::PolygonVect a(*tp);
				a.print(file);
		} else if(dynamic_cast<Circle::Circle* >(shapes[i])){
				Circle::Circle* cp = new Circle::Circle;
				cp = dynamic_cast<Circle::Circle* >(shapes[i]);
				PolygonVect::PolygonVect a(*cp);
				a.print(file);
		} else if(dynamic_cast<PolygonVect::PolygonVect* >(shapes[i])){
				PolygonVect::PolygonVect* pvp = new PolygonVect::PolygonVect;
				pvp = dynamic_cast<PolygonVect::PolygonVect* >(shapes[i]);
				file << pvp;
		} else if(dynamic_cast<PolygonDyn::PolygonDyn* >(shapes[i])){
				PolygonDyn::PolygonDyn* pdp = new PolygonDyn::PolygonDyn;
				pdp = dynamic_cast<PolygonDyn::PolygonDyn* >(shapes[i]);
				file << pdp;
		} else {
			throw std::bad_cast();
		}
	}
}

void sortAll(vector<Shape*>& shapes) throw(){
	//Sort elements using bubble sort
	unsigned int i, j;
	for(i = 0; i < (shapes.size() - 1); i++){
		for(j = 0; j < (shapes.size() -i-1); j++){
			if(shapes[j]->getArea() > shapes[j+1]->getArea()){
				swap(shapes[j], shapes[j+1]);
			}
		}
	}
}

vector<PolygonDyn::PolygonDyn> convertAll(vector<Shape*> shapes) throw (std::bad_cast){
		//First try to make cast. If cast is succesful downcast pointer and and make operations on derived object pointer. Otherwise throw bad_cast
	vector<PolygonDyn::PolygonDyn> poly;
	for(unsigned int i = 0; i < shapes.size(); i++){
		if(dynamic_cast<Rectangle::Rectangle* >(shapes[i])){
			Rectangle::Rectangle* rp = new Rectangle::Rectangle;
			rp = dynamic_cast<Rectangle::Rectangle* >(shapes[i]);
			PolygonDyn::PolygonDyn a(*rp);
			poly.push_back(a);
		} else if(dynamic_cast<Triangle::Triangle* >(shapes[i])){
			Triangle::Triangle* tp = new Triangle::Triangle;
			tp = dynamic_cast<Triangle::Triangle* >(shapes[i]);
			PolygonDyn::PolygonDyn a(*tp);
			poly.push_back(a);
		} else if(dynamic_cast<Circle::Circle* >(shapes[i])){
			Circle::Circle* cp = new Circle::Circle;
			cp = dynamic_cast<Circle::Circle* >(shapes[i]);
			PolygonDyn::PolygonDyn a(*cp);
			poly.push_back(a);
		} else if(dynamic_cast<PolygonDyn::PolygonDyn* >(shapes[i])){
				PolygonDyn::PolygonDyn* pdp = new PolygonDyn::PolygonDyn;
				pdp = dynamic_cast<PolygonDyn::PolygonDyn* >(shapes[i]);
				PolygonDyn::PolygonDyn a(*pdp);
				poly.push_back(a);
		} else if(dynamic_cast<PolygonVect::PolygonVect* >(shapes[i])){
				PolygonVect::PolygonVect* pvp = new PolygonVect::PolygonVect;
				pvp = dynamic_cast<PolygonVect::PolygonVect* >(shapes[i]);
				PolygonDyn::PolygonDyn a(*pvp);
				poly.push_back(a);
		} else {
			throw std::bad_cast();
		}
	}
	return poly;
}

int main(){
	using Triangle::Triangle;
	using Circle::Circle;
	using Rectangle::Rectangle;
	using ComposedShape::ComposedShape;
	using GeneralShape::Shape;
	using Polygon::Polygon;
	using PolygonDyn::PolygonDyn;
	using PolygonVect::PolygonVect;
	ofstream myFile, myFile2;//File open for output SVG file
	myFile.open("printAll.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile2.open("printAll2.svg");
	myFile2 << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	vector<Shape*> test;
	try {
		//Elements initiliazing
		Rectangle rect[3] = {Rectangle(), Rectangle(), Rectangle()};
		Triangle triang[3] = {Triangle(), Triangle(), Triangle()};
		Circle circ[3] = {Circle(), Circle(), Circle()};
		rect[0] = {12, 13, 0, 0};
		rect[1] = {234, 123, 0, 0};
		rect[2] = {334, 233, 0, 0};
		triang[0] = {223, 0, 0, 0, 0, 0, 0, 0, 0};
		triang[1] = {34, 0, 0, 0, 0, 0, 0, 0, 0};
		triang[2] = {45, 0, 0, 0, 0, 0, 0, 0, 0};
		circ[0] = {234, 234, 234};
		circ[1] = {23, 23, 23};
		circ[2] = {35, 35, 35};
		PolygonDyn polDyn[3] =  {{rect[0]}, {triang[2]}, {circ[1]}};
		PolygonDyn polVect[3] = {{rect[1]}, {triang[0]}, {circ[2]}};
		ComposedShape comp1(rect[1], rect[0]);
		ComposedShape comp2(circ[0], rect[0]);
		ComposedShape comp3(triang[0], rect[0]);
		ComposedShape comp4(rect[1], triang[1]);
		ComposedShape comp5(circ[0], circ[1]);
		ComposedShape comp6(triang[0], circ[1]);
		ComposedShape comp7(triang[0], rect[0]);
		ComposedShape comp8(circ[0], triang[1]);
		ComposedShape comp9(triang[0], triang[1]);
		test.push_back(&triang[0]);
		test.push_back(&polDyn[2]);
		test.push_back(&polVect[1]);
		test.push_back(&circ[2]);
		test.push_back(&rect[1]);
		cout << endl;
		//Post and prefix test
		cout << (&rect[0]) << endl;
		rect[0]++;
		cout << (&rect[0]) << endl;
		cout << (&triang[1]) << endl;
		++triang[1];
		cout << (&triang[1]) << endl;
		printAll(test, myFile);
		printPoly(test, myFile2);
		cout << "Before sorting according to area order is:";
		for(unsigned int i = 0; i < test.size(); i++)
			cout << test[i]->getArea() << " ";
		cout << endl;
		sortAll(test);
		cout << "After sorting according to area order is:";
		for(unsigned int i = 0; i < test.size(); i++)
			cout << test[i]->getArea() << " ";
		cout << endl;
		convertAll(test);//Converts all shape elements to polygon
	} catch(std::exception& a) {
		cout << a.what() << endl;
	}
	myFile << "</svg>";
	myFile2 << "</svg>";
}
