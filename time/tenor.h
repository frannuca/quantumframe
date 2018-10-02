#pragma once
#include "exports_termstructure.h"

namespace qtime
{
	inline namespace literals
	{
		struct EXPORT_TSTRUCT SDAY   { double n; };
		struct EXPORT_TSTRUCT SMONTH { double n; };
		struct EXPORT_TSTRUCT SWEEK  { double n; };
		struct EXPORT_TSTRUCT SYEAR  { double n; };

		template<typename Q>
		struct EXPORT_TSTRUCT Tenor: public Q
		{			
			Tenor(long double x) { this->Q::n = double(x); }
			Tenor<Q> operator=(const double& x) {return Tenor<Q>{x}; }
			Tenor<Q> operator+=(const Tenor<Q>& rhs) { return Tenor<Q>{this->Q::n + rhs}; }			
			Tenor<Q> operator-=(const Tenor<Q>& rhs) { return Tenor<Q>{this->Q::n - rhs}; }
		};

		template<typename Q>
		bool operator==(const Tenor<Q>& lhs, const Tenor<Q>& rhs) { return std::abs(lhs.n - rhs.n)<1e-12; }

		template<typename Q>
		Tenor<Q> operator+(const Tenor<Q>& lhs,const Tenor<Q>& rhs) { return Tenor<Q>(lhs.n + rhs.n); }

		template<typename Q>
		Tenor<Q> operator-(const Tenor<Q>& lhs, const Tenor<Q>& rhs) { return Tenor<Q>(lhs.n - rhs.n); }

		template<typename Q>
		Tenor<Q> operator*(const Tenor<Q>& lhs, const double& l) { return Tenor<Q>(lhs.n * l); }

		template<typename Q>
		Tenor<Q> operator*(const double& l, const Tenor<Q>& rhs) { return Tenor<Q>(l*rhs.n); }

		template<typename Q>
		Tenor<Q> operator/(const Tenor<Q>& lhs,const double & l) { return Tenor<Q>(lhs.n / l); }

		template<typename Q>
		Tenor<Q> operator/(const double & l, const Tenor<Q>& rhs) { return Tenor<Q>(l/ rhs.n); }

		template<typename Q>
		Tenor<Q> operator*=(const double & l, const Tenor<Q>& rhs) { return Tenor<Q>(l*rhs.n); }

		template<typename Q>
		Tenor<Q> operator*=(const Tenor<Q>& lhs, const double & l) { return Tenor<Q>(lhs.n*l); }

		template<typename Q>
		Tenor<Q> operator/=(const double & l, const Tenor<Q>& rhs) { return Tenor<Q>(l/rhs.n); }


		inline double to_years(const Tenor<SDAY>& o, int daysperyear = 360) { return o.n / daysperyear; }
		inline double to_years(const Tenor<SMONTH>& o, int daysperyear = 360) { return o.n / 12.0; }
		inline double to_years(const Tenor<SYEAR>& o, int daysperyear = 360) { return o.n; }
		inline double to_years(const Tenor<SWEEK>& o, int daysperyear = 360) { return o.n*7/daysperyear; }
		

		inline Tenor<SDAY> operator""_days(long double n) { return Tenor<SDAY>(n); }
		inline Tenor<SMONTH> operator""_months(long double n) { return Tenor<SMONTH>(n); }
		inline Tenor<SWEEK> operator""_weeks(long double n) { return Tenor<SWEEK>(n); }
		inline Tenor<SYEAR> operator""_years(long double n) { return Tenor<SYEAR>(n); }
	}
	

}
