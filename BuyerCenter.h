//
// Created by Jack_shen on 2022/9/12.
//

#ifndef CAP_BUYERCENTER_H
#define CAP_BUYERCENTER_H

#include "LoginScene.h"
#include "AuctionSystem.h"
class BuyerCenter {
    AuctionSystem *auctionSystem;
    userInfo *curUser;
public:
    BuyerCenter(userInfo *_curUser, AuctionSystem *_system);
    void selectOpt();
    void viewCommodityList();
    void bidCommodity();
    void searchCommodity();
    void viewOrderList();
    void viewDetailedCommodity();
    ~BuyerCenter();
};


#endif //CAP_BUYERCENTER_H
