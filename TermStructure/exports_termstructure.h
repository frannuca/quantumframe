#pragma once

#ifdef EXPMODULE_TERMSTRUCTURE
#define EXPORT_TSTRUCT __declspec(dllexport)
#else
#define EXPORT_TSTRUCT __declspec(dllimport)
#endif

