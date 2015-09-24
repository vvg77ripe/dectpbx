
#ifndef _TIME_H
#define _TIME_H

typedef unsigned int time_t;

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

time_t time(time_t *T);
struct tm *gmtime(const time_t clock, struct tm *res);
time_t timegm(struct tm *tm);

#endif
