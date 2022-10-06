#pragma once
#if defined(__linux__)
	#include<netinet/in.h> // LINUX 地址结构体
#endif

#include<string>
#include<iostream>
#include<ydApi.h>
#include<ydDataStruct.h>
#include<ydDataType.h>
#include<ydError.h>
#include<ydUtil.h>

using namespace std;

string stringToUpper(string &inputString);  // 字符串全部大写
vector<string> splitCmdLine(string &cmdLine);  // 解析命令行
void print_yd_config(const string &fname);
void read_and_print_user_info(const string &fname, string &userID, string &pwd, string &appID, string &authCode, string &exchangeID, string &ydApiFunc, string &useProtocol);

class myYDListener : public YDListener
{
protected:
	YDApi *m_ydApi;
	const char *m_userID, *m_pwd, *m_appID, *m_authCode;
	string m_exchangeID;
	const YDExchange *m_pExchange;
	int m_maxOrderRef;
	// 查询上期所或能源所持仓
	void qry_position_shfe_or_ine(YDExtendedApi *);
	// 查询中金所持仓
	void qry_position_cffex(YDExtendedApi *);
	// 查询大商所持仓
	void qry_position_dce(YDExtendedApi *);

public:
	// 构造函数
	myYDListener(YDApi *ydApi, const char *userID, const char *pwd, const char *appID, const char *authCode, string exchangeID);
	// 析构函数
	~myYDListener()=default;
	// 连接完成，可以准备登录的回调函数
	void notifyReadyForLogin(bool hasLoginFailed) override;
	// 登录函数
    void login();
	// 登录函数的回调函数
	void notifyLogin(int errorNo, int maxOrderRef, bool isMonitor) override;
	// 推送初始化数据完成的回调函数
	void notifyFinishInit() override;
	// 断开连接
	void disconnect();
	// 修改密码
	void chgPwd(string &oldPwd, string &newPwd);
	// 修改密码的回调函数
	void notifyChangePassword(int errorNo) override;
	// 行情订阅函数
	void sub(string &instrumentID);
	// 行情回调函数，展示行情
	void notifyMarketData(const YDMarketData *pMarketData) override;
	// 取消订阅行情
	void unsub(string &instrumentID);
	// 下单
	virtual void putOrder(vector<string>::iterator, vector<string>::iterator);
	// 柜台报单成功回调
	void notifyOrder(const YDOrder *pOrder, const YDInstrument *pInstrument, const YDAccount *pAccount) override;
	// 柜台报单失败回调
	void notifyFailedOrder(const YDInputOrder *pFailedOrder, const YDInstrument *pInstrument, const YDAccount *pAccount) override;
	// 成交回调
	void notifyTrade(const YDTrade *pTrade, const YDInstrument *pInstrument, const YDAccount *pAccount) override;
	// 查询账户资金情况
	void qryFund();
	// 查询持仓
	void qryPosition();
	// 通过orderSysID查询报单
	void qryOrderSys(int orderSysID);
	// 通过orderRef查询报单
	void qryOrderRef(int orderRef);
	// 查询全部报单信息
	void qryOrders();
	// 查询成交信息
	void qryTrade();
	// 撤单
	virtual void cancelOrder(int orderSysID, int orderFlag);
	// 撤单失败的回调函数
	void notifyFailedCancelOrder(const YDFailedCancelOrder *pFailedCancelOrder, const YDExchange *pExchange, const YDAccount *pAccount) override;
};

myYDListener * get_plistener(string &ydApiFunc, string &userID, string &pwd, string &appID, string &authCode, string exchangeID, string useProtocol);