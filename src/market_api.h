#ifndef __MARKET_API__
#define __MARKET_API__

#include "ThostFtdcMdApi.h"

class market_api:public CThostFtdcMdApi
{
private:
    /* data */
public:
    market_api(char *subscribe_file_path);
    ~market_api();
};


#endif //__MARKET_API__
