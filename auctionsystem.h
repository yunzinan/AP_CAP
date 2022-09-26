#ifndef AUCTIONSYSTEM_H
#define AUCTIONSYSTEM_H

#include "config.h"
#include "myvector.h"
#include <time.h>

class AuctionSystem
{
    commodityInfo *commodityInfoList[COMMODITYCAPACITY];
    orderInfo *orderInfoList[ORDERCAPACITY];
    userInfo **userInfoList;
    int commodityIdx = 0;
    int orderIdx = 0;
    int userIdx = 0;
    tm *ltm;
    myTimer *_myTimer;
    MyVector vector[COMMODITYCAPACITY];
public:
    AuctionSystem(userInfo **userInfoList, int userIdx);
    void loadCommodityInfo();
    void loadOrderInfo();
    commodityInfo* createCommodity(const QString &buffer);
    orderInfo* createOrder(const QString &buffer);
    ~AuctionSystem();
    commodityList* getCommodity_b(const QString &commodityName);
    commodityList* getCommodity_s(const QString &commodityName, const QString &sellerID);
    commodityList* getCommodity_a(const QString &commodityName); //返回所有的商品
    orderList* getOrderList_b(const QString &buyerID);
    orderList* getOrderList_s(const QString &sellerID);
    orderList* getOrderList_a(); //返回所有的订单
    QString addCommoditycheck(); //先判断是否能够继续添加新商品
    void addCommodity(commodityInfo *cur);
    bool bidCheck(const QString &buyerID, const QString &commodityID);
    void addOrder(const QString &commodityID, const QString &sellerID, const QString &buyerID, float bidPrice);
    QString generateTime(); //添加订单时使用
    commodityInfo* getCommodity(const QString& commodityID); //竞拍时候用
    userList* getUserList(const QString &username); //管理员功能
    orderList* calcResult();//核心功能
    int ID2int(const QString &str);
};

#endif // AUCTIONSYSTEM_H
