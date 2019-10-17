#define _CRT_SECURE_NO_WARNINGS

#include<time.h>
#include"cstring.h"
#include"ctime.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<string>
#include<iostream>
#include<tuple>
#include<vector>
#include <chrono>
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#define  CRITICAL_SECTION   pthread_mutex_t
#define  _vsnprintf         vsnprintf
#endif

using namespace std;
//m月 Y 年 M 分
char *get_time(char *format)
{
	static char buf[64] = { 0 };
	 //strcpy(buf, format);
	time_t tm = time(NULL);
	struct tm *pstm=localtime(&tm);
	//struct tm *stm = gmtime(&tm);
	strftime(buf, sizeof(buf), format, pstm);
	/*replace(buf, "HH", _itoa(stm->tm_hour, strstr(buf, "HH"), 10));
	replace(buf, "mm", _itoa(stm->tm_mon, strstr(buf, "mm"), 10));
	replace(buf, "dd", _itoa(stm->tm_mday, strstr(buf, "dd"), 10));
	replace(buf, "SS", _itoa(stm->tm_sec, strstr(buf, "SS"), 10));
	replace(buf, "MM", _itoa(stm->tm_min, strstr(buf, "MM"), 10));
	replace(buf, "YYYY", _itoa(stm->tm_year, strstr(buf, "YYYY"), 10));*/
	return buf;
}

std::string get_nowtime(char * format)
{
	char buf[64] = { 0 };
	//strcpy(buf, format);
	time_t tm = time(NULL);
	struct tm *pstm = localtime(&tm);
	//struct tm *stm = gmtime(&tm);
	strftime(buf, sizeof(buf), format, pstm);
	
	return buf;
}



int get_weekday()
{
	time_t tm = time(NULL);
	struct tm *pstm = localtime(&tm);
	return pstm->tm_wday;
}

int get_hour()
{
	time_t tm = time(NULL);
	struct tm *pstm = localtime(&tm);
	return pstm->tm_hour;
}

int get_min()
{
	time_t tm = time(NULL);
	struct tm *pstm = localtime(&tm);
	return pstm->tm_min;
}


const char* GetFormatedTime()
{
	const int T_LEN = 7;
	static char st_FormatedTime[T_LEN];
	struct tm t;
	time_t now;
	int year;

	time(&now);
	t = *localtime(&now);
	year = t.tm_year;
	if (year < 50)
		year += 2000;
	else
		year += 1900;
	sprintf(st_FormatedTime, "%02d%02d%02d", t.tm_hour, t.tm_min, t.tm_sec);
	st_FormatedTime[T_LEN - 1] = 0;
	return st_FormatedTime;
}

//返回指定的年、月、日是一年中的第几天
unsigned int day_of_year(unsigned int year, unsigned int month, unsigned int day)
{
	unsigned int days = 0;
	for (unsigned int i = 1; i < month; i++)
	{
		switch (i)
		{
		case 4:
		case 6:
		case 9:
		case 11:
			days += 30;
			break;
		case 2:
			days += (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) ? 29 : 28;
			break;
		default:
			days += 31;
		}
	}
	days += day;
	return days;
}


string getmilliseconds()
{
	char buf[64] = { 0 };
	char millbuf[128] = { 0 };
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	std::tm now_tm = *std::localtime(&now_c);
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	std::size_t fractional_seconds = ms.count() % 1000;
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &now_tm);
	sprintf(millbuf, "%s.%d", buf, fractional_seconds);
	return string(millbuf);
}




//获取毫秒
#ifdef _WIN32
unsigned long getMs() {
	return GetTickCount();
}
#else
unsigned long getMs() {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	sleep(3);
	gettimeofday(&end, NULL);
	int timeuse = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("time: %d us\n", timeuse);
	return 0;
}

double get_microsecond()
{
	    static char strtime[128];
	     char buf[64] = { 0 };
	     memset(strtime, 0, sizeof(strtime));
	     struct timeval tv;
	     gettimeofday(&tv, NULL);
	     struct tm *pstm = localtime(&tv.tv_sec);
	     strftime(buf, sizeof(buf), "%Y%m%d%H%M%S", pstm);
	     //sprintf(strtime,"%s%lf",buf,(double)tv.tv_usec/1000000);
	     double ret = atof(buf) + (double)tv.tv_usec / 1000000;
	     return ret;
}


int  get_millisecond_i()
 {
	     char strtime[128] = { 0 };
	     char buf[64] = { 0 };
	     memset(strtime, 0, sizeof(strtime));
	     struct timeval tv;
	     gettimeofday(&tv, NULL);
	     struct tm *pstm = localtime(&tv.tv_sec);
	     strftime(buf, sizeof(buf), "%H%M%S", pstm);
	     sprintf(strtime, "%s%d", buf, tv.tv_usec / 1000);
	     return atoi(strtime);
}

#endif



char *DoubleToStr(double d)
{
	static char str[64] = { 0 };
	sprintf(str, "%f", d);
	return str;
}

//将分割字符以及值插入
std::string CreateSpliteString(char *splite, int n_args, ...)
{
	va_list ap;
	va_start(ap, n_args);
	std::stringstream ss;
	for (int i = 2; i <= n_args; i++) {
		char * str = va_arg(ap, char *);
		ss << str << splite;
	}
	va_end(ap);
	return ss.str();
}

void logdebug(string str)
{

}

int main78()
{
	
	//logdebug(stringstream("dassfa") << 1 << "hehe");

	char direction[64] = { 0 };
	char test1str[8] = "1";
	char c2 = '1';
	strcat(direction, test1str);
	strcat(direction, "#");
	strcat(direction, &c2);
	printf("%s", direction);



	cout << time(NULL) << endl;
	char str[128] = "YYYY-mm-dd HH:MM:SS";
	printf("%s", get_time("%Y%m%d"));
	string cpsstr = CreateSpliteString("|", 5, "112", "333", "6345", "hey");
	cout << cpsstr << endl;
	cpsstr = "";
	std::string line = hsGetCol(cpsstr.c_str(), 3, '|');
	cout << line << endl;
	vector<tuple<int, int, const char *>> pack(10);
	pack[0] = make_tuple(1, 2, "543rtqws");
	cin.get();
	return 0;
}


