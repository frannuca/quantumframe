#include "MarketData.h"

namespace
{
	class IMDataDefault :public pricing::IMData
	{
	public:
		const std::type_info& GetType() override;
		bool HasData() override;
	};

	const std::type_info&  IMDataDefault::GetType()
	{
		return typeid(IMDataDefault);
	}

	bool IMDataDefault::HasData()
	{
		return false;
	}
}

pricing::MarketData::MarketData(): pdata(new IMDataDefault())
{
}

pricing::MarketData::MarketData(std::shared_ptr<IMData> data):pdata(data)
{
}

const qtime::QDate& pricing::MarketData::StartDate() const
{
	if (startdate) { return startdate.get(); }
	else { return qtime::QDate::ZERO; }
}

const qtime::QDate& pricing::MarketData::Maturity() const
{
	if (startdate) { return maturity.get(); }
	else { return qtime::QDate::ZERO; }
}

const qtime::QDate& pricing::MarketData::Settlement() const
{
	if (startdate) { return settlementdate.get(); }
	else { return qtime::QDate::ZERO; }
}

const pricing::IMData* pricing::MarketData::Data() const
{
	return pdata.get();
}
