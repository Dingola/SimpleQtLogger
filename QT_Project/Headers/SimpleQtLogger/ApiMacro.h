#ifdef SIMPLEQTLOGGER_USE_DLL
#ifdef SIMPLEQTLOGGER_BUILDING_PROJECT
#define SIMPLEQTLOGGER_API __declspec(dllexport)
#else
#define SIMPLEQTLOGGER_API __declspec(dllimport)
#endif
#else
#define SIMPLEQTLOGGER_API
#endif
