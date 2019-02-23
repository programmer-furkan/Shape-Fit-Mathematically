MyProgram : circle.o 161044001_main.o composedShape.o rectangle.o triangle.o polygon.o polygonDyn.o polygonVect.o shape.o
	g++ -o MyProgram shape.o circle.o 161044001_main.o composedShape.o rectangle.o triangle.o polygon.o polygonDyn.o polygonVect.o

circle.o : circle.cpp
	g++ -c -std=c++0x -Wall circle.cpp

polygon.o : polygon.cpp
	g++ -c -std=c++0x -Wall polygon.cpp

polygonDyn.o : polygonDyn.cpp
	g++ -c -std=c++0x -Wall polygonDyn.cpp

polygonVect.o : polygonVect.cpp
	g++ -c -std=c++0x -Wall polygonVect.cpp

161044001_main.o : 161044001_main.cpp
	g++ -c -std=c++0x -Wall 161044001_main.cpp

composedShape.o : composedShape.cpp
	g++ -c -std=c++0x -Wall composedShape.cpp

rectangle.o : rectangle.cpp
	g++ -c -std=c++0x -Wall rectangle.cpp

triangle.o : triangle.cpp
	g++ -c -std=c++0x -Wall triangle.cpp

shape.o : shape.cpp
	g++ -c -std=c++0x -Wall shape.cpp

clean:
	rm *.o MyProgram
