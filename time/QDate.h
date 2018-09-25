#pragma once
#include "exports_termstructure.h"
#include <time.h>
#include <iostream>
#include "CalendarCommons.h"
namespace boost { namespace gregorian{ class date; } }

namespace termstructure {
	
class EXPORT_TSTRUCT QDate {
protected:
	boost::gregorian::date *_d;
public:
	//ctors
	QDate() = delete;
	QDate(int day, int month, int year);	
	explicit QDate(const long& unixtime);

	//copy
	QDate(const QDate& date);
	QDate(QDate&& date) noexcept;
	QDate& operator=(const QDate& other);
	QDate& operator=(QDate&& other) noexcept;
	WEEKDAY DayOfTheWeek() const;
	int DayOfTheMonth() const;
	int DayOfYear() const;
	bool IsWeekend() const;
	MONTH Month() const;
	int Year() const;
	//dtor
	~QDate();

		
	QDate operator+(int days);
	QDate operator-(int days) const;
	int operator-(const QDate& that) const;
	bool operator>(const QDate& that) const;
	bool operator<(const QDate& that) const;
	bool operator<=(const QDate& that) const;
	bool operator>=(const QDate& that) const;

	bool operator==(const QDate& that) const;
	time_t toEpoch() const;

	static bool isLeapYear(int year);
	friend EXPORT_TSTRUCT std::ostream&  operator<<(std::ostream& os, const QDate& dt);
	
};

	
}
