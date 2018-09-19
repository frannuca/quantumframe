#pragma once
#include "exports_optim.h"
#include "armadillo.h"
#include <boost/date_time.hpp>
namespace optim {
	using namespace arma;
	class EXPORT_OPTIM Algorithm
	{
	private:
		mat A;

	public:
		Algorithm();
		~Algorithm();
	};


}
