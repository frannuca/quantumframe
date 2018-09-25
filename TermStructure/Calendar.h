#pragma once

#include "exports_termstructure.h"
#include <functional>
#include "QDate.h"


namespace termstructure {

	class EXPORT_TSTRUCT Calendar {
	public:
		Calendar() = delete;
		virtual bool isBankHoliday(const QDate&) = 0;
		bool isWeekend(const QDate&);
		bool isHoliday(const QDate&);
		bool isBusinessDay(const QDate&);
		QDate nextBusinessDay(const QDate& d);
		QDate prevBusinessDay(const QDate& d);
	};
}

