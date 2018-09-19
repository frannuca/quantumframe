#pragma once

#ifdef EXPMODULE_OPTIM
#define EXPORT_OPTIM __declspec(dllexport)
#else
#define EXPORT_OPTIM __declspec(dllimport)
#endif
