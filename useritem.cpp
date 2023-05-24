#include "useritem.h"
#include "ui_useritem.h"
#include<QIcon>
#include<QBitmap>
UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_EMIT SIG_userItemClicked(m_id);
}

void UserItem::slot_setInfo(int id, QString name, int state, int iconid, QString feeling)
{
    m_id = id;
    m_name = name;
    m_state = state;
    m_iconid = iconid;
    m_feeling = feeling;

    //设置标签
    ui->lb_name->setText(m_name);
    ui->le_feeling->setText(m_feeling);

    QString pathIcon = QString ("/icon/%1.jpeg").arg(m_iconid);
    if(m_state)
    {
        ui->pb_icon->setIcon(QIcon(pathIcon));
    }
    else
    {
        //图标添加位图是黑白的
        QBitmap bmp;
        bmp.load(pathIcon);
        ui->pb_icon->setIcon(bmp);
    }
    //重绘
    this->repaint();
}

//void UserItem::on_pb_icon_clicked()
//{
//    Q_EMIT SIG_userItemClicked(m_id);
//}

