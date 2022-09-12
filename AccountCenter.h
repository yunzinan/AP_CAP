//
// Created by Jack_shen on 2022/9/12.
//

#ifndef CAP_ACCOUNTCENTER_H
#define CAP_ACCOUNTCENTER_H

#include "LoginScene.h"

class AccountCenter {
    LoginScene *parent;
    userInfo *curUser;
public:
    void init(LoginScene *_parent, userInfo *_userInfo);
//    AccountCenter(LoginScene* _parent, userInfo* _curUser);
    void selectOpt(); // 显示并选择选项
    void viewUserInfo();
    void modifyUserInfo();
    void recharge();
};


#endif //CAP_ACCOUNTCENTER_H
