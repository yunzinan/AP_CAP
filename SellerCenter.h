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
    SellerCenter(userInfo *_curUser);
    void selectOpt();
    void releaseCommodity();
    void viewCommodityList(); // 查看 该用户 发布的商品
//    void modifyCommodityInfo();
//    void cancelCommodity();
    void viewOrderList();
    std::string generateTime();
    std::string generateDate();
    ~SellerCenter();
};


#endif //CAP_SELLERCENTER_H
