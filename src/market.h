#ifndef __MARKET_H__
#define __MARKET_H__

#include "ThostFtdcMdApi.h"
#include <vector>
#include <string>
#include <iostream>
#include "memory_log.h"

extern void get_user_info(CThostFtdcReqUserLoginField *log_user, CThostFtdcMdApi *pUserMdApi);

class Market:public CThostFtdcMdSpi
{
    public:
    Market(CThostFtdcMdApi *RegisterSpi);
    ~Market();

    bool connect();
    void virtual  OnFrontConnected()
    {
		std::cout <<"OnFrontConnected !!!\n" << std::endl;
        front_connected = true;
    }
	// 当客户端与交易托管系统通信连接断开时，该方法被调用
	virtual void OnFrontDisconnected(int nReason)
	{
		// 当发生这个情况后，API会自动重新连接，客户端可不做处理
		std::cout <<"<OnFrontDisconnected>\n" << nReason <<std::endl;
		std::cout <<"\tnReason= = [%d]" << nReason <<std::endl;
		std::cout <<"</OnFrontDisconnected>\n" << nReason <<std::endl;
	}
    void ReqUserLogin()
    {
        if(!pUserMdApi) return;
		CThostFtdcReqUserLoginField reqUserLogin = {0};
        int num  = pUserMdApi->ReqUserLogin(&reqUserLogin,2);
		std::cout << "login rsp " << num <<std::endl;
    }
	
