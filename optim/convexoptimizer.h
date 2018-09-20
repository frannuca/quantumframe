#pragma once
#include "exports_optim.h"
#include "armadillo.h"
#include <boost/optional.hpp>

namespace optim {
	using namespace arma;
	class EXPORT_OPTIM ConvexOptimizer
	{
	private:		
		int counter;
		boost::optional<arma::vec> xstart;
	public:
		ConvexOptimizer();
		int next(vec x0, int niter = 1);
		~ConvexOptimizer();
	};
}
