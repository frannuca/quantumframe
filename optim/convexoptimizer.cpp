#include "convexoptimizer.h"
#include "armadillo.h"
#include <boost/optional.hpp>

namespace optim {
	using namespace arma;

	ConvexOptimizer::ConvexOptimizer() :counter(0)
	{
	}

	int ConvexOptimizer::next(vec x0, int niter)
	{
		return 0;
	}

	ConvexOptimizer::~ConvexOptimizer()
	{
	}
}
