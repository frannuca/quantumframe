#pragma once
#include "exports_termstructure.h"
#include "QDate.h"
namespace qtime
{
	template<typename T>
	struct Pillar
	{	
		QDate date;
		T value;		
	};
}