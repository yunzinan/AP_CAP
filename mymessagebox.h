#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include "config.h"
#include "auctionsystem.h"
namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QWidget
{
    Q_OBJECT
    commodityInfo* cur;
    AuctionSystem * auctionSystem;
    userInfo *curUser;
public:
    explicit MyMessageBox(QWidget *parent, userInfo* curUser, commodityInfo* cur, AuctionSystem* auctionSystem);
    ~MyMessageBox();
    void showCommodityInfo();
    void purchase();

private:
    Ui::MyMessageBox *ui;
signals:
    void exitSignal();
};

#endif // MYMESSAGEBOX_H
