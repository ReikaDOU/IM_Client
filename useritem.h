#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
#include<QMouseEvent>
namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(QWidget *parent = nullptr);
    ~UserItem();
    void mouseDoubleClickEvent(QMouseEvent* event);
signals:
    void SIG_userItemClicked(int id);
private:
    Ui::UserItem *ui;
public slots:
    void slot_setInfo(int id,QString name,int state=1,int iconid=1,QString feeling ="这是一个测试");
public:
    int m_id;
    QString m_name;
    int m_state;
    int m_iconid;
    QString m_feeling;
private slots:
    //void on_pb_icon_clicked();
};

#endif // USERITEM_H
