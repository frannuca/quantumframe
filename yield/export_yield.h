#pragma once
#ifdef EXPMODULE_YIELD
#define EXPORT_YIELD __declspec(dllexport)
#else
#define EXPORT_YIELD __declspec(dllimport)
#endif
