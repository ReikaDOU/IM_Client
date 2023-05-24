#include "logindialog.h"
#include "ui_logindialog.h"
#include<QMessageBox>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pb_clear_clicked()
{
    ui->le_tel->setText("");
    ui->le_password->setText("");
}


void LoginDialog::on_pb_commit_clicked()
{
    QString tel = ui->le_tel->text();
    QString password = ui->le_password->text();
    //输入校验
    QString tempTel = tel;
    if(tel.isEmpty()||password.isEmpty()||tempTel.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","手机号或密码不能为空");
        return ;
    }
    if(tel.length()> 15||password.length()>10)
    {
        QMessageBox::about(this,"提示","手机号不超过15位，密码不超过10位");
        return ;
    }

    Q_EMIT SIG_LoginCommit(tel,password);
}


void LoginDialog::on_pb_clear_re_clicked()
{
    ui->le_tel_re->setText("");
    ui->le_name_re->setText("");
    ui->le_password_re->setText("");
}


void LoginDialog::on_pb_commit_re_clicked()
{
    QString tel = ui->le_tel_re->text();
    QString password = ui->le_password_re->text();
    QString name =ui->le_name_re->text();
    //输入校验
    QString tempTel = tel;
    QString tempName = name;
    if(tel.isEmpty()||password.isEmpty()||name.isEmpty()||
            tempTel.remove(" ").isEmpty()||tempName.remove(" ").isEmpty())
    {
        QMessageBox::about(this,"提示","手机号、昵称、密码不能为空");
        return ;
    }
    if(tel.length()> 15||password.length()>10||name.length()>20)
    {
        QMessageBox::about(this,"提示","手机号不超过15位，密码不超过10位，昵称不超过20位");
        return ;
    }

    Q_EMIT SIG_RegisterCommit(tel,password,name);
}

