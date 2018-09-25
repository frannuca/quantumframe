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
	QDate(QDate&& date);
	QDate& operator=(const QDate& other);
	QDate& operator=(QDate&& other);
	WEEKDAY DayOfTheWeek();
	//dtor
	~QDate();

		
	QDate operator+(int days);
	QDate operator-(int days);
	time_t toEpoch();

	friend EXPORT_TSTRUCT std::ostream&  operator<<(std::ostream& os, const QDate& dt);
};
}
