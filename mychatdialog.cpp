#include "mychatdialog.h"
#include "ui_mychatdialog.h"

MyChatDialog::MyChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MyChatDialog)
{
    ui->setupUi(this);
}

MyChatDialog::~MyChatDialog()
{
    delete ui;
}

