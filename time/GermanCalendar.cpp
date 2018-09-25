#include "GermanCalendar.h"
#include "CalendarCommons.h"

termstructure::GermanCalendar::GermanCalendar()
{
}

bool termstructure::GermanCalendar::isBankHoliday(const termstructure::QDate& date) {
	

	int d = date.DayOfTheMonth();

	MONTH m = date.Month();

	int y = date.Year();

	int em = EasterMonday(y);
	int dd = date.DayOfYear();

	if (date.IsWeekend()

		// New Year's Day

		|| (d == 1 && m == MONTH::JAN)

		// Good Friday

		|| (dd == em - 3)

		// Easter Monday

		|| (dd == em)

		// Labour Day

		|| (d == 1 && m == MONTH::MAY)

		// Christmas' Eve

		|| (d == 24 && m == MONTH::DEC)

		// Christmas

		|| (d == 25 && m == MONTH::DEC)

		// Christmas Day

		|| (d == 26 && m == MONTH::DEC)

		// New Year's Eve

		|| (d == 31 && m == MONTH::DEC))

		return false;

	return true;
}
