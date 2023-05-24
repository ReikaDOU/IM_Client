#include "ckernel.h"
#include"TcpClientMediator.h"
#include"mychatdialog.h"
#include<QMessageBox>
#include <qdebug.h>
#include<QTextCodec>
#define NetPackFunMap(a) m_netProtocalMap[a-DEF_PROTOCAL_BASE-10]
void CKernel::setProtocalMap()
{
    memset(m_netProtocalMap,0,sizeof(m_netProtocalMap));
    NetPackFunMap(DEF_PACK_REGISTER_RS)     = &CKernel::slot_registerRs;
    NetPackFunMap(DEF_PACK_LOGIN_RS)        = &CKernel::slot_loginRs;
    NetPackFunMap(DEF_PACK_FRIEND_INFO)     = &CKernel::slot_friendInfoRq;
    NetPackFunMap(DEF_PACK_CHAT_RQ)         = &CKernel::slot_ChatRq;
    NetPackFunMap(DEF_PACK_CHAT_RS)         = &CKernel::slot_ChatRs;
}

CKernel::CKernel(QObject *parent) :
    QObject(parent),m_id(0),m_state(0),m_iconid(0)
{
    qDebug()<<__func__;

    //创建登录注册窗口对象
    m_loginDialog = new LoginDialog;
    m_loginDialog->showNormal();
    //初始中介者对象
    m_tcpClient = new TcpClientMediator;


    //绑定接收数据信号与槽函数
    connect(m_tcpClient,SIGNAL(SIG_ReadyData(long,char*,int)),
            this,SLOT(slot_dealData(long,char*,int)));
    //-------绑定登录注册信号与槽
    connect(m_loginDialog,SIGNAL(SIG_LoginCommit(QString,QString)),
            this,SLOT(slot_LoginCommit(QString,QString)));
    connect(m_loginDialog,SIGNAL(SIG_RegisterCommit(QString,QString,QString)),
            this,SLOT(slot_RegisterCommit(QString,QString,QString)));
    //定义对话框
    m_mainWnd = new MyChatDialog;
    //打开网络
    if(!m_tcpClient->OpenNet())
    {
        QMessageBox::about(m_mainWnd,"提示","打开网络失败");
        exit(0);
    }








    //m_mainWnd->show();

    setProtocalMap();


}

