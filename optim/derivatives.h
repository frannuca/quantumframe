#pragma once
#include "exports_optim.h"
#include <functional>
#include "armadillo.h"

namespace optim {
	using namespace arma;
	using ObjectiveFunction = std::function<double(const vec&)>;
	using ObjectiveVectorFunction = std::function<vec(const vec&)>;
	EXPORT_OPTIM double compute_first_derivative(std::function<double(const double&)>f, const double &x);
	
	EXPORT_OPTIM void foo();
	
	EXPORT_OPTIM vec compute_gradient(ObjectiveFunction feval,const vec &x);
	EXPORT_OPTIM mat compute_hessian(ObjectiveFunction feval, const vec &x);
	EXPORT_OPTIM mat compute_jacobian(ObjectiveVectorFunction feval, const vec &x);
}
