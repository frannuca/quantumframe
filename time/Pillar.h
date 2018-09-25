#pragma once
#include "exports_termstructure.h"
#include "QDate.h"
namespace termstructure
{
	template<typename T>
	struct Pillar
	{	
		QDate date;
		T value;		
	};
}