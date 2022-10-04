#ifndef ADMINCENTER_H
#define ADMINCENTER_H

#include <QMainWindow>
#include "auctionsystem.h"
#include "config.h"
#include "commoditybox.h"
namespace Ui {
class AdminCenter;
}

class AdminCenter : public QMainWindow
{
    Q_OBJECT
    AuctionSystem *auctionSystem;
    CommodityBox *commodityBox;
public:
    AdminCenter(QWidget *parent, AuctionSystem *auctionSystem);
    ~AdminCenter();
    void showUserList();
    void showCommodityList();
    void showOrderList();
private:
    Ui::AdminCenter *ui;
    void showAuctionRes(orderList *ret);
};

#endif // ADMINCENTER_H
