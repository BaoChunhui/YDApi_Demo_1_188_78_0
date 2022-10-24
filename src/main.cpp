#if defined(__linux__)
	#include <sys/socket.h>
	#include<unistd.h>
	#include<netinet/in.h>
	#include<arpa/inet.h>
	#include<unistd.h>
#endif

#include <iostream>
#include <vector>
#include <string>

#include<ydApi.h>
#include<ydDataStruct.h>
#include<ydDataType.h>
#include<ydError.h>
#include<ydUtil.h>
#include<YdUserApiInfo.h>

using namespace std;



int main(){
    string userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradeIP, udpTradePort;
    read_and_print_user_info("../config_files/user_info.txt", userID, pwd, appID, authCode, exchangeID, ydApiFunc, useProtocol, udpTradePort);
	getServerIP("../config_files/yd_config.txt", udpTradeIP);
	cout << "当前易达API版本号：" << getYDVersion() << endl;
	cout << "当前使用易达功能[basic(基础版) | extended(扩展版)]为：" << ydApiFunc << endl;
    print_yd_config("../config_files/yd_config.txt");
    myYDListener * plistener = get_plistener(ydApiFunc, userID, pwd, appID, authCode, exchangeID, useProtocol, udpTradeIP, udpTradePort);
	cout << "\n请输入命令(输入help获取命令提示)：" << endl;
	while (true)
	{
		string cmdLine;
		getline(cin, cmdLine);
		vector<string> cmdWords = splitCmdLine(cmdLine);
		vector<string>::iterator iter = cmdWords.begin();
		if (*iter == "login")
			plistener->login();
		else if (*iter == "logout")
			plistener->disconnect();
		else if (*iter == "exit")
		{
			cout << "\t退出成功" << endl;
			exit(0);
		}
		else if (*iter == "chgpwd")
		{
			if (cmdWords.size() == 3)
			{
				string oldPwd = *++iter;
				string newPwd = *++iter;
				plistener->chgPwd(oldPwd, newPwd);
			}
			else
				cerr << "\t修改命令格式错误，正确格式：chgpwd <oldPassWord> <newPassWord>" << endl;
		}
		else if (*iter == "sub")
		{
			for (++iter; iter != cmdWords.end(); ++iter)
				plistener->sub(*iter);
		}
		else if (*iter == "unsub")
		{
			for (++iter; iter != cmdWords.end(); ++iter)
				plistener->unsub(*iter);
		}
		else if (*iter == "order")
			plistener->putOrder(++iter, cmdWords.end());
		else if (*iter == "qryfund")
			plistener->qryFund();
		else if (*iter == "qryposition")
			plistener->qryPosition();
		else if (*iter == "qryorders")
			plistener->qryOrders();
		else if (*iter == "qryordersysid")
		{
			for (++iter; iter != cmdWords.end(); ++iter)
				plistener->qryOrderSys(atoi(iter->c_str()));
		}
		else if (*iter == "qryorderref")
		{
			for (++iter; iter != cmdWords.end(); ++iter)
				plistener->qryOrderRef(atoi(iter->c_str()));
		}
 		else if (*iter == "qrytrade")
 			plistener->qryTrade();
		else if (*iter == "cancel")
		{
			
			for (++iter; iter != cmdWords.end(); ++iter)
				plistener->cancelOrder(atoi(iter->c_str()), YD_YOF_Normal);
		}
		else
		{
			cout << "输入的命令错误，请重新输入" << endl;
		}
	}
	
    return 0;
}