#include <string>
#include <time.h>
#include "class_time.h"

class_time::class_time(cwMarketDataPtr time_update)
{
    struct tm datetime;

    memset(&datetime, 0, sizeof(struct tm)); // Initialize struct to zeroes
    // Convert date string to integers using strtol()
    datetime.tm_year = strtol(time_update->ActionDay, NULL, 10) - 1900;
    datetime.tm_mon = strtol(time_update->ActionDay + 4, NULL, 10) - 1;
    datetime.tm_mday = strtol(time_update->ActionDay + 6, NULL, 10);
    // datetime.tm_hour = strtol(datestr + 8, NULL, 10);
    // datetime.tm_min = strtol(datestr + 10, NULL, 10);

    if (datetime.tm_year < 0 || datetime.tm_year > 8099 ||
        datetime.tm_mon < 0 || datetime.tm_mon > 11 ||
        datetime.tm_mday < 1 || datetime.tm_mday > 31 ||
        datetime.tm_hour < 0 || datetime.tm_hour > 23 ||
        datetime.tm_min < 0 || datetime.tm_min > 59) {
        printf("Invalid date/time input\n");
        // return 1;
    }

    time_t result = mktime(&datetime);
    printf("Unix timestamp: %ld\n", result);

    // return 0;

    cwTimeStamp time;
	std::string ActionDay = time_update->ActionDay;
	std::string tradingTime = time_update->UpdateTime;
    if(0 != strcmp(cur_date,time_update->ActionDay))
    {
        memcpy(cur_date,time_update->ActionDay,sizeof(TThostFtdcDateType));
        covert_time_string()
    }

	time.SetYear(atoi(ActionDay.substr(0, 4).c_str()));
	time.SetMonth(atoi(ActionDay.substr(4, 2).c_str()));
	time.SetDay(atoi(ActionDay.substr(6, 2).c_str()));

	int hour = 0, minute = 0, second = 0;
#ifdef _MSC_VER
	sscanf_s(time_update->UpdateTime, "%d:%d:%d", &hour, &minute, &second);
#else
	sscanf(pData->UpdateTime, "%d:%d:%d", &hour, &minute, &second);
#endif // _MSC_VER

	SetHour(hour);
	SetMinute(minute);
	SetSecond(second);
	SetMicrosecond(time_update->UpdateMillisec * 1000);

	current_second = (int64_t)(time.GetTotalMicrosecond());
}