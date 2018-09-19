#include "../optim/derivatives.h"
#include <functional>
#include "../optim/armadillo.h"

using namespace arma;

int main() {
	auto f = [](const vec &x)
	{
		auto a = x[0];
		auto b = x[1];
		auto s= (x[0])*(x[0]) + (x[1])*(x[1]); 
		return s;
	};
	vec x0(2);
	x0[0] = 1.0;
	x0[1] = 1.0;
	auto df = optim::compute_gradient(f, x0);
	auto h = optim::compute_hessian(f, x0);
	
	std::cout << df << std::endl;
	std::cout << h << std::endl;


}