#pragma once
#include "exports_termstructure.h"

namespace qtime
{
	inline namespace literals
	{
		struct EXPORT_TSTRUCT SDAY   { int n; };
		struct EXPORT_TSTRUCT SMONTH { int n; };
		struct EXPORT_TSTRUCT SWEEK  { int n; };
		struct EXPORT_TSTRUCT SYEAR  { int n; };

		template<typename Q>
		struct EXPORT_TSTRUCT Tenor: public Q
		{			
			Tenor(long double x) { this->Q::n = int(x); }
			Tenor<Q> operator=(const int& x) {return Tenor<Q>{x}; }
			Tenor<Q> operator+=(const Tenor<Q>& rhs) { return Tenor<Q>{this->Q::n + rhs}; }			
			Tenor<Q> operator-=(const Tenor<Q>& rhs) { return Tenor<Q>{this->Q::n - rhs}; }
		};

		template<typename Q>
		bool operator==(const Tenor<Q>& lhs, const Tenor<Q>& rhs) { return lhs.n == rhs.n; }

		template<typename Q>
		Tenor<Q> operator+(const Tenor<Q>& lhs,const Tenor<Q>& rhs) { return Tenor<Q>(lhs.n + rhs.n); }

		template<typename Q>
		Tenor<Q> operator-(const Tenor<Q>& lhs, const Tenor<Q>& rhs) { return Tenor<Q>(lhs.n - rhs.n); }

		template<typename Q>
		Tenor<Q> operator*(const Tenor<Q>& lhs, const int& l) { return Tenor<Q>(lhs.n * l); }

		template<typename Q>
		Tenor<Q> operator*(const int& l, const Tenor<Q>& rhs) { return Tenor<Q>(l*rhs.n); }

		template<typename Q>
		Tenor<Q> operator/(const Tenor<Q>& lhs,const int & l) { return Tenor<Q>(lhs.n / l); }

		template<typename Q>
		Tenor<Q> operator/(const int & l, const Tenor<Q>& rhs) { return Tenor<Q>(l/ rhs.n); }

		template<typename Q>
		Tenor<Q> operator*=(const int & l, const Tenor<Q>& rhs) { return Tenor<Q>(l*rhs.n); }

		template<typename Q>
		Tenor<Q> operator*=(const Tenor<Q>& lhs, const int & l) { return Tenor<Q>(lhs.n*l); }

		template<typename Q>
		Tenor<Q> operator/=(const int & l, const Tenor<Q>& rhs) { return Tenor<Q>(l/rhs.n); }


		inline Tenor<SDAY> operator""_days(long double n) { return Tenor<SDAY>(n); }
		inline Tenor<SMONTH> operator""_months(long double n) { return Tenor<SMONTH>(n); }
		inline Tenor<SWEEK> operator""_weeks(long double n) { return Tenor<SWEEK>(n); }
		inline Tenor<SYEAR> operator""_years(long double n) { return Tenor<SYEAR>(n); }
	}
	

}
