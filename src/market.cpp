#include "market.h"
#include "ThostFtdcUserApiStruct.h"
#include "memory_log.h"
#include <cstring>

using namespace std;
void get_user_info(CThostFtdcReqUserLoginField *log_user, CThostFtdcMdApi *pUserMdApi)
{
    strncpy(log_user->BrokerID, "9999",sizeof(log_user->BrokerID));
    strncpy(log_user->UserID, "047859",sizeof(log_user->UserID));
    strncpy(log_user->Password, "qian19876025~",sizeof(log_user->Password));
    return;
}
Market::Market(CThostFtdcMdApi *RegisterSpi)
{
    front_connected = false;
    if (!RegisterSpi)
    {
        log("error wrong init api !!!!\r\n");
        return;
    }
    log(" market init\r\n");
    pUserMdApi = RegisterSpi;
    get_user_info(&user_login_info, pUserMdApi);
    connect();
}
bool Market::connect()
{
    int i = 0;
    if (front_connected)
    {
        log("error front already connect!!!!\r\n");
        return true;
    }
    if (!pUserMdApi)
    {
        log("error api not register !!!!\r\n");
        return false;
    }
    pUserMdApi->RegisterSpi(this);
    log("be init 1\r\n");
    pUserMdApi->RegisterFront(const_cast<char *>("tcp://180.168.146.187:10131"));
    // pUserMdApi->RegisterFront(const_cast<char *>("tcp://180.168.146.187:10211"));
    pUserMdApi->Init();
    log("be init 2\r\n");
    while (false == front_connected)
    {
        if(1000  == i++) {
            log("wait\r\n");
        }
        continue;
    }
    ReqUserLogin();
    char **ppInstrumentID = new char*("cu2305");
    pUserMdApi->SubscribeMarketData(ppInstrumentID,1);
     pUserMdApi->SubscribeForQuoteRsp(ppInstrumentID,1);
    log("be init 3\r\n");
    pUserMdApi->Join();
    return true;
}