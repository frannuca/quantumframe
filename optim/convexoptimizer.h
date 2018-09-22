#pragma once
#include "exports_optim.h"
#include <functional>
#include <vector>
#include <memory>
#include <boost/optional.hpp>
#include <utility>



namespace optim {
	
	class IConvexOptimizer {
	public:
		typedef double function_t(unsigned, const double*, double*, void*);
		struct ConvexOptimizerResult {
			double feval;
			std::vector<double> solution;
			double error;
		} ;
		
		virtual ConvexOptimizerResult mimimize(int niter, std::vector<double> xstart,void* data) = 0;
		virtual ~IConvexOptimizer();
	};

	class EXPORT_OPTIM ConvexOptimizerBuilder
	{	
	private:
		//unsigned n, const double *x, double *grad, void *data
		boost::optional<IConvexOptimizer::function_t*> _feval;
		std::vector<std::pair<IConvexOptimizer::function_t*, void*>> eq_constraints;
		std::vector<std::pair<IConvexOptimizer::function_t*, void*>> ineq_constraints;
		std::vector<double> up_limits;
		std::vector<double> down_limits;		
		boost::optional<int> nlopt_method;

	public:	
		ConvexOptimizerBuilder();
		enum OPTMETHOD  { AUGLAG = 0, SLSQP, COBYLA, NELDERMEAD};
		

		ConvexOptimizerBuilder & withFitnessFunction(IConvexOptimizer::function_t* f);
		ConvexOptimizerBuilder & withLowerBounds(std::vector<double> lb);
		ConvexOptimizerBuilder & withUpperBounds(std::vector<double> up);
		ConvexOptimizerBuilder & withEquallyConstraint(IConvexOptimizer::function_t*  fconstraint,void* value);
		ConvexOptimizerBuilder & withInEquallyConstraint(IConvexOptimizer::function_t* fconstraint, void* value);
		ConvexOptimizerBuilder & withMethod(OPTMETHOD method);

		std::unique_ptr<IConvexOptimizer> Build();
	};
}
