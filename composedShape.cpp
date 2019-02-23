#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <vector>
#include "composedShape.h"
#include "triangle.h"
#include "rectangle.h"
#include "circle.h"
#include "shape.h"
using namespace std;


namespace ComposedShape{
/*Constructors runs according to given shapes. Character use for determine parameter of OptimalFit's*/
ComposedShape::ComposedShape() throw(){}
ComposedShape::ComposedShape(Rectangle big_r, Rectangle small_r) throw(std::bad_alloc, std::domain_error):big_rect(big_r), small_rect(small_r){
	container = 'R';
	inside = 'R';
	optimalFit();
}
ComposedShape::ComposedShape(Rectangle big_r, Circle small_c) throw(std::bad_alloc, std::domain_error):big_rect(big_r), small_circ(small_c){
	container = 'R';
	inside = 'C';
	optimalFit();
}
ComposedShape::ComposedShape(Rectangle big_r, Triangle small_t) throw(std::bad_alloc, std::domain_error):big_rect(big_r), small_triang(small_t){
	container = 'R';
	inside = 'T';
	optimalFit();
}
ComposedShape::ComposedShape(Circle big_c, Rectangle small_r) throw(std::bad_alloc, std::domain_error):big_circ(big_c), small_rect(small_r){
	container = 'C';
	inside = 'R';
	optimalFit();
}
ComposedShape::ComposedShape(Circle big_c, Circle small_c) throw(std::bad_alloc, std::domain_error):big_circ(big_c), small_circ(small_c){
	container = 'C';
	inside = 'C';
	optimalFit();
}
ComposedShape::ComposedShape(Circle big_c, Triangle small_t) throw(std::bad_alloc, std::domain_error):big_circ(big_c), small_triang(small_t){
	container = 'C';
	inside = 'T';
	optimalFit();
}
ComposedShape::ComposedShape(Triangle big_t, Rectangle small_r) throw(std::bad_alloc, std::domain_error):big_triang(big_t), small_rect(small_r){
	container = 'T';
	inside = 'R';
	optimalFit();
}
ComposedShape::ComposedShape(Triangle big_t, Circle small_c) throw(std::bad_alloc, std::domain_error):big_triang(big_t), small_circ(small_c){
	container = 'T';
	inside = 'C';
	optimalFit();
}
ComposedShape::ComposedShape(Triangle big_t, Triangle small_t) throw(std::bad_alloc, std::domain_error):big_triang(big_t), small_triang(small_t){
	container = 'T';
	inside = 'T';
	optimalFit();
}

inline vector<Shape*>& ComposedShape::getShape() throw() { return shapes; }
double ComposedShape::getArea() const throw() { return 0; }
double ComposedShape::getPerimeter() const throw() { return 0; }
void ComposedShape::print(ostream& outputStream) const throw(){ return; }

void ComposedShape::optimalFit() throw(std::bad_alloc, std::domain_error){
	if(container == 'R' && inside == 'R'){
		optimalFitRectAndRect(big_rect, small_rect);
	} else if(container == 'R' && inside == 'C'){
		optimalFitRectAndCirc(big_rect, small_circ);
	} else if(container == 'R' && inside == 'T'){
		optimalFitRectAndTriang(big_rect, small_triang);
	} else if(container == 'C' && inside == 'C'){
		optimalFitCircAndCirc(big_circ, small_circ);
	} else if(container == 'C' && inside == 'R'){
		optimalFitCircAndRect(big_circ, small_rect);
	} else if(container == 'C' && inside == 'T'){
		optimalFitCircAndTriang(big_circ, small_triang);
	} else if(container == 'T' && inside == 'R'){
		optimalFitTriangAndRect(big_triang, small_rect);
	} else if(container == 'T' && inside == 'C'){
		optimalFitTriangAndCirc(big_triang, small_circ);
	} else if(container == 'T' && inside == 'T'){
		optimalFitTriangAndTriang(big_triang, small_triang);
	}
}

void ComposedShape::optimalFitRectAndRect(Rectangle big_rect, Rectangle small_rect) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output1.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<rect x=\"" << big_rect.getInitX() <<"\" y=\"" << big_rect.getInitY() << "\" width=\"" << big_rect.getWidth() << "\" " << "height=\"" << big_rect.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	int rectNumber = 0;
	while((small_rect.getInitY() + small_rect.getHeight()) <= big_rect.getHeight()){//Repeat before add last shape
		while((small_rect.getInitX() + small_rect.getWidth()) <= big_rect.getWidth()){//Repeat until reach edge of big container
			Rectangle pushed(small_rect.getWidth(), small_rect.getHeight(), small_rect.getInitX(), small_rect.getInitY());//Construct small object
			Shape* sp1 = new Rectangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1; //Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			small_rect.setInitX(small_rect.getInitX() + small_rect.getWidth());
			rectNumber++;
		}
		//Reset coordinate
		small_rect.setInitX(0);
		//Increase total y
		small_rect.setInitY(small_rect.getInitY() + small_rect.getHeight());
	}

