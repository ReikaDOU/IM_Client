#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QTime>
ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::slot_setInfo(int id,const QString &name)
{
    m_id =id;
    m_name = name;
    //聊天窗口的标题， 与【ip】的聊天
    setWindowTitle(QString("与【%1】的的聊天").arg(name));
}

void ChatDialog::slot_setUserOffline()
{
    ui->tb_chat->append(QString("[%1] %2 该用户不在线").arg(m_name)
                        .arg(QTime::currentTime().toString("hh:mm:ss")));
}

void ChatDialog::on_pb_send_clicked()
{
    //1、把用户输入的数据取出来
    //toPlanText取的是不带格式的纯文本
//    QString content=ui->te_chat->toPlainText();
//    if(content.isEmpty())
//    {
//        return ;
//    }
//    //2、清空编辑窗口
//    ui->te_chat->clear();
//    //3、添加数据到浏览窗口，【我】时间内容
//    //append是换行追加
//    ui->tb_chat->append(QString("【我】%1").arg(QTime::currentTime().toString("hh:mm:ss")));
//    ui->tb_chat->append(content);
    //4、数据发送出去
    //Q_EMIT SIG_SendChatMsg(m_id,content);
}

void ChatDialog::slot_setChatMsg(QString content)
{
    //【ip】时间 内容
    ui->tb_chat->append(QString("【%1】%2").arg(m_name).
                        arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
}
