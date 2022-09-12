//
// Created by Jack_shen on 2022/9/12.
//

#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <cstdio>
#include <string>

#define USERCAPACITY 20

typedef struct userInfo
{
    std::string userID; // U001
    std::string userName; // no more than 10
    std::string password; // no more than 20
    std::string phonenumber; // no more than 40, numbers only
    std::string address; // nomore than 40,
    std::string userState; // activate, inactivate

}userInfo;


class LoginScene
{
private:
    userInfo *userInfoList[USERCAPACITY];// 预设用户量上限为20
public:
    LoginScene();
    void loadUserInfo(); //在初始化的时候从文件中读取信息或创建新文件
    void selectOpt(); // 显示选择选项, 并接受回答, 从而调用其他函数或类
    void userLogin();
    void userRegister();
    void adminLogin();
    void selectUserOpt(); // 用户中心选择显示和接收
    ~LoginScene();
};

#endif //LOGINSCENE_H