CKernel::~CKernel()
{
    //回收login窗口
    if(m_loginDialog)
    {
        m_loginDialog->hide();
        delete m_loginDialog;
        m_loginDialog = NULL;
    }
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

void CKernel::utf8ToGb2312(char *gbbuf, int nLen, QString &utf8)
{
    //转码对象
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    //类型数组封装类：转码、写IO操作
    QByteArray ba = gb2312code->fromUnicode(utf8);

    strcpy_s(gbbuf,nLen,ba.data());
}

QString CKernel::gb2312ToUtf8(char *gbbuf)
{
    QTextCodec* gb2312code = QTextCodec::codecForName("gb2312");
    return gb2312code->toUnicode(gbbuf);
}

void CKernel::slot_dealData(long lSendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    qDebug()<< lSendIp << ":" << buf << endl;
    //获取协议头：每个协议头对应一个处理函数，映射表
    int type = *(int*)buf;
    //判断协议在映射数组范围
    if(type>=DEF_PROTOCAL_BASE+10 && type<DEF_PROTOCAL_BASE+DEF_PROTOCAL_COUNT+10)
    {
        //获取协议对应数组下标
        PFUN pf = NetPackFunMap(type);
        //函数指针存在，调取对应处理函数
        if(pf)
        {
            (this->*pf)(buf,nLen);
        }
    }
    //回收创建空间
    delete []buf;

}

void CKernel::slot_loginRs(char *buf, int nLen)
{
    qDebug()<<__func__;
    STRU_LOGIN_RS* rs = (STRU_LOGIN_RS*)buf;
    switch (rs->result)
    {
        case user_not_exist:
            QMessageBox::about(this->m_loginDialog,"提示","登录失败，用户不存在");
            break;
        case password_error:
            QMessageBox::about(this->m_loginDialog,"提示","登录失败，密码错误");
            break;
        case login_success:
            //QMessageBox::about(this->m_loginDialog,"提示","登录成功");
            {
                m_loginDialog->hide();
                m_mainWnd->showNormal();
                m_id = rs->userid;
            }
            break;
        default:
            break;
    }

}

void CKernel::slot_registerRs(char *buf, int nLen)
{
    qDebug()<<__func__;
    //1、拆包
    STRU_REGISTER_RS* rs=(STRU_REGISTER_RS*)buf;
    //2、判断注册结果
    switch (rs->result)
    {
    case user_is_exist:
        QMessageBox::about(this->m_loginDialog,"提示","注册失败,用户已存在");
        break;
    case register_success:
        QMessageBox::about(this->m_loginDialog,"提示","注册成功");
        break;
    case register_fail:
        QMessageBox::about(this->m_loginDialog,"提示","注册失败,网络或数据库出错");
        break;
    default:
        break;
    }
}
//提交登录
void CKernel::slot_LoginCommit(QString tel, QString password)
{
    //QString->string
    std::string strTel = tel.toStdString();
    std::string strPwd = password.toStdString();
    //封包
    STRU_LOGIN_RQ rq;
    strcpy(rq.tel,strTel.c_str());
    strcpy(rq.password,strPwd.c_str());

    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

void CKernel::slot_RegisterCommit(QString tel, QString password, QString name)
{
    //QString->string
    std::string strTel = tel.toStdString();
    std::string strPwd = password.toStdString();
    std::string strName = name.toStdString();
    //封包
    STRU_REGISTER_RQ rq;
    strcpy(rq.tel,strTel.c_str());
    strcpy(rq.password,strPwd.c_str());
    //strcpy(rq.name,strName.c_str());

    utf8ToGb2312(rq.name,sizeof(rq.name),name);

    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

void CKernel::slot_friendInfoRq(char *buf, int nLen)
{
    STRU_FRIEND_INFO *info = (STRU_FRIEND_INFO*) buf;
    QString tmpName = gb2312ToUtf8(info->name);
    QString tmpFeeling = gb2312ToUtf8(info->feeling);

    if(m_id==info->userid)//id是自己
    {
        m_mainWnd->slot_setInfo(tmpName,info->iconid,tmpFeeling);
        m_name = tmpName;
        m_iconid = info->iconid;
        m_state = info->state;
        m_feeling = tmpFeeling;
        return;
    }
    if(m_mapIdToUserItem.find(info->userid) ==m_mapIdToUserItem.end() )
    {
        UserItem* item = new UserItem;
        item->slot_setInfo(info->userid,tmpName,info->state,info->iconid,tmpFeeling);

        //4·2、给控件绑定点击的信号和槽
        connect(item,SIGNAL(SIG_userItemClicked(int)),this,SLOT(slot_userItemClicked(int)));
        //4·3、创建聊天窗口，但不显示
        ChatDialog*chat=new ChatDialog;
        chat->slot_setInfo(info->userid,m_name);
        //4·4、给聊天窗口绑定发送数据的信号和槽函数
        connect(chat,SIGNAL(SIG_SendChatMsg(int,QString)),this,SLOT(slot_SendChatMsg(int,QString)));

        m_mainWnd->slot_addFriend(item);
        m_mapIdToUserItem[info->userid]=item;

    }
    else
    {
        UserItem* item = m_mapIdToUserItem[info->userid];
        if(item&&item->m_state ==0 && info->state == 1)
        {
            qDebug()<<QString("用户[%1]上线").arg(tmpName);
        }
        item->slot_setInfo(info->userid,tmpName,info->state,info->iconid,tmpFeeling);
    }
}

void CKernel::slot_userItemClicked(int id)
{
    if(m_mapIdToChatDialog.find(id)!=m_mapIdToChatDialog.end())
    {
        ChatDialog* chat = m_mapIdToChatDialog[id];
        chat->showNormal();
    }
}

void CKernel::slot_SendChatMsg(int id, QString content)
{
    qDebug()<<__func__<<id<<content;
    //1、封包
    STRU_CHAT_RQ rq;
    //发送的聊天内容不需要转码，因为两个客户端使用都是utf8
    rq.userid=m_id;
    rq.friendid=id;
    //兼容中文
    std::string strContent=content.toStdString();
    strcpy(rq.content,strContent.c_str());
    //2、聊天请求发送给服务器
    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

void CKernel::slot_ChatRq(char *buf, int nLen)
{
    STRU_CHAT_RQ* rq= (STRU_CHAT_RQ*)buf;
    if(m_mapIdToChatDialog.count(rq->userid)>0)
    {
        ChatDialog* chat = m_mapIdToChatDialog[rq->userid];
        chat->slot_setChatMsg(QString::fromStdString(rq->content));
    }
}

void CKernel::slot_ChatRs(char *buf, int nLen)
{
    STRU_CHAT_RS* rs= (STRU_CHAT_RS*)buf;
    if(m_mapIdToChatDialog.count(rs->userid)>0)
    {
        ChatDialog* chat = m_mapIdToChatDialog[rs->userid];
        chat->slot_setUserOffline();
    }
}

