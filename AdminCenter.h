//
// Created by Jack_shen on 2022/9/13.
//

#ifndef CAP_ADMINCENTER_H
#define CAP_ADMINCENTER_H
#include "AuctionSystem.h"
#include "LoginScene.h"
#include "config.h"

class AdminCenter {
    AuctionSystem * auctionSystem; // 里面有commodityList 和 orderInfoList
    userInfo **userInfoList;
    int userIdx = 0;

public:
    AdminCenter(userInfo *_userInfoList[], int _idx);
    void loadUserInfo();//deprecated: 另一种解决方案: LoginScene不是构造时就loadUserInfo, 而是进入UserLogin函数时才进行load, 同时释放&写入放在UserLoginExit处
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
