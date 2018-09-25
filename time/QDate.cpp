#include "QDate.h"

#include <boost/date_time/gregorian/gregorian_types.hpp> 
#include <ctime>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include "boost/date_time/local_time/local_time.hpp"

namespace pt = boost::posix_time;
namespace g = boost::gregorian;

termstructure::QDate::QDate(int day, int month, int year) {
	_d = new boost::gregorian::date(year, month, day);
	auto a = _d->day();
	auto b = _d->year();
	auto c = _d->month();
}

termstructure::QDate::QDate(const QDate& that) {
	_d = new boost::gregorian::date(*that._d);
}

termstructure::QDate::QDate(QDate&& that) noexcept
{
	if (this != &that)
	{
		_d = that._d;		
		that._d = nullptr;
	}	
}

termstructure::QDate::QDate(const long &btime) {
	_d = new boost::gregorian::date(boost::posix_time::from_time_t(btime).date());
}

termstructure::QDate::~QDate() {
	delete _d;
}

termstructure::QDate& termstructure::QDate::operator=(const termstructure::QDate& other) {
	if (this != &other) {
		delete _d;
		_d = new boost::gregorian::date(*other._d);
	}
	return *this;
}

termstructure::QDate& termstructure::QDate::operator=(termstructure::QDate&& other) noexcept
{
	if (this != &other) {
		delete _d;		
		_d = std::exchange(other._d, nullptr);
	}
	return *this;
}

termstructure::QDate termstructure::QDate::operator+(int ndays) {
	auto date = *_d + boost::gregorian::days(ndays);
	QDate d(date.day(), date.month(), date.year());
	return d;
}
termstructure::WEEKDAY termstructure::QDate::DayOfTheWeek() const{	
	auto iday = _d->day_of_week();
	auto wd = boost::lexical_cast<std::string>(_d->day_of_week());
	return termstructure::WEEKDAY((int)iday);			
}

int termstructure::QDate::DayOfTheMonth() const
{
	return _d->day();
}

int termstructure::QDate::DayOfYear() const
{
	return _d->day_of_year();
}

bool termstructure::QDate::IsWeekend() const
{
	auto dw = DayOfTheWeek();
	return dw == WEEKDAY::SATURDAY || dw == WEEKDAY::SUNDAY;
}

termstructure::MONTH termstructure::QDate::Month() const
{
	auto m = _d->month().as_enum();	
	return MONTH(m);	
}

int termstructure::QDate::Year() const
{
	return _d->year();
}

termstructure::QDate termstructure::QDate::operator-(int ndays) const
{
	auto date = *_d - boost::gregorian::days(ndays);
	QDate d(date.day(), date.month(), date.year());
	return d;
}

int termstructure::QDate::operator-(const QDate& that) const
{
	return (*_d - *(that._d)).days();
}

bool termstructure::QDate::operator>(const QDate& that) const
{
	return (*_d) < *(that._d);
}

bool termstructure::QDate::operator<(const QDate& that) const
{
	return !(this->operator<(that));
}

bool termstructure::QDate::operator<=(const QDate& that) const
{
	return (this->operator<(that) || this->operator==(that));
}

bool termstructure::QDate::operator>=(const QDate& that) const
{
	return (this->operator>(that) || this->operator==(that));
}

bool termstructure::QDate::operator==(const QDate& that) const
{
	return *_d == *(that._d);
}


time_t termstructure::QDate::toEpoch() const
{
	using namespace boost::posix_time;
	static ptime epoch(boost::gregorian::date(1970, 1, 1));
	time_duration::sec_type secs = (ptime(*_d, seconds(0)) - epoch).total_seconds();
	return time_t(secs);
}

const std::locale fmt(std::locale::classic(),
	new boost::gregorian::date_facet("%m/%d/%Y"));

std::string dateAsMMDDYYYY(const boost::gregorian::date& date)
{
	std::ostringstream os;
	os.imbue(fmt);
	os << date;
	return os.str();
}
std::ostream&  termstructure::operator<<(std::ostream& os, const termstructure::QDate& dt) {
	os.imbue(fmt);
	os << *(dt._d);
	return os;
}

