#ifndef __CTIME_H__
#define  __CTIME_H__
#include <string>
#ifdef __cplusplus
extern "C" {
#endif
extern char *get_time(char *format);

extern int get_weekday();

const char* GetFormatedTime();

std::string getmilliseconds();
#ifdef __cplusplus
};
#endif
std::string get_nowtime(char *format);







#endif