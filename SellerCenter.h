//
// Created by Jack_shen on 2022/9/12.
//

#ifndef CAP_SELLERCENTER_H
#define CAP_SELLERCENTER_H

#include <iostream>
#include <ctime>
#include "LoginScene.h"
#include "AuctionSystem.h"

typedef struct myTimer{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}myTimer;

class SellerCenter {
    userInfo *curUser;
    AuctionSystem *auctionSystem;
    tm *ltm;
    myTimer *_myTimer;
public:
    SellerCenter(userInfo *_curUser, AuctionSystem * _system);
    void selectOpt();
    void releaseCommodity();
    void viewCommodityList(); // 查看 该用户 发布的商品
    void modifyCommodityInfo(); // 先查找, 然后修改, 并且商品属于自己
    void cancelCommodity(); // 先查找是否存在这个商品 并且商品属于自己 然后修改属性为下架
    void viewOrderList(); // 订单系统还未实现
    std::string generateTime();
    std::string generateDate();
    ~SellerCenter();
};


#endif //CAP_SELLERCENTER_H
