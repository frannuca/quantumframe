#include "../optim/derivatives.h"
#include <functional>
#include "../optim/armadillo.h"

#include <thread>
#include <chrono>
#include <mutex>
#include <functional>
#include <iostream>
#include <cmath>
#include "../optim/convexoptimizer.h"

typedef struct {
	double a, b;
} my_constraint_data;

int main()
{
	my_constraint_data data[2] = { {2,0}, {-1,1} };
	typedef double function_t(unsigned, const double*, double*, void*);

	auto myconstraint=[](unsigned n, const double *x, double *grad, void *data)
	{
		my_constraint_data *d = (my_constraint_data *)data;
		double a = d->a, b = d->b;
		if (grad) {
			grad[0] = 3 * a * (a*x[0] + b) * (a*x[0] + b);
			grad[1] = -1.0;
		}
		return (a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1];
	};

	auto myfunc= [](unsigned n, const double *x, double *grad, void *my_func_data)
	{
		if (grad) {
			grad[0] = 0.0;
			grad[1] = 0.5 / sqrt(x[1]);
		}
		return sqrt(x[1]);
	};

	optim::ConvexOptimizerBuilder builder;
	auto opt = builder
		.withFitnessFunction(myfunc)
		.withInEquallyConstraint(myconstraint, &data[0])
		.withInEquallyConstraint(myconstraint, &data[1])
		.withLowerBounds({ -100000.0,0 })		
		.withMethod(optim::ConvexOptimizerBuilder::OPTMETHOD::SLSQP).Build();
	opt->mimimize(100, { 1.234, 5.678 }, data);
	return 0;
}
//using namespace arma;
//
//int main() {
//	auto f = [](const vec &x)
//	{
//		auto a = x[0];
//		auto b = x[1];
//		auto s= (x[0])*(x[0]) + (x[1])*(x[1]); 
//		return s;
//	};
//
//	auto fv = [](const vec &x)
//	{
//		vec r(2);
//		r[0] = (x[0])*(x[0]) + (x[1])*(x[1]);
//		r[1] = (x[0])*(x[0])*(x[0]) + (x[1])*(x[1])*(x[1]);
//		return r;
//	};
//	vec x0(2);
//	x0[0] = 1.0;
//	x0[1] = 1.0;
//	auto df = optim::compute_gradient(f, x0);
//	auto h = optim::compute_hessian(f, x0);
//	auto J = optim::compute_jacobian(fv, x0);
//	
//	std::cout << df << std::endl;
//	std::cout << h << std::endl;
//	std::cout << J << std::endl;
//
//	optim::foo();
//}