#pragma once
#ifdef EXPMODULE_PRICING
#define EXPORT_PRICING __declspec(dllexport)
#else
#define EXPORT_PRICING __declspec(dllimport)
#endif