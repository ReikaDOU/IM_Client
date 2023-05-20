#ifndef MYCHATDIALOG_H
#define MYCHATDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MyChatDialog; }
QT_END_NAMESPACE

class MyChatDialog : public QDialog
{
    Q_OBJECT

public:
    MyChatDialog(QWidget *parent = nullptr);
    ~MyChatDialog();

private:
    Ui::MyChatDialog *ui;
};
#endif // MYCHATDIALOG_H
