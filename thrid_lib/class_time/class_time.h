#include <stdint.h>
#include <memory>
#include "ThostFtdcUserApiStruct.h"

struct CThostFtdcDepthMarketDataField;
typedef std::shared_ptr<CThostFtdcDepthMarketDataField> cwMarketDataPtr;
class class_time{
    class_time(cwMarketDataPtr time_update);
    int diff_with_sys_second_ms();
    int diff_with_last_update_second_ms();
    int diff_with_compare_seconds_ms(int second_compare);
    private:
    int64_t current_second;
    int64_t sys_second;
    TThostFtdcDateType cur_date;
};