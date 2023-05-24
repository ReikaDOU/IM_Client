#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"mychatdialog.h"
#include"INetMediator.h"
#include "PackDef.h"
#include"logindialog.h"
#include<QMap>
#include"useritem.h"
#include"chatdialog.h"
class CKernel;
typedef void(CKernel::*PFUN)(char* buf,int nLen);
class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
    //编码转换
    //QT使用UTF8编码中文，VS、MySQL使用GB2312编码
    //QString->char* gb2312
    static void utf8ToGb2312(char* gbbuf,int nLen,QString &utf8);
    //char* gb2312->string
    QString gb2312ToUtf8(char* gbbuf);

public slots:
    void slot_dealData(long lSendIp, char* buf, int nLen);
    //注册登录回复
    void slot_loginRs(char* buf,int nLen);
    void slot_registerRs(char* buf,int nLen);
    //处理登录信息请求
    void slot_LoginCommit(QString tel,QString password);
    //处理注册信息请求
    void slot_RegisterCommit(QString tel,QString password,QString name);
    //处理好友信息请求
    void slot_friendInfoRq(char* buf,int nLen);
    //点击某个用户的请求
    void slot_userItemClicked(int id);
    //处理聊天内容函数
    void slot_SendChatMsg(int id,QString content);
    //处理聊天请求
    void slot_ChatRq(char* buf,int nLen);
    //处理聊天回复
    void slot_ChatRs(char* buf,int nLen);
private:
    MyChatDialog* m_mainWnd;
    INetMediator* m_tcpClient;
    LoginDialog* m_loginDialog;
    //协议映射表
    PFUN m_netProtocalMap[DEF_PROTOCAL_COUNT];
    void setProtocalMap();
    //保存id 用户项映射关系
    QMap<int ,UserItem*> m_mapIdToUserItem;
    int m_id;
    QString m_name;
    int m_state;
    int m_iconid;
    QString m_feeling;
    //每个用户对应一个聊天窗口
    QMap<int ,ChatDialog*> m_mapIdToChatDialog;
};

#endif // CKERNEL_H
