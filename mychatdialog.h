#ifndef MYCHATDIALOG_H
#define MYCHATDIALOG_H

#include <QDialog>
#include<QVBoxLayout>
#include "useritem.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MyChatDialog; }
QT_END_NAMESPACE

class MyChatDialog : public QDialog
{
    Q_OBJECT

public:
    MyChatDialog(QWidget *parent = nullptr);
    ~MyChatDialog();
public slots:
    void slot_addFriend(UserItem* item);
    //设置ui控件属性
    void slot_setInfo(QString name,int iconId,QString feeling);
private:
    Ui::MyChatDialog *ui;

    //垂直布局的层
    QVBoxLayout* m_layout;
};
#endif // MYCHATDIALOG_H
