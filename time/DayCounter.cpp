#include "DayCounter.h"
namespace termstructure
{
	DayCounter::DayCounter()
	{
	}

	Actual360::Actual360(bool includelastday) :_includeLastDay(includelastday)
	{
	}

	std::string Actual360::name()
	{
		return _includeLastDay ? "Actual360 (inc)" : "Actual360";
	}

	double Actual360::dayCount(const QDate& d1, const QDate& d2)
	{		
		auto dd = (d2 - d1);
		return dd + (_includeLastDay ? 1.0 : 0.0);
	}

	double Actual360::yearfraction(const QDate& d1, const QDate& d2)
	{
		return dayCount(d1,d2) / 360.0;
	}

	Actual365fixed::Actual365fixed()
	{
	}

	std::string Actual365fixed::name()
	{
		return "Actual365fixed";
	}

	double Actual365fixed::dayCount(const QDate& d1, const QDate& d2)
	{
		static const int MonthOffset[] = {

			   0,  31,  59,  90, 120, 151,  // Jan - Jun

			   181, 212, 243, 273, 304, 334   // Jun - Dec

		};



		auto s1 = d1.DayOfTheMonth() + MonthOffset[d1.DayOfTheMonth() - 1] + (d1.Year() * 365);

		auto s2 = d2.DayOfTheMonth() + MonthOffset[d2.DayOfTheMonth() - 1] + (d2.Year() * 365);



		if (d1.Month() == MONTH::FEB && d1.DayOfTheMonth() == 29) {

			--s1;
		}



		if (d2.Month() == MONTH::FEB && d2.DayOfTheMonth() == 29) {

			--s2;
		}

		return s2 - s1;
	}

	double Actual365fixed::yearfraction(const QDate& d1, const QDate& d2)
	{
		return dayCount(d1, d2) / 365.0;		
	}
}
