#pragma once
#include "export_instruments.h"
#include "../time/QDate.h"
#include <boost/optional.hpp>
#include "../time/tenor.h"

namespace instrument
{
	class EXPORT_INSTRUMENT Instrument
	{
	public:
		boost::optional<qtime::QDate> startdate;
		boost::optional<qtime::QDate> maturity;
		boost::optional<std::string>  currency;
	};

	class EXPORT_INSTRUMENT CashFlow: public Instrument
	{
	public:
		CashFlow(const qtime::Tenor<qtime::SMONTH>& tenor, double nominal)
			: tenor(tenor),
			  nominal(nominal)
		{
		}

		const qtime::Tenor<qtime::SMONTH> tenor;
		const double nominal;		
	};

	class EXPORT_INSTRUMENT Swap:public Instrument
	{
	public:
		boost::optional<double> C;
		CashFlow floating_leg;
		CashFlow fixed_leg;
	};

}
