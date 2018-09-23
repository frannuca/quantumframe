#include "convexoptimizer.h"
#include "armadillo.h"
#include <nlopt.h>

namespace
{
	class ConvexOptimizerImp :public optim::IConvexOptimizer
	{
	public:
		std::shared_ptr<FunctionData> _feval;
		double ftol;
		std::vector<std::shared_ptr<FunctionData>> eq_constraints;
		std::vector<std::shared_ptr<FunctionData>> ineq_constraints;
		std::vector<double> up_limits;
		std::vector<double> down_limits;
		int nlopt_method;
			
		ConvexOptimizerResult mimimize(int niter, std::vector<double> xstart) override;
	};

	optim::IConvexOptimizer::ConvexOptimizerResult ConvexOptimizerImp::mimimize(int niter, std::vector<double> xstart)
	{					
		nlopt_opt opt = nlopt_create(static_cast<nlopt_algorithm>(nlopt_method), xstart.size());
								
		
		nlopt_set_min_objective(opt, _feval.get()->func, _feval.get()->pdata);
		
		nlopt_set_ftol_abs(opt, _feval.get()->ftol);		
		nlopt_set_maxeval(opt, niter);
		
		
		if(down_limits.size()>0)
		{
			nlopt_set_lower_bounds(opt, &down_limits[0]);
		}

		if(up_limits.size()>0)
		{
			nlopt_set_lower_bounds(opt, &up_limits[0]);
		}

		
		for (auto c : eq_constraints) { nlopt_add_equality_constraint(opt, c.get()->func, c.get()->pdata, c.get()->ftol); }
		

		for (auto c : ineq_constraints){nlopt_add_inequality_constraint(opt, c.get()->func, c.get()->pdata, c.get()->ftol);}

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
		result.feval = _feval.get()->func(x.size(), &x[0], nullptr, _feval.get()->pdata);
		result.solution = x;
		return result;
	}
}

optim::IConvexOptimizer::~IConvexOptimizer()
{
}


optim::ConvexOptimizerBuilder::ConvexOptimizerBuilder(IConvexOptimizer::function_t* f, void* pdata, double tol)
{
	auto p = new IConvexOptimizer::FunctionData();
	p->ftol = tol;
	p->pdata = pdata;
	p->func = f;
	_feval.reset(p);
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

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withEquallyConstraint(IConvexOptimizer::function_t*  fconstraint, void* pdata, double tol)
{
	auto p = new IConvexOptimizer::FunctionData();
	p->ftol = tol;
	p->pdata = pdata;
	p->func = fconstraint;
	
	eq_constraints.push_back(std::unique_ptr<IConvexOptimizer::FunctionData>(p));
	return *this;
}

optim::ConvexOptimizerBuilder& optim::ConvexOptimizerBuilder::withInEquallyConstraint(IConvexOptimizer::function_t*  fconstraint, void* pdata, double tol)
{
	auto p = new IConvexOptimizer::FunctionData();
	p->ftol = tol;
	p->pdata = pdata;
	p->func = fconstraint;

	ineq_constraints.push_back(std::unique_ptr<IConvexOptimizer::FunctionData>(p));
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

std::unique_ptr<optim::IConvexOptimizer> optim::ConvexOptimizerBuilder::Build() const
{
	auto o = new ConvexOptimizerImp();
	o->ftol = ftol.value_or(1e-8);
	o->nlopt_method = nlopt_method.value_or(NLOPT_LN_COBYLA);
	o->up_limits = up_limits;
	o->down_limits = down_limits;
	o->eq_constraints = eq_constraints;
	o->ineq_constraints = ineq_constraints;
	o->nlopt_method = nlopt_method.value_or(NLOPT_LN_COBYLA);
	o->_feval = _feval;		
	return std::unique_ptr<IConvexOptimizer>(o);
}
