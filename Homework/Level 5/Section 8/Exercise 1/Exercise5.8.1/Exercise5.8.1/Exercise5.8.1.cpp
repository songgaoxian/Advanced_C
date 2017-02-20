//Exercise5.8.1
//
//test classes of ShapeDecorator hierarchy and Shape hierarchy
//written on 2016/7/1

#include"Shape.hpp"
#include"ShapeComposite.hpp"
#include"ShapeDecorator.hpp"

int main() {
	NameDecorator* nameD= new NameDecorator(new Point(1, 2), "point");
	std::cout << "\nPrint the Shape in nameD:\n";
	std::cout << *dynamic_cast<Point*>(nameD->GetShape()) << '\n';
	std::cout << "Shape's name=" << nameD->GetName() << '\n';

	//change to line
	nameD->SetShape(new Line(Point(1, 2), Point(0, 1)));
	std::cout << "\nPrint the Shape in nameD:\n";
	std::cout << *dynamic_cast<Line*>(nameD->GetShape()) << '\n';
	//change name
	nameD->SetName("line");
	//print name
	std::cout << "Shape's name=" << nameD->GetName() << '\n';
	


	return 0;

}