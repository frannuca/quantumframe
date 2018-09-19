#include "derivatives.h"
#include <boost/math/tools/numerical_differentiation.hpp>

using namespace arma;

double optim::compute_first_derivative(std::function<double(const double&)> f, const double & x)
{
	double error_estimate;
	return boost::math::tools::finite_difference_derivative<decltype(f),double,6>(f, x,&error_estimate);
}


vec optim::compute_gradient(ObjectiveFunction feval, const vec & x)
{
	vec g(x.size());
	for (int i = 0; i < g.size(); ++i) {
		auto f_i = [&](const double& s) {
			vec v = x;
			v[i] = s;
			return feval(v);
		};

		g[i] = compute_first_derivative(f_i, x[i]);
	}
	return g;
}

mat optim::compute_hessian(ObjectiveFunction feval, const vec & x)
{
	{
		using namespace std::placeholders;

		int N = x.size();
		mat H(N, N);
		auto fij = [&x,&feval](double i, double j, double xi, double xj) {
			vec v = x;
			double di = xi - x[i];
			double dj = xj - x[j];
			v[i] += di;
			v[j] += dj;
			return feval(v);
		};
		
		for (int i = 0; i < N; ++i) {			
			
			for (int j = i; j < N; ++j) {
				
				auto di = [fij, i, j,x](const double xj) {return compute_first_derivative(std::bind(fij, i, j, _1, xj),x[i]); };
				auto dij = compute_first_derivative(di, x[j]);
				H(i, j) = dij;
				if (i != j) {
					H(j, i) = H(i, j);
				}
			}
		}
		return H;

	}
}

mat optim::compute_jacobian(ObjectiveVectorFunction feval, const vec & x)
{
	int N = x.size();
	mat J(N, N);
	for (int i = 0; i < N; ++i) {
		auto g = compute_gradient([&feval, i](decltype(x) v) {return feval(v)[i]; },x);
		for (int j = 0; j < N; ++j) {
			J(i, j) = g[j];
		}
	}
	return J;
	
}
