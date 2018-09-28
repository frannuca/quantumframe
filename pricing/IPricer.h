#pragma once
#include "export_pricers.h"
#include "MarketData.h"
#include <memory>

namespace pricing
{
	class EXPORT_PRICING IPricer
	{		
	public:
		virtual ~IPricer() = default;	
		virtual void Compute(const MarketData* md)=0;
		
	};
}