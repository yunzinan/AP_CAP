//
// Created by Jack_shen on 2022/9/12.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include "LoginScene.h"
#include "AccountCenter.h"
#include "SellerCenter.h"

LoginScene::LoginScene() {
    this->loadUserInfo();
    this->selectOpt();
}

LoginScene::~LoginScene() {
    // 写文件
    std::fstream fout;
    fout.open("../res/userInfo.txt", std::ios::out | std::ios::trunc);//覆盖写入
    // 释放内存, 写入文件
    fout << "userID,username,password,phoneNumber,address,balance,userState" << std::endl;
    for(int i = 0; i < this->idx; i++) {
        if(userInfoList[i] != nullptr) {
            fout << userInfoList[i]->userID << ",";
            fout << userInfoList[i]->username << ",";
            fout << userInfoList[i]->password << ",";
            fout << userInfoList[i]->phonenumber << ",";
            fout <<  userInfoList[i]->address << ",";
            fout << std::setiosflags(std::ios::fixed) << std::setprecision(1) << userInfoList[i]->balance << ",";
            fout << userInfoList[i]->userState << std::endl;
            delete userInfoList[i];
        }
    }
    fout.close();
}

void LoginScene::loadUserInfo() {
    std::fstream fin("../res/userInfo.txt", std::ios::in); //open
    if (!fin) {
        printf("file not exists!\n");
        std::fstream fout;
        fout.open("../res/userInfo.txt", std::ios::out);
        std::string head = "userID,username,password,phoneNumber,address,balance,userState";
        fout << head << std::endl;
        fout.close();
    }
    fin.close();
    fin.open("../res/userInfo.txt", std::ios::in);
    std::string buffer;
    fin >> buffer; // 先去掉标题行
    while(!fin.eof()) { //读取
        buffer.clear();
        fin >>  buffer;
        if(buffer.empty()){
            //说明是因为换行符导致进入到这一行
            break;
        }
        if(this->idx >= USERCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->userInfoList[this->idx++] = this->createUser(buffer);
//            std::cout << this->userInfoList[this->idx-1]->username << this->userInfoList[this->idx-1]->password << std::endl;
        }
    }
    fin.close();
}


void LoginScene::selectOpt() {
    int ans;
    bool isValid = false; // 退出标志
    while(!isValid) {
//        system("cls");
        printf("------------------------------------------------------------\n");
        printf("*****************************LOGIN**************************\n");
        printf("------------------------------------------------------------\n");
        printf("1. UserLogin 2. UserRegister 3. AdminLogin 4. exit\n");
        printf("type a number to continue: ");
        scanf("%d", &ans);
        switch (ans) {
            case 1:
                this->userLogin();
                break;
            case 2:
                this->userRegister();
                break;
            case 3:
                this->adminLogin();
                break;
            case 4: // exit
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                break;
        }
    }
}

void LoginScene::userLogin() {
//    system("cls");
    bool isValid = false;
    int falseCnt = 0; //记录错误输入用户名/密码的次数, 达到3次自动退出登录.
    while(!isValid) {
        printf("------------------------------------------------------------\n");
        printf("************************USER LOGIN**************************\n");
        printf("------------------------------------------------------------\n");
        printf("username: ");
        std::string usernameBuffer;
        std::cin >> usernameBuffer;
        printf("password: ");
        std::string passwordBuffer;
        std::cin >> passwordBuffer;
        this->curUser = this->userLoginCheck(usernameBuffer, passwordBuffer);
        if(this->curUser != nullptr) {
            printf("success!\n");
            isValid = true;
        }
        else {
            if (++falseCnt == 3) {
                printf("you've typed wrong username/password 3 times! going to return....\n");
                break;
            }
            printf("permission denied the %d time! type again\n", falseCnt);
        }
    }
    if(falseCnt >= 3 && !isValid) return ;
    //登录成功, 登录用户界面
    this->selectUserOpt();
}

void LoginScene::userRegister() {
//    system("cls");
    bool isValid = false;
    while(!isValid) {
        printf("------------------------------------------------------------\n");
        printf("************************USER Register***********************\n");
        printf("------------------------------------------------------------\n");
        // buffer
        std::string _username;
        std::string _password;
        std::string _phoneNumber;
        std::string _address;
        printf("username: ");
        std::cin >> _username;
        printf("password: ");
        std::cin >> _password;
        printf("phoneNumber: ");
        std::cin >> _phoneNumber;
        printf("address: ");
        std::cin >> _address;
        std::string _userID = this->userRegisterCheck(_username);
        if(!_userID.empty()) {
            isValid = true;
            userInfo *cur = new userInfo;
            cur->username = _username;
            cur->password = _password;
            cur->userID = _userID;
            cur->userState = "active";
            cur->address = _address;
            cur->balance = 0.0;
            cur->phonenumber = _phoneNumber;
            //将创建的userInfo添加到userInfoList;
            if(this->idx >= USERCAPACITY) {
                printf("error! out of capacity! going to return...\n");
                break;
            }
            else {
                printf("success!\n");
                this->userInfoList[this->idx++] = cur;
            }
        }
        else {
            printf("error! username already used! try another name!\n");
        }
    }
}

