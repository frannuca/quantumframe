#pragma once
#include "../instrument/Instrument.h"
#include "../time/QDate.h"
#include <vector>
#include "../time/DayCounter.h"

namespace yield
{
	class YieldCurveBuilder;

	class YieldCurve
	{
		std::unique_ptr<qtime::DayCounter>  dc_;
		std::vector<const instrument::Instrument*> pinstruments;
		YieldCurve(std::unique_ptr<qtime::DayCounter>& dc, const qtime::QDate& t0,std::vector<const instrument::Instrument*> pintr);
		std::vector<double> t_;
		std::vector<double> rates_;
		
		double interpolated_rate(const double& t,boost::optional<std::pair<double,double>> pn);
		double priceSwap(const instrument::Swap* n, const double &p);
		friend class YieldCurveBuilder;
		double compute_rate(const double& years);
		double compute_discount(const double & t);
		
	public:
		const qtime::QDate t0_;
		double discount(qtime::Tenor<qtime::SDAY> ndays);
		double discount(qtime::Tenor<qtime::SYEAR> nyears);
		double discount(qtime::Tenor<qtime::SWEEK> nweeks);
		double discount(qtime::Tenor<qtime::SMONTH> nmonths);
		double discount(const qtime::QDate& t);

		double rate(qtime::Tenor<qtime::SDAY> ndays);
		double rate(qtime::Tenor<qtime::SYEAR> nyears);
		double rate(qtime::Tenor<qtime::SWEEK> nweeks);
		double rate(qtime::Tenor<qtime::SMONTH> nmonths);
		double rate(const qtime::QDate& t);


		double forward(const qtime::QDate& t1, qtime::Tenor<qtime::SDAY> ndays);
		double forward(const qtime::QDate& t1, qtime::Tenor<qtime::SYEAR> nyears);
		double forward(const qtime::QDate& t1, qtime::Tenor<qtime::SWEEK> nweeks);
		double forward(const qtime::QDate& t1, qtime::Tenor<qtime::SMONTH> nmonths);
		double forward(const qtime::QDate& t1, const qtime::QDate& t2);
		void boostrap();
	};


	class YieldCurveBuilder
	{
		std::vector<const instrument::Instrument*> instruments;
		std::unique_ptr<qtime::DayCounter> dc;
		const qtime::QDate& t0_;

		double interpolatedRate(const double &t1, const double &t2);
	public:
		YieldCurveBuilder(const qtime::QDate& t0);
		YieldCurveBuilder& withInstrument(const instrument::Instrument* pintr);
		YieldCurveBuilder& withDayCount(std::unique_ptr<qtime::DayCounter> pdc);	
		const YieldCurve & Build();
	};

}