	cout << "I can fit at most " << rectNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>" << endl;
}

void ComposedShape::optimalFitRectAndCirc(Rectangle big_rect, Circle small_circ) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output2.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<rect x=\"" << big_rect.getInitX() <<"\" y=\"" << big_rect.getInitY() << "\" width=\"" << big_rect.getWidth() << "\" " << "height=\"" << big_rect.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	int circleNumber = 0; //Shape number can be found by multiplying these numbers
	small_circ.setInitX(small_circ.getRadius());
	small_circ.setInitY(small_circ.getRadius());
	while(small_circ.getInitY() <= big_rect.getHeight() - small_circ.getRadius()){
		while(small_circ.getInitX() <= big_rect.getWidth() - small_circ.getRadius()){
			Circle pushed(small_circ.getRadius(), small_circ.getInitX(), small_circ.getInitY());//Construct small object
			Shape* sp1 = new Circle(pushed);//Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			small_circ.setInitX(small_circ.getInitX() + small_circ.getDiameter());
			circleNumber++;
		}
		small_circ.setInitX(small_circ.getRadius());
		small_circ.setInitY(small_circ.getInitY() + small_circ.getDiameter());
	}
	cout << "I can fit at most " << circleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>" << endl;
	myFile.close();
}

void ComposedShape::optimalFitRectAndTriang(Rectangle big_rect, Triangle small_triang) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output3.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<rect x=\"" << big_rect.getInitX() <<"\" y=\"" << big_rect.getInitY() << "\" width=\"" << big_rect.getWidth() << "\" " << "height=\"" << big_rect.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	int triangleNumber = 0; //Shape number can be found by multiplying these numbers
	double initial_side = small_triang.getSide(), initial_mid = small_triang.getSide()/2, initial_height = small_triang.getHeight();
	small_triang.setInitX(0);
	small_triang.setInitY(0);
	while(small_triang.getInitY() <= big_rect.getHeight() - small_triang.getHeight()){
		while(small_triang.getInitX() <= big_rect.getWidth() - small_triang.getSide()){
			Triangle pushed{small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), small_triang.getInitX(), initial_height, initial_mid, small_triang.getInitY(), initial_side, initial_height};//Construct small object
			Shape* sp1 = new Triangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			triangleNumber++;
			if(big_rect.getWidth() - (small_triang.getInitX() + small_triang.getSide()) >= small_triang.getSide()){ //Reverse triangles
				Triangle pushed_2{small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), initial_mid, small_triang.getInitY(), initial_side, initial_height, (initial_mid + small_triang.getSide()), small_triang.getInitY()};//Construct small object
				Shape* sp2 = new Triangle(pushed_2); //Convert object to base class pointer
				if(sp2 == NULL)
					throw std::bad_alloc();
				myFile << sp2;//Write file with overloaded operator
				getShape().push_back(sp2);//Push inside the vector of Shape Pointer
				triangleNumber++;
			}
			small_triang.setInitX(small_triang.getInitX() + small_triang.getSide());
			initial_mid = initial_mid + small_triang.getSide();
			initial_side = initial_side + small_triang.getSide();
		}
		//Reset x and increase total y
		small_triang.setInitY(small_triang.getInitY() + small_triang.getHeight());
		initial_height = initial_height + small_triang.getHeight();
		small_triang.setInitX(0);
		initial_side = small_triang.getSide();
		initial_mid = small_triang.getSide()/2;
	}
	cout << "I can fit at most " << triangleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitCircAndRect(Circle big_circ, Rectangle small_rect) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output4.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<circle cx=\""<< big_circ.getRadius() << "\" " << "cy=\"" << big_circ.getRadius() << "\" " << "r=\"" << big_circ.getRadius() << "\" " << "fill=\"green\"/>" << endl;
	int rectNumber = 0;
	//Find largest rectangle that can fit in a circle
	double largest_square_side = big_circ.getRadius() * sqrt(2);
	//Determine initial x and y according to largest rectangle
	small_rect.setInitY(big_circ.getRadius() - ((big_circ.getRadius() * sqrt(2))/2));
	small_rect.setInitX(big_circ.getRadius() - ((big_circ.getRadius() * sqrt(2))/2));
	double control = largest_square_side + (big_circ.getRadius() - ((big_circ.getRadius() * sqrt(2))/2));
	while((small_rect.getInitY() + small_rect.getHeight()) <= control){ //Repeat before add last shape
		while((small_rect.getInitX() + small_rect.getWidth()) <= control){
			Rectangle pushed(small_rect.getWidth(), small_rect.getHeight(), small_rect.getInitX(), small_rect.getInitY());//Construct small object
			Shape* sp1 = new Rectangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			small_rect.setInitX(small_rect.getInitX() + small_rect.getWidth());
			rectNumber++;
		}
		//Reset coordinate
		small_rect.setInitX(big_circ.getRadius() - ((big_circ.getRadius() * sqrt(2))/2));
		//Increase total y
		small_rect.setInitY(small_rect.getInitY() + small_rect.getHeight());
	}
	cout << "I can fit at most " << rectNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitCircAndCirc(Circle big_circ, Circle small_circ) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output5.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<circle cx=\""<< big_circ.getRadius() << "\" " << "cy=\"" << big_circ.getRadius() << "\" " << "r=\"" << big_circ.getRadius() << "\" " << "fill=\"green\"/>" << endl;
	int circleNumber = 0;
	double newCenter = big_circ.getRadius() - small_circ.getRadius(); //Small circles start tanget to big circle and
	double numberOfCircles;
	double angle; //Angle increment for new small circles center
	double trace = 0;
	while(newCenter >= small_circ.getDiameter()){
		numberOfCircles = floor((2 * M_PI * newCenter) / (2 * small_circ.getRadius())); //Finding angle for new centers
		angle = 360 / numberOfCircles; //Finding angle for new centers
		while(trace <= 360){
			Circle pushed(small_circ.getRadius(),(big_circ.getRadius() - (newCenter * cos((trace * M_PI) / 180))) , (big_circ.getRadius() - (newCenter * sin((trace * M_PI) / 180))));//Construct small object
			Shape* sp1 = new Circle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			trace = trace + angle;//Add angle for new center
			circleNumber++;
		}
		newCenter = newCenter - (2 * small_circ.getRadius());//Push off new centers inside of big circle center
		trace = 0;
	}
	circleNumber += 1; //Add manual circle to total
	cout << "I can fit at most " << circleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitCircAndTriang(Circle big_circ, Triangle small_triang) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output6.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<circle cx=\""<< big_circ.getRadius() << "\" " << "cy=\"" << big_circ.getRadius() << "\" " << "r=\"" << big_circ.getRadius() << "\" " << "fill=\"green\"/>" << endl;
	int triangleNumber = 0;
	double insideTriangleHeight = big_circ.getRadius() * (sqrt(3)/2); //hexagon triangle lenght
	double initial_x1 = small_triang.getInitX(), initial_x2 = small_triang.getInitX(); //Starting coordinates
	double initial_y1 = big_circ.getRadius(), initial_y2 = big_circ.getRadius(); //Starting coordinates
	double iter_x = small_triang.getSide()/2; //Top point coordinate x of small shape
	double iter_x_initial = iter_x; //Covering iter_x value
	int control = (2 * big_circ.getRadius()) / small_triang.getSide(); //Control condition for avoiding overflow
	int loop = 1; //Loop increment percentage
	while(initial_y1 > big_circ.getRadius() - insideTriangleHeight + small_triang.getHeight()){
		for (int i = 0; i < control; ++i){
			//Pushing coordinates to vector
			Triangle pushed(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), initial_x1, initial_y1, iter_x, (initial_y1 - small_triang.getHeight()), (iter_x + iter_x_initial), initial_y1);//Construct small object
			Shape* sp1 = new Triangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			triangleNumber++;
			if(control - 1 > i){ //Every row reverse triangle must be one shape lack of normal triangles
				Triangle pushed_2(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), iter_x, (initial_y1 - small_triang.getHeight()), (iter_x + iter_x_initial), initial_y1, (iter_x + small_triang.getSide()), (initial_y1 - small_triang.getHeight()));//Construct small object
				Shape* sp2 = new Triangle(pushed_2); //Convert object to base class pointer
				if(sp2 == NULL)
					throw std::bad_alloc();
				myFile << sp2;//Write file with overloaded operator
				getShape().push_back(sp2);//Push inside the vector of Shape Pointer
				triangleNumber++;
			}
			initial_x1 += small_triang.getSide(); //Next shape's x coordinate push off by side lenght of small shape
			iter_x += small_triang.getSide(); //Next shape's iter_x push off by side lenght of small shape
		}
		initial_x1 = 0; //Reset inital
		initial_x1 = iter_x_initial*loop; //Increment proportional with row
		iter_x = iter_x_initial; //Reset initial iter
		iter_x += iter_x_initial * loop; //Increment proportional with row
		initial_y1 = initial_y1 - small_triang.getHeight(); //Every next row decrease y coordinate by height of small shape
		control--;
		loop++;
	}
	//******************--Reset all initial values and make progress reversely until reach bottom of circle--***********************
	iter_x = iter_x_initial;
	loop = 1;
	control = (2 * big_circ.getRadius()) / small_triang.getSide();
	while(initial_y2 < big_circ.getRadius() + insideTriangleHeight - small_triang.getHeight()){
		for (int i = 0; i < control; ++i){
			Triangle pushed_3(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), initial_x2, initial_y2, iter_x, (initial_y2 + small_triang.getHeight()), (iter_x + iter_x_initial), initial_y2);//Construct small object
			Shape* sp3 = new Triangle(pushed_3); //Convert object to base class pointer
			if(sp3 == NULL)
				throw std::bad_alloc();
			myFile << sp3;//Write file with overloaded operator
			getShape().push_back(sp3);//Push inside the vector of Shape Pointer
			triangleNumber++;
			if(control - 1 > i){
				Triangle pushed_4(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), iter_x, (initial_y2 + small_triang.getHeight()), (iter_x + iter_x_initial), initial_y2, (iter_x + small_triang.getSide()), (initial_y2 + small_triang.getHeight()));//Construct small object
				Shape* sp4 = new Triangle(pushed_4); //Convert object to base class pointer
				if(sp4 == NULL)
					throw std::bad_alloc();
				myFile << sp4;//Write file with overloaded operator
				getShape().push_back(sp4);//Push inside the vector of Shape Pointer
				triangleNumber++;
			}
			initial_x2 += small_triang.getSide();
			iter_x += small_triang.getSide();
		}
		initial_x2 = 0;
		initial_x2 = iter_x_initial*loop;
		iter_x = iter_x_initial;
		iter_x += iter_x_initial * loop;
		initial_y2 = initial_y2 + small_triang.getHeight();
		control--;
		loop++;
	}
	cout << "I can fit at most " << triangleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitTriangAndRect(Triangle big_triang, Rectangle small_rect) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output7.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<polygon points=\"" << 0 << " " << big_triang.getHeight() << ", "  << big_triang.getSide()/2 << " " << 0 << ", " << big_triang.getSide() << " " << big_triang.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	small_rect.setInitX(small_rect.getHeight() / sqrt(3)); //Finding first shape x coordinate
	small_rect.setInitY(big_triang.getHeight() - small_rect.getHeight()); //Finding first shape y coordinate
	double control = big_triang.getSide() - small_rect.getInitX(); //Control condition for avoiding overflow
	int rectNumber = 0; //Small shape counter
	int increment = 1; // For every row we need to reset initial data and set back initial_x values since we should make increment proportional to row.
	while(small_rect.getInitY() > 0){ //Total small shapes height must be smaller than container shape height
		while(control > small_rect.getInitX() + small_rect.getWidth()){ //Iterate until overflow happen
			Rectangle pushed(small_rect.getWidth(), small_rect.getHeight(), small_rect.getInitX(), small_rect.getInitY());//Construct small object
			Shape* sp1 = new Rectangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			small_rect.setInitX(small_rect.getWidth() + small_rect.getInitX()); //Next shape's x coordinate puss off by width of small shape
			rectNumber++;
		}
		small_rect.setInitY(small_rect.getInitY() - small_rect.getHeight()); //Every next row decrease y coordinate by height of small shape
		increment++;
		small_rect.setInitX((small_rect.getHeight() / sqrt(3)) * increment); //reset inital_x proportional with (small_h / sqrt(3))
		control -= (small_rect.getHeight() / sqrt(3)); //Control must decrease same percentage
	}
	cout << "I can fit at most " << rectNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitTriangAndCirc(Triangle big_triang, Circle small_circ) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output8.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<polygon points=\"" << 0 << " " << big_triang.getHeight() << ", "  << big_triang.getSide()/2 << " " << 0 << ", " << big_triang.getSide() << " " << big_triang.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	int circleNumber = 0; //Small shape counter
	small_circ.setInitX(small_circ.getRadius() * sqrt(3)); //First shape's initial x coordinate
	double coord_x;
	double horizontal = small_circ.getInitX(); //Covering first_x coordinate for next usings
	double first_y = big_triang.getHeight() - small_circ.getRadius(); //First shape's initial y coordinate
	double control = big_triang.getSide() - small_circ.getInitX(); //Control condition for avoiding overflow
	while(first_y > (small_circ.getRadius() * 2)){
		coord_x = horizontal;
    	while(coord_x < control){
		Circle pushed(small_circ.getRadius(), coord_x, first_y);//Construct small object
		Shape* sp1 = new Circle(pushed); //Convert object to base class pointer
		if(sp1 == NULL)
			throw std::bad_alloc();
		myFile << sp1;//Write file with overloaded operator
		getShape().push_back(sp1);//Push inside the vector of Shape Pointer
    	  	coord_x += 2 * small_circ.getRadius(); //Next shape's x coordinate push off by diameter of small shape
    	  	circleNumber++;
    	}
    	horizontal += small_circ.getRadius(); //Next initial x coordinate push off by radius of small shape
    	first_y = first_y - small_circ.getInitX(); // next y coordinate of small shape decrease by small_r * sqrt(3)
    	control -= small_circ.getRadius();  //Control must decrease same percentage
  	}
	cout << "I can fit at most " << circleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}

