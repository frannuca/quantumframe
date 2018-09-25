#pragma once

#include "exports_termstructure.h"
#include <functional>
#include "QDate.h"
#include "Calendar.h"

	namespace termstructure {

		class  EXPORT_TSTRUCT GermanCalendar:public Calendar {
		
		public:
			GermanCalendar();
			bool isBankHoliday(const QDate&) override;			
		};
	}
