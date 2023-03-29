
#include "market.h"
#include "market_api.h"
#include "memory_log.h"

Memory_log log_module(3000);
CThostFtdcMdApi  *UserMdApi;
Market *market;
void init_market_process()
{
    UserMdApi = CThostFtdcMdApi::CreateFtdcMdApi("./", false, false);
    if(UserMdApi)
    {
        market = new Market(UserMdApi);
    }
}
void init_trader_system_setting()
{
    init_market_process();
    // init_trader_proces();
    // init_strategy();
}
int main(void)
{
    init_trader_system_setting();
    // init_trade_strategy();
    // init_trade_prices_update_process();
    // init_trade_process();
}