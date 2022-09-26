#ifndef ADMINCENTER_H
#define ADMINCENTER_H

#include <QMainWindow>
#include "auctionsystem.h"
#include "config.h"
namespace Ui {
class AdminCenter;
}

class AdminCenter : public QMainWindow
{
    Q_OBJECT
    AuctionSystem *auctionSystem;
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
