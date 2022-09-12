//
// Created by Jack_shen on 2022/9/12.
//
#include <iostream>
#include <fstream>
#include "LoginScene.h"
#include "LoginScene.h"

LoginScene::LoginScene() {
    this->loadUserInfo();
    printf("------------------------------------------------------------\n");
    printf("*****************************LOGIN**************************\n");
    printf("------------------------------------------------------------\n");
}

LoginScene::~LoginScene() {
    for(int i = 0; i < USERCAPACITY; i++) {
        if(userInfoList[i] != NULL) {
            delete userInfoList[i];
        }
    }
}

void LoginScene::loadUserInfo() {
    std::fstream fin("../res/userInfo.txt", std::ios::in);
    if (!fin) {
        printf("file not exists!\n");
        std::fstream fout;
        fout.open("../res/userInfo.txt", std::ios::out);
        std::string head = "userID,username,password,phoneNumber,address,balance,userState";
        fout << head << std::endl;
        fout.close();
    }
    std::string buffer;
    fin >> buffer; // 先去掉标题行
    while(!fin.eof()) {
        buffer.clear();
        fin >>  buffer;
        if(this->idx >= USERCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->userInfoList[this->idx++] = this->createUser(buffer);
//            std::cout << this->userInfoList[this->idx-1]->username << this->userInfoList[this->idx-1]->password << std::endl;
        }

    }
}


void LoginScene::selectOpt() {

}

void LoginScene::userLogin() {

}

void LoginScene::userRegister() {

}

void LoginScene::adminLogin() {

}

void LoginScene::selectUserOpt() {

}

userInfo* LoginScene::createUser(std::string &buffer) {
    if(buffer == "") {
        printf("error! no input!\n");
        return NULL;
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
