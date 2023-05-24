#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
signals:
    void SIG_LoginCommit(QString tel,QString password);
    void SIG_RegisterCommit(QString tel,QString password,QString name);
private slots:
    void on_pb_clear_clicked();

    void on_pb_commit_clicked();

    void on_pb_clear_re_clicked();

    void on_pb_commit_re_clicked();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
