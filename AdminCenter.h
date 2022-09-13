//
// Created by Jack_shen on 2022/9/13.
//

#ifndef CAP_ADMINCENTER_H
#define CAP_ADMINCENTER_H
#include "AuctionSystem.h"
#include "LoginScene.h"

class AdminCenter {
    AuctionSystem * auctionSystem; // 里面有commodityList 和 orderInfoList
    userInfo **userInfoList;
    int userIdx = 0;

public:
    AdminCenter(userInfo *_userInfoList[], int _idx);
    void loadUserInfo();

    void selectOpt(); //展示并选择选项
    void viewCommodityList();
    void viewOrderList();
    void searchCommodity();
    void cancelCommodity();
    void viewUserList();
    void banUser();
    void endAuction(); // 最重要的函数
    ~AdminCenter();
    userInfo *createUser(std::string &buffer);
};


#endif //CAP_ADMINCENTER_H
