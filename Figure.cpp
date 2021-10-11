#include <utility>
#ifndef __FIGURE__
#define __FIGURE__
class Figure {
	public:
	virtual std::pair<double, double> center() const noexcept = 0;
	virtual void coordinates() const noexcept = 0;
	virtual double area() const noexcept = 0;
	std::vector<std::pair<double, double>> verteces;
};
#endif