void ComposedShape::optimalFitTriangAndTriang(Triangle big_triang, Triangle small_triang) throw(std::bad_alloc, std::domain_error){
	ofstream myFile;//File open for output SVG file
	myFile.open("output9.svg");
	myFile << "<svg width=\"100%\" height=\"100%\" xmlns=\"http://www.w3.org/2000/svg\">"<< endl;
	myFile << "<polygon points=\"" << 0 << " " << big_triang.getHeight() << ", "  << big_triang.getSide()/2 << " " << 0 << ", " << big_triang.getSide() << " " << big_triang.getHeight() << "\" " << "fill=\"green\"/>" << endl;
	int triangleNumber = 0; //Small shape counter
	small_triang.setInitY(big_triang.getHeight()); //Initial y same with big container
	double iter_x = small_triang.getSide()/2; //Top point coordinate x of small shape
	double iter_x_initial = iter_x; //Covering iter value for next using
	small_triang.setInitX(0); //Initial x same with big container
	int control = big_triang.getSide() / small_triang.getSide(); //Control condition for avoiding overflow
	int loop = 1; // For every row we need to reset initial data and set back initial_x values since we should make increment proportional to row.
	while(small_triang.getInitY() > 0){
		for (int i = 0; i < control; ++i){
			Triangle pushed(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), small_triang.getInitX(), small_triang.getInitY(), iter_x, (small_triang.getInitY() - small_triang.getHeight()), (iter_x + iter_x_initial), small_triang.getInitY());//Construct small object
			Shape* sp1 = new Triangle(pushed); //Convert object to base class pointer
			if(sp1 == NULL)
				throw std::bad_alloc();
			myFile << sp1;//Write file with overloaded operator
			getShape().push_back(sp1);//Push inside the vector of Shape Pointer
			triangleNumber++;
			if(control - 1 > i){ //Every row reverse triangle must be one shape lack of normal triangles
				//Pushing coordinates to vector
				Triangle pushed_2(small_triang.getSide(), small_triang.getInitX(), small_triang.getInitY(), iter_x, (small_triang.getInitY() - small_triang.getHeight()), (iter_x + iter_x_initial), small_triang.getInitY(), (iter_x + small_triang.getSide()), (small_triang.getInitY() - small_triang.getHeight()));//Construct small object
				Shape* sp2 = new Triangle(pushed_2); //Convert object to base class pointer
				if(sp2 == NULL)
					throw std::bad_alloc();
				myFile << (sp2);//Write file with overloaded operator
				getShape().push_back(sp2);//Push inside the vector of Shape Pointer
				triangleNumber++;
			}
			small_triang.setInitX(small_triang.getInitX() + small_triang.getSide()); //Next shape's x coordinate push off by side lenght of small shape
			iter_x += small_triang.getSide(); //Next shape's iter_x coordinate push off by side lenght of small shape
		}
		small_triang.setInitX(0); //Reseting for next row
		small_triang.setInitX(iter_x_initial*loop); ////Next shape's x coordinate puss off with proportional to row number
		iter_x = iter_x_initial; //Reseting initial iter
		iter_x += iter_x_initial * loop; ///Next shape's x coordinate puss off with proportional to row number
		small_triang.setInitY(small_triang.getInitY() - small_triang.getHeight()); //Every next row decrease y coordinate by height of small shape
		control--;
		loop++;
	}
	cout << "I can fit at most " << triangleNumber <<" small shapes into the main container. The empty area (red) in container is ";
	myFile << "</svg>";
}
}
