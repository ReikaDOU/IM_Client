#pragma once
#include"INetMediator.h"

class TcpClientMediator :public INetMediator
{
    Q_OBJECT
signals:
    void SIG_ReadyData(long lSendIp,char* buf,int nLen);
public:
	TcpClientMediator();
	~TcpClientMediator();
	//初始化网络
	bool OpenNet();
	//关闭网络
	void CloseNet();
	//发送数据
    bool SendData(long lSendIp, char* buf, int nLen);
	//处理数据
    void DealData(long lSendIp, char* buf, int nLen);
};
