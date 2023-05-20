#include "ckernel.h"
#include"TcpClientMediator.h"
#include<QMessageBox>
#include<QDebug>
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    //定义对话框
    m_mainWnd = new MyChatDialog;
    m_mainWnd->show();
    //初始中介者对象
    m_tcpClient = new TcpClientMediator;
    //打开网络
    if(!m_tcpClient->OpenNet())
    {
        QMessageBox::about(m_mainWnd,"提示","打开网络失败");
        exit(0);
    }

    //测试连接-----------------------
    char a[100] = "hello world";
    m_tcpClient->SendData(0, a, strlen("hello world") + 1);
    //测试连接-----------------------

    //绑定接收数据信号与槽函数
    connect(m_tcpClient,SIGNAL(SIG_ReadyData(long,char*,int)),
            this,SLOT(slot_dealData(long,char*,int)));
}

CKernel::~CKernel()
{
    //回收主窗口对象
    if(m_mainWnd)
    {
        m_mainWnd->hide();
        delete m_mainWnd;
        m_mainWnd = NULL;
    }
    //回收中介者对象
    if(m_tcpClient)
    {
        m_tcpClient->CloseNet();
        delete m_tcpClient;
        m_tcpClient = NULL;
    }
    exit(0);
}
#include<QDebug>
void CKernel::slot_dealData(long lSendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
}
