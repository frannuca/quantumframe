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
		struct FunctionData {
			IConvexOptimizer::function_t* func;
			void* pdata;
			double ftol;
		};

		virtual ConvexOptimizerResult mimimize(int niter, std::vector<double> xstart) = 0;
		virtual ~IConvexOptimizer();
	};

	class EXPORT_OPTIM ConvexOptimizerBuilder
	{	
	private:
		

		//unsigned n, const double *x, double *grad, void *data
		std::shared_ptr<IConvexOptimizer::FunctionData> _feval;
		boost::optional<double> ftol;
		std::vector<std::shared_ptr<IConvexOptimizer::FunctionData>> eq_constraints;
		std::vector<std::shared_ptr<IConvexOptimizer::FunctionData>> ineq_constraints;
		std::vector<double> up_limits;
		std::vector<double> down_limits;		
		boost::optional<int> nlopt_method;

	public:
		ConvexOptimizerBuilder(IConvexOptimizer::function_t* f, void* pdata, double tol);
		ConvexOptimizerBuilder() = delete;
		enum OPTMETHOD  { AUGLAG = 0, SLSQP, COBYLA, NELDERMEAD};
				
		ConvexOptimizerBuilder & withLowerBounds(std::vector<double> lb);
		ConvexOptimizerBuilder & withUpperBounds(std::vector<double> up);
		ConvexOptimizerBuilder & withEquallyConstraint(IConvexOptimizer::function_t*  fconstraint,void* pdata,double tol);
		ConvexOptimizerBuilder & withInEquallyConstraint(IConvexOptimizer::function_t* fconstraint, void* pdata,double tol);
		ConvexOptimizerBuilder & withMethod(OPTMETHOD method);		

		std::unique_ptr<IConvexOptimizer> Build() const;
	};
}
