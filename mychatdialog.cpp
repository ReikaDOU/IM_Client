#include "mychatdialog.h"
#include "ui_mychatdialog.h"

MyChatDialog::MyChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyChatDialog)
{
    ui->setupUi(this);
    setWindowTitle("MyChat V1.0");
    //初始化QCBoxLayout指针
    m_layout = new QVBoxLayout;
    m_layout->setContentsMargins(0,0,0,0);//左右上下距离外边框多远
    m_layout->setSpacing(3);//每个控件之间的距离
    //设置控件的层
    ui->wdg_list->setLayout(m_layout);
}

MyChatDialog::~MyChatDialog()
{
    delete ui;
}

void MyChatDialog::slot_addFriend(UserItem *item)
{
    m_layout->addWidget(item);
}

void MyChatDialog::slot_setInfo(QString name, int iconId, QString feeling)
{
    ui->lb_name->setText(name);
    ui->le_feeling->setText(feeling);
    ui->pb_icon->setIcon(QIcon(QString(":/icon/%1.jpeg").arg(iconId)));
}
