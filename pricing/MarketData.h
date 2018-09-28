#pragma once
#include "export_pricers.h"
#include <boost/optional.hpp>
#include <memory>
#include "../time/QDate.h"

namespace pricing {
	using namespace qtime;
	
	class EXPORT_PRICING IMData
	{
	public:
		virtual ~IMData() = default;
		virtual const std::type_info& GetType() = 0;
		virtual bool HasData() = 0;
	};
	template<class T>
	class MarketDataBuilder;

	class EXPORT_PRICING MarketData
	{	
	protected:
		boost::optional<QDate> startdate;
		boost::optional<QDate> maturity;
		boost::optional<QDate> settlementdate;
		std::shared_ptr<IMData> pdata;
	public:
		MarketData();
		explicit MarketData(std::shared_ptr<IMData> data);
		const QDate& StartDate() const;	
		const QDate& Maturity() const;
		const QDate& Settlement() const;
		const ::pricing::IMData* Data() const;

		template<typename T> friend class MarketDataBuilder;

	};

	template<typename T>
	class EXPORT_PRICING MarketDataBuilder
	{
		boost::optional<QDate> startdate;
		boost::optional<QDate> maturity;
		boost::optional<QDate> settlementdate;
		std::shared_ptr<T> pdata;
	public:
		MarketDataBuilder() {};
		MarketDataBuilder& WithStartDate(const QDate &d) {  startdate		= d; return *this; }
		MarketDataBuilder& WithMaturity(const QDate &d) {   maturity		= d; return *this; }
		MarketDataBuilder& WithSettlement(const QDate &d) { settlementdate  = d; return *this; }
		MarketDataBuilder& WithData(std::shared_ptr<T> &p) { pdata			= p; return *this; }

		std::unique_ptr<MarketData> Build()
		{
			std::unique_ptr<MarketData> m(new MarketData());
			m->startdate = startdate;
			m->settlementdate = settlementdate;
			m->pdata = pdata;
			return std::move(m);
		}
	};
}
