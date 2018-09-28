#pragma once
#ifdef EXPMODULE_CREDITPRICING
#define EXPORT_CREDITPRICING __declspec(dllexport)
#else
#define EXPORT_CREDITPRICING __declspec(dllimport)
#endif