    void SubscribeMarketData()//收行情
	{
		int md_num = 0;
		char **ppInstrumentID = new char*[5000];
		for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++)
		{
			if (count1 < md_InstrumentID.size() / 500)
			{
				int a = 0;
				for (a; a < 500; a++)
				{
					ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->SubscribeMarketData(ppInstrumentID, a);
				// LOG((result == 0) ? "订阅行情请求1......发送成功\n" : "订阅行情请求1......发送失败，错误序号=[%d]\n", result);
			}
			else if (count1 == md_InstrumentID.size() / 500)
			{
				int count2 = 0;
				for (count2; count2 < md_InstrumentID.size() % 500; count2++)
				{
					ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->SubscribeMarketData(ppInstrumentID, count2);
				// LOG((result == 0) ? "订阅行情请求2......发送成功\n" : "订阅行情请求2......发送失败，错误序号=[%d]\n", result);
			}
		}
	}

	///深度行情通知
	#define LOG printf
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
	{
		//获取系统时间
		// SYSTEMTIME sys;
		// GetLocalTime(&sys);
		// LOG("%02d:%02d:%02d.%03d\t",
		// 	sys.wHour,
		// 	sys.wMinute,
		// 	sys.wSecond,
		// 	sys.wMilliseconds);
		LOG("<OnRtnDepthMarketData>");
		if (pDepthMarketData)
		{
			LOG("\tTradingDay [%s]\n", pDepthMarketData->TradingDay);
			LOG("\tInstrumentID [%s]", pDepthMarketData->InstrumentID);
			// LOG("\tExchangeID [%s]", pDepthMarketData->ExchangeID);
			// LOG("\tExchangeInstID [%s]\n", pDepthMarketData->ExchangeInstID);
			LOG("\tUpdateTime [%s]", pDepthMarketData->UpdateTime);
			LOG("\tActionDay [%s]\n", pDepthMarketData->ActionDay);
			LOG("\tVolume [%d]\n", pDepthMarketData->Volume);
			LOG("\tUpdateMillisec [%d]", pDepthMarketData->UpdateMillisec);
			LOG("\tAskPrice1 [%.8lf]", (pDepthMarketData->AskPrice1 > 10000000) ? 0 : pDepthMarketData->AskPrice1);
			LOG("\tAskVolume1 [%d]\n", pDepthMarketData->AskVolume1);
			LOG("\tAskPrice2 [%.8lf]\n", (pDepthMarketData->AskPrice2 > 10000000) ? 0 : pDepthMarketData->AskPrice2);
			LOG("\tBidPrice1 [%.8lf] ", (pDepthMarketData->BidPrice1 > 10000000) ? 0 : pDepthMarketData->BidPrice1);
			LOG("\tBidVolume1 [%d]\n", pDepthMarketData->BidVolume1);
			// LOG("\tBidVolume2 [%d]\n", pDepthMarketData->BidVolume2);
			// LOG("\tBidPrice2 [%.8lf]\n", (pDepthMarketData->BidPrice2 > 10000000) ? 0 : pDepthMarketData->BidPrice2);
			// LOG("\tAskVolume2 [%d]\n", pDepthMarketData->AskVolume2);
			// LOG("\tBidVolume3 [%d]\n", pDepthMarketData->BidVolume3);
			// LOG("\tBidPrice3 [%.8lf]", (pDepthMarketData->BidPrice3 > 10000000) ? 0 : pDepthMarketData->BidPrice3);
			// LOG("\tAskVolume3 [%d]\n", pDepthMarketData->AskVolume3);
			// LOG("\tAskPrice3 [%.8lf]", (pDepthMarketData->AskPrice3 > 10000000) ? 0 : pDepthMarketData->AskPrice3);
			// LOG("\tBidPrice4 [%.8lf]", (pDepthMarketData->BidPrice4 > 10000000) ? 0 : pDepthMarketData->BidPrice4);
			// LOG("\tBidVolume4 [%d]\n", pDepthMarketData->BidVolume4);
			// LOG("\tAskPrice4 [%.8lf]", (pDepthMarketData->AskPrice4 > 10000000) ? 0 : pDepthMarketData->AskPrice4);
			// LOG("\tAskVolume4 [%d]\n", pDepthMarketData->AskVolume4);
			// LOG("\tBidPrice5 [%.8lf]", (pDepthMarketData->BidPrice5 > 10000000) ? 0 : pDepthMarketData->BidPrice5);
			// LOG("\tBidVolume5 [%d]\n", pDepthMarketData->BidVolume5);
			// LOG("\tAskPrice5 [%.8lf]", (pDepthMarketData->AskPrice5 > 10000000) ? 0 : pDepthMarketData->AskPrice5);
			// LOG("\tAskVolume5 [%d]\n", pDepthMarketData->AskVolume5);
			LOG("\tLastPrice [%.8lf]\n", (pDepthMarketData->LastPrice > 10000000) ? 0 : pDepthMarketData->LastPrice);
			LOG("\tPreSettlementPrice [%.8lf]\n", (pDepthMarketData->PreSettlementPrice > 10000000) ? 0 : pDepthMarketData->PreSettlementPrice);
			LOG("\tPreClosePrice [%.8lf]\n", (pDepthMarketData->PreClosePrice > 10000000) ? 0 : pDepthMarketData->PreClosePrice);
			LOG("\tPreOpenInterest [%.8lf]\n", (pDepthMarketData->PreOpenInterest > 10000000) ? 0 : pDepthMarketData->PreOpenInterest);
			LOG("\tOpenPrice [%.8lf]\n", (pDepthMarketData->OpenPrice > 10000000) ? 0 : pDepthMarketData->OpenPrice);
			LOG("\tHighestPrice [%.8lf]\n", (pDepthMarketData->HighestPrice > 10000000) ? 0 : pDepthMarketData->HighestPrice);
			LOG("\tLowestPrice [%.8lf]\n", (pDepthMarketData->LowestPrice > 10000000) ? 0 : pDepthMarketData->LowestPrice);
			LOG("\tTurnover [%.8lf]\n", (pDepthMarketData->Turnover > 10000000) ? 0 : pDepthMarketData->Turnover);
			LOG("\tOpenInterest [%.8lf]\n", (pDepthMarketData->OpenInterest > 10000000) ? 0 : pDepthMarketData->OpenInterest);
			LOG("\tClosePrice [%.8lf]\n", (pDepthMarketData->ClosePrice > 10000000) ? 0 : pDepthMarketData->ClosePrice);
			LOG("\tSettlementPrice [%.8lf]\n", (pDepthMarketData->SettlementPrice > 10000000) ? 0 : pDepthMarketData->SettlementPrice);
			LOG("\tUpperLimitPrice [%.8lf]\n", (pDepthMarketData->UpperLimitPrice > 10000000) ? 0 : pDepthMarketData->UpperLimitPrice);
			LOG("\tLowerLimitPrice [%.8lf]\n", (pDepthMarketData->LowerLimitPrice > 10000000) ? 0 : pDepthMarketData->LowerLimitPrice);
			// LOG("\tPreDelta [%.8lf]\n", (pDepthMarketData->PreDelta > 10000000) ? 0 : pDepthMarketData->PreDelta);
			// LOG("\tCurrDelta [%.8lf]\n", (pDepthMarketData->CurrDelta > 10000000) ? 0 : pDepthMarketData->CurrDelta);
			LOG("\tAveragePrice [%.8lf]\n", (pDepthMarketData->AveragePrice > 10000000) ? 0 : pDepthMarketData->AveragePrice);
		}
		LOG("</OnRtnDepthMarketData>\n");
	};


	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
	{
		log("<OnRspSubMarketData>\n");
		if (pSpecificInstrument)
		{
			printf("\tInstrumentID [%s]\n", pSpecificInstrument->InstrumentID);
		}
		if (pRspInfo)
		{
			printf("\tErrorMsg [%s]\n", pRspInfo->ErrorMsg);
			printf("\tErrorID [%d]\n", pRspInfo->ErrorID);
		}
		printf("\tnRequestID [%d]\n", nRequestID);
		printf("\tbIsLast [%d]\n", bIsLast);
		printf("</OnRspSubMarketData>\n");
		if (bIsLast)
		{
			// SetEvent(xinhao);
		}
	};
    ///订阅询价请求
	void SubscribeForQuoteRsp()
	{
		int md_num = 0;
		char **ppInstrumentID = new char*[5000];
		for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++)
		{
			if (count1 < md_InstrumentID.size() / 500)
			{
				int a = 0;
				for (a; a < 500; a++)
				{
					ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->SubscribeForQuoteRsp(ppInstrumentID, a);
				// LOG((result == 0) ? "订阅询价请求1......发送成功\n" : "订阅询价请求1......发送失败，错误序号=[%d]\n", result);
			}
			else if (count1 == md_InstrumentID.size() / 500)
			{
				int count2 = 0;
				for (count2; count2 < md_InstrumentID.size() % 500; count2++)
				{
					ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->SubscribeForQuoteRsp(ppInstrumentID, count2);
				// LOG((result == 0) ? "订阅询价请求2......发送成功\n" : "订阅询价请求2......发送失败，错误序号=[%d]\n", result);
			}
		}
	}
    
	void UnSubscribeMarketData()
	{
		int md_num = 0;
		char **ppInstrumentID = new char*[5000];
		for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++)
		{
			if (count1 < md_InstrumentID.size() / 500)
			{
				int a = 0;
				for (a; a < 500; a++)
				{
					ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->UnSubscribeMarketData(ppInstrumentID, a);
				// LOG((result == 0) ? "退订行情请求1......发送成功\n" : "退订行情请求1......发送失败，错误序号=[%d]\n", result);
			}
			else if (count1 == md_InstrumentID.size() / 500)
			{
				int count2 = 0;
				for (count2; count2 < md_InstrumentID.size() % 500; count2++)
				{
					ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->UnSubscribeMarketData(ppInstrumentID, count2);
				// LOG((result == 0) ? "退订行情请求2......发送成功\n" : "退订行情请求2......发送失败，错误序号=[%d]\n", result);
			}
		}
	}

	void UnSubscribeForQuoteRsp()
	{
		int md_num = 0;
		char **ppInstrumentID = new char*[5000];
		for (int count1 = 0; count1 <= md_InstrumentID.size() / 500; count1++)
		{
			if (count1 < md_InstrumentID.size() / 500)
			{
				int a = 0;
				for (a; a < 500; a++)
				{
					ppInstrumentID[a] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->UnSubscribeForQuoteRsp(ppInstrumentID, a);
				// LOG((result == 0) ? "退订询价请求1......发送成功\n" : "退订询价请求1......发送失败，错误序号=[%d]\n", result);
			}
			else if (count1 == md_InstrumentID.size() / 500)
			{
				int count2 = 0;
				for (count2; count2 < md_InstrumentID.size() % 500; count2++)
				{
					ppInstrumentID[count2] = const_cast<char *>(md_InstrumentID.at(md_num).c_str());
					md_num++;
				}
				int result = pUserMdApi->UnSubscribeForQuoteRsp(ppInstrumentID, count2);
				// LOG((result == 0) ? "退订询价请求2......发送成功\n" : "退订询价请求2......发送失败，错误序号=[%d]\n", result);
			}
		}
	}

    void subscribe_data(uint8_t flag_subScribe)
    {
        if(1&flag_subScribe)
        {
            SubscribeMarketData();
        } else {
            UnSubscribeMarketData();
        }
        if(2 & flag_subScribe)
        {
            SubscribeForQuoteRsp();
        } else {
            UnSubscribeForQuoteRsp();
        }
    }
    private:
    CThostFtdcReqUserLoginField user_login_info;
    CThostFtdcMdApi *pUserMdApi;
    std::string chanFrontMdAddr;
    std::vector<std::string> md_InstrumentID;

    int nRequestID;
    bool front_connected;
};
#endif