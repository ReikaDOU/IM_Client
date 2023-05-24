#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
signals:
    void SIG_SendChatMsg(int id,QString content);

private slots:
    void on_pb_send_clicked();
public slots:
    void slot_setChatMsg(QString content);
    void slot_setInfo(int id,const QString &name);
    //聊天对象不在线
    void slot_setUserOffline();

private:
    Ui::ChatDialog *ui;
    int m_id;
    QString m_name;

};

#endif // CHATDIALOG_H
