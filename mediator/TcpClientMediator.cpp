#pragma once
#include"TcpClientMediator.h"
#include"TcpClient.h"
#include<INetMediator.h>
TcpClientMediator::TcpClientMediator()
{
	m_pNet = new TcpClient(this);
}
TcpClientMediator::~TcpClientMediator()
{
	if (m_pNet)
	{
		delete m_pNet;
		m_pNet = nullptr;
	}
}

bool TcpClientMediator::OpenNet()
{
	if (!m_pNet->InitNet())
	{
		return false;
	}
	return true;
}

void TcpClientMediator::CloseNet()
{
	m_pNet->UnInitNet();
}

bool TcpClientMediator::SendData(long lSendIp, char* buf, int nLen)
{
	if (!m_pNet->SendData(lSendIp, buf, nLen))
	{
		return false;
	}
	return true;
}
#include <qdebug.h>
void TcpClientMediator::DealData(long lSendIp, char* buf, int nLen)
{
    qDebug()<< lSendIp << ":" << buf << endl;
    Q_EMIT SIG_ReadyData(lSendIp,buf,nLen);
}