void LoginScene::adminLogin() {
//    system("cls");
    bool isValid = false;
    int falseCnt = 0;
    while(!isValid) {
        printf("------------------------------------------------------------\n");
        printf("**************************Admin Login***********************\n");
        printf("------------------------------------------------------------\n");
        std::string _adminID;
        std::string _password;
        printf("adminID: ");
        std::cin >> _adminID;
        printf("password: ");
        std::cin >> _password;
        if(_adminID == "admin" && _password == "root") {
            isValid = true;
            printf("success!\n");
        }
        else {
            if(++falseCnt == 3) {
                printf("you've tried 3 times wrong answer! going to return...\n");
                break;
            }
            printf("permission denied! the %d time!\n", falseCnt);
        }
    }
    if(isValid) {//进入admin界面
        printf("going to the admin scene!\n");
    }
    return;
}

void LoginScene::selectUserOpt() {//1. 我是卖家 2. 我是买家 3. 个人中心 4. 返回
    //    system("cls");
    int ans;
    bool isValid = false;
    AccountCenter a;
    SellerCenter s(this->curUser);
    a.init(this, this->curUser);
    while(!isValid) {
        printf("------------------------------------------------------------\n");
        printf("****************************User Menu***********************\n");
        printf("------------------------------------------------------------\n");
        printf("Welcome, ");
        std::cout << this->curUser->username << std::endl;
        printf("1. Seller Center 2. Buyer Center 3. Account Center 4. exit\n");
        printf("select a num: ");
        scanf("%d", &ans);
        switch (ans) {
            case 1:
                printf("going to the Seller Center...\n");
                //调用卖家模块
                s.selectOpt();
                break;
            case 2:
                printf("going to the Buyer Center...\n");
                //调用买家模块
                break;
            case 3:
                printf("going to the Account Center...\n");
                a.selectOpt();
                //调用个人中心模块
                break;
            case 4://return
                this->curUser = nullptr;// 清空当前用户指针
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                break;
        }
    }
}

userInfo* LoginScene::createUser(std::string &buffer) {
    if(buffer.empty()) {
        printf("error! no input!\n");
        return nullptr;
    }
    //create a new userInfo struct
    userInfo * cur = new userInfo;
    //split
    int l = 0, r = 0;//双指针
    //userID,
    while(buffer[++r] != ',') {}
    cur->userID = buffer.substr(l, r-l);
    l = r+1;
    //username,
    while(buffer[++r] != ',') {}
    cur->username = buffer.substr(l, r-l);
    l = r+1;
    //password,
    while(buffer[++r] != ',') {}
    cur->password = buffer.substr(l, r-l);
    l = r+1;
    //phonenumber,
    while(buffer[++r] != ',') {}
    cur->phonenumber = buffer.substr(l, r-l);
    l= r+1;
    //address,
    while(buffer[++r] != ',') {}
    cur->address = buffer.substr(l, r-l);
    l = r+1;
    //balance,
    while(buffer[++r] != ',') {}
    cur->balance = atof(buffer.substr(l, r-l).c_str());
    l = r+1;
    //userState
    cur->userState = buffer.substr(l, buffer.length() - l);
    return cur;
}

userInfo* LoginScene::userLoginCheck(const std::string& username, const std::string& password) {
    for(int i = 0; i < this->idx; i++) {
        if(username == this->userInfoList[i]->username && password == this->userInfoList[i]->password) {
            return this->userInfoList[i];
        }
    }
    return nullptr;
}

std::string LoginScene::userRegisterCheck(const std::string& username) {
    std::string ret;
    for(int i = 0; i < this->idx; i++) {
        if(username == this->userInfoList[i]->username) {
            return ret;
        }
    }
    //说明不重复, 指派一个userID
    std::string num = std::to_string(this->idx+1);
    if(num.length() == 1) {
        ret += "U00";
    }
    else if(num.length() == 2) {
        ret += "U0";
    }
    else {
        ret += "U";
    }
    ret += num;
    return ret;
}
