#ifndef USERCENTER_H
#define USERCENTER_H

#include <QMainWindow>
#include "config.h"
#include "auctionsystem.h"
#include <time.h>
#include "mymessagebox.h"
#include "commoditybox.h"
namespace Ui {
class UserCenter;
}

class UserCenter : public QMainWindow
{
    Q_OBJECT
    userInfo *curUser;
    AuctionSystem *auctionSystem;
    tm *ltm;
    myTimer *_myTimer;
    MyMessageBox *bidScene;
    CommodityBox *commodityBox;

public:
    UserCenter(QWidget *parent, userInfo *curUser, AuctionSystem *auctionSystem);
    ~UserCenter();

private:
    Ui::UserCenter *ui;
    void showUserInfo();
    void searchCommodityList_b(); //买家查看/搜索: 只显示在售的商品
    void searchCommodityList_s(); //卖家查看/搜索: 只显示属于卖家自己的商品
    void showOrderList_b(); //买家查看: 仅查看买家是自己的订单
    void showOrderList_s(); //卖家查看: 仅查看卖家是自己的订单
    void addCommodity(); //卖家发布商品
    QString generateDate(); //卖家发布商品时间
    bool isDigitString(const QString& src) {
        const char *s = src.toUtf8().data();
        while(*s && ((*s>='0' && *s<='9') || *s == '.'))s++;
        return !bool(*s);
    }
};

#endif // USERCENTER_H
