//
// Created by Jack_shen on 2022/9/12.
//

#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <cstdio>
#include <string>
#include "AuctionSystem.h"

#define USERCAPACITY 20

typedef struct userInfo

    {
        std::string userID; // U001
        std::string username; // no more than 10
        std::string password; // no more than 20
        std::string phonenumber; // no more than 40, numbers only
        std::string address; // no more than 40,
        float balance; // set precision 1
        std::string userState; // activate, inactivate
}userInfo;


class LoginScene
{
private:
    userInfo *userInfoList[USERCAPACITY];// 预设用户量上限为20
    userInfo *curUser;//记录当前登录的用户指针
    int idx = 0; //记录当前存在的用户数量, 数组记得要减1!
public:
    LoginScene();
    void loadUserInfo(); //在初始化的时候从文件中读取信息或创建新文件
    void selectOpt(); // 显示选择选项, 并接受回答, 从而调用其他函数或类
    void userLogin();
    userInfo* userLoginCheck(const std::string& username, const std::string& password);
    void userRegister(); //需要输入完整的信息
    std::string userRegisterCheck(const std::string& username); //检查用户名是否重复
    void adminLogin();
    void selectUserOpt(); // 用户中心选择显示和接收
    userInfo* createUser(std::string &buffer); //接收完整的一行信息并创建一个用户结构体, 返回其地址(初始化时读取)
    ~LoginScene();
};

#endif //LOGINSCENE_H
