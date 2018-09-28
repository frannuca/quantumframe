#pragma once

#ifdef EXPMODULE_INSTRUMENT
#define EXPORT_INSTRUMENT __declspec(dllexport)
#else
#define EXPORT_INSTRUMENT __declspec(dllimport)
#endif

