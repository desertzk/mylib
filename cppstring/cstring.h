#ifndef __CSTRING_H__
#define  __CSTRING_H__
#include<string>
#include<vector>
/*
静态区的字符串也会报错
*/
extern char * substring(char *str, int beginindex, int endindex, char *ret);

extern char * trim(char *str);
extern char *replace(char *str, char *oldstr, char *newstr);
extern char *replaceall(char *str, char *oldstr, char *newstr);
extern int start_with(char *str, char *start);
extern int end_with(char *str, char *end);
extern char * to_upper_case(char *str, int start, int offset);
extern char * to_lower_case(char *str, int start, int offset);

std::vector<std::string> split(std::string src, std::string regexstr);
std::vector<std::string> splitwithrexstr(std::string src, std::string regexstr);
extern std::string hsGetCol(const char* ASourceStr, int AColNo, char AChar);
#endif