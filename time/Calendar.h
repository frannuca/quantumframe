#pragma once

#include "exports_termstructure.h"
#include <functional>
#include "QDate.h"


namespace qtime {

	class EXPORT_TSTRUCT Calendar {
	public:
		virtual ~Calendar() = default;
		Calendar();
		virtual bool isBankHoliday(const QDate&) = 0;
		static bool isWeekend(const QDate&);
		bool isHoliday(const QDate&);
		bool isBusinessDay(const QDate&);
		QDate nextBusinessDay(const QDate& d);
		QDate prevBusinessDay(const QDate& d);
		static int EasterMonday(int year);
	};
}

