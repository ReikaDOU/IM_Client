#ifndef CKERNEL_H
#define CKERNEL_H

#include <QObject>
#include"mychatdialog.h"
#include"INetMediator.h"
class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = nullptr);
    ~CKernel();
signals:
public slots:
    void slot_dealData(long lSendIp, char* buf, int nLen);
private:
    MyChatDialog* m_mainWnd;
    INetMediator* m_tcpClient;
};

#endif // CKERNEL_H
