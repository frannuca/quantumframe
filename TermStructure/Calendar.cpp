#include "Calendar.h"

	namespace termstructure {
		
	
		bool Calendar::isWeekend(const QDate& d) {
			throw "Not Implemented";
		}

		bool Calendar::isHoliday(const QDate& d) {
			return isBankHoliday(d) || isWeekend(d);
		}

		bool Calendar::isBusinessDay(const QDate& d) {
			return !isHoliday(d);
		}
		
		QDate Calendar::nextBusinessDay(const QDate& d) {
			auto x = d;
			int counter = 0;
			while (!isBusinessDay(d) && counter<100) {
				x = x + 1;
				counter++;
			}
			if (counter > 100) {
				throw "wrong detection of holidays";
			}
			return x;
		}

		QDate Calendar::prevBusinessDay(const QDate& d) {
			auto x = d;
			int counter = 0;
			while (!isBusinessDay(d) && counter < 100) {
				x = x - 1;
				counter++;
			}
			if (counter > 100) {
				throw "wrong detection of holidays";
			}
			return x;
		}
	}
