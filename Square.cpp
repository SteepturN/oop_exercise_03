#include <vector>
#include "Figure.cpp"
#include <utility>
#include <iostream>
#define NUM_OF_VERTECES_OF_SQUARE 3
class Square : public Figure {
	public:
	std::pair<double, double> center() const noexcept override {
		std::pair<double, double> _center(verteces[0]);
		for(int i = 1; i < NUM_OF_VERTECES_OF_SQUARE; ++i) {
			_center.first+=verteces[i].first;
			_center.second+=verteces[i].second;
		}
		_center.first/=NUM_OF_VERTECES_OF_SQUARE;
		_center.second/=NUM_OF_VERTECES_OF_SQUARE;
		return _center;
	}
	void coordinates() const noexcept override{
		for(int i = 0; i < NUM_OF_VERTECES_OF_SQUARE; ++i)
			std::cout << '(' << verteces[i].first << ", " << verteces[i].second << ')';
	}
	double area() const noexcept override{
		double area(0);
		for(int i = 0; i< NUM_OF_VERTECES_OF_SQUARE; ++i) {
			area+=	verteces[i].first	*	verteces[(i+1)%NUM_OF_VERTECES_OF_SQUARE].second	-	\
				verteces[(i+1)%NUM_OF_VERTECES_OF_SQUARE].first	*	verteces[i].second;
		}
		area/=2;
		return area>0?area:-area;
	}
};
