#include "CDSPricer.h"
#include "../time/QDate.h"
#include <vector>

void pricing::CDSPricer::Compute(const MarketData* md)
{
	int M = 100; // number of remaining payments
	double C = 0.05; //coupon
	double N = 100e6;//nominal
	QDate tv(28, 02, 2018);//trade date
	std::vector<QDate> Tpayments; //payment dates
	
	double PVpremium = 0.0;
	for(int i=0;i<M;++i)
	{
		
	}
}
