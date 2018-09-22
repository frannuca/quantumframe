#include "convexoptimizer.h"
#include "armadillo.h"
#include <nlopt.h>

namespace
{
	class ConvexOptimizerImp :public optim::IConvexOptimizer
	{
	public:
		function_t*  _feval;
		std::vector<std::pair<function_t* , void*>> eq_constraints;
		std::vector<std::pair<function_t*, void*>> ineq_constraints;
		std::vector<double> up_limits;
		std::vector<double> down_limits;		
		int nlopt_method;
		
		ConvexOptimizerResult mimimize(int niter, std::vector<double> xstart,void * data) override;
	};

	optim::IConvexOptimizer::ConvexOptimizerResult ConvexOptimizerImp::mimimize(int niter, std::vector<double> xstart, void * data)
	{					
		nlopt_opt opt = nlopt_create(static_cast<nlopt_algorithm>(nlopt_method), xstart.size());
								
		nlopt_set_min_objective(opt, _feval, nullptr);
		
		nlopt_set_xtol_rel(opt, 1e-4);
		
		nlopt_set_maxeval(opt, niter);
		
		
		if(down_limits.size()>0)
		{
			nlopt_set_lower_bounds(opt, &down_limits[0]);
		}

		if(up_limits.size()>0)
		{
			nlopt_set_lower_bounds(opt, &up_limits[0]);
		}

		
		for (auto c : eq_constraints) { nlopt_add_equality_constraint(opt, c.first, c.second, 1e-3); }
		

		for (auto c : ineq_constraints){nlopt_add_inequality_constraint(opt, c.first, c.second, 1e-3);}

		std::vector<double> x = xstart;
		double minf; /* `*`the` `minimum` `objective` `value,` `upon` `return`*` */
		if (nlopt_optimize(opt, &x[0], &minf) < 0) {
			printf("nlopt failed!\n");
		}
		else {
			printf("found minimum at f(%g,%g) = %0.10g\n", x[0], x[1], minf);
		}

		ConvexOptimizerResult result;
		result.error=minf;
		result.feval = _feval(x.size(), &x[0], nullptr, data);
		result.solution = x;
		return result;
	}
}

optim::IConvexOptimizer::~IConvexOptimizer()
{
}

optim::ConvexOptimizerBuilder::ConvexOptimizerBuilder()
{
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withFitnessFunction(IConvexOptimizer::function_t* f)
{
	_feval = f;
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withLowerBounds(std::vector<double> lb)
{
	down_limits = lb;
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withUpperBounds(std::vector<double> up)
{
	up_limits = up;
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withEquallyConstraint(IConvexOptimizer::function_t* fconstraint, void *value)
{
	eq_constraints.push_back(std::make_pair(fconstraint, value));
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withInEquallyConstraint(IConvexOptimizer::function_t*  fconstraint, void *value)
{
	ineq_constraints.push_back(std::make_pair(fconstraint, value));
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withMethod(OPTMETHOD method)
{
	switch (method)
	{
	case(AUGLAG):
		nlopt_method = NLOPT_LD_AUGLAG;			
		break;
	case(SLSQP):
		nlopt_method = NLOPT_LD_SLSQP;
		break;
	case(COBYLA):
			nlopt_method = NLOPT_LN_COBYLA;
			break;
	case(NELDERMEAD):
		nlopt_method = NLOPT_LN_NELDERMEAD;
		break;
	}

	return *this;
}

std::unique_ptr<optim::IConvexOptimizer> optim::ConvexOptimizerBuilder::Build()
{
	auto o = new ConvexOptimizerImp();
	o->up_limits = up_limits;
	o->down_limits = down_limits;
	o->eq_constraints = eq_constraints;
	o->ineq_constraints = ineq_constraints;
	o->nlopt_method = nlopt_method.value_or(NLOPT_LN_COBYLA);
	o->_feval = _feval.value();		
	return std::unique_ptr<IConvexOptimizer>(o);
}
