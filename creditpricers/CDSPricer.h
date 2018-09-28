#pragma once
#include "exports_creditpricing.h"
#include "../pricing/MarketData.h"
#include "../pricing/IPricer.h"
namespace pricing
{
	class EXPORT_CREDITPRICING CDSPricer:IPricer
	{
	public:
		using IPricer::IPricer;
		virtual void Compute(const MarketData* md) override;
	};
}

