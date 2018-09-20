#include "derivatives.h"
#include <boost/math/tools/numerical_differentiation.hpp>
#include <nlopt.h>
#include <math.h>

using namespace arma;

double myfunc(unsigned n, const double *x, double *grad, void *my_func_data)
{
	if (grad) {
		grad[0] = 0.0;
		grad[1] = 0.5 / sqrt(x[1]);
	}
	auto a = sqrt(x[1]);
	std::cout << a << std::endl;
	return a;
}

typedef struct {
	double a, b;
} my_constraint_data;

double myconstraint(unsigned n, const double *x, double *grad, void *data)
{
	my_constraint_data *d = (my_constraint_data *)data;
	double a = d->a, b = d->b;
	if (grad) {
		grad[0] = 3 * a * (a*x[0] + b) * (a*x[0] + b);
		grad[1] = -1.0;
	}
	return ((a*x[0] + b) * (a*x[0] + b) * (a*x[0] + b) - x[1]);
}

 void optim::foo()
{
	double lb[2] = { -HUGE_VAL, 0 }; /* lower bounds */
	nlopt_opt opt;
	opt = nlopt_create(NLOPT_LD_MMA, 2); /* algorithm and dimensionality */
	nlopt_set_lower_bounds(opt, lb);
	nlopt_set_min_objective(opt, myfunc, NULL);
	
	my_constraint_data data[2] = { {2,0}, {-1,1} };
	nlopt_add_inequality_constraint(opt, myconstraint, &data[0], 1e-3);
	nlopt_add_inequality_constraint(opt, myconstraint, &data[1], 1e-3);
	nlopt_set_ftol_abs(opt, 1e-2);
	double x[2] = { 1.234, 5.678 };  /* `*`some` `initial` `guess`*` */
	double minf; /* `*`the` `minimum` `objective` `value,` `upon` `return`*` */
	if (nlopt_optimize(opt, x, &minf) < 0) {
		printf("nlopt failed!\n");
	}
	else {
		printf("found minimum at f(%g,%g) = %0.10g\n", x[0], x[1], minf);
	}

	nlopt_destroy(opt);
}

double optim::compute_first_derivative(std::function<double(const double&)> f, const double & x)
{
	double error_estimate;
	return boost::math::tools::finite_difference_derivative<decltype(f),double,6>(f, x,&error_estimate);
}


vec optim::compute_gradient(ObjectiveFunction feval, const vec & x)
{
	vec g(x.size());
	for (arma::uword i = 0; i < g.size(); ++i) {
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
