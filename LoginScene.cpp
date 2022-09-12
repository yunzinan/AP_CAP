//
// Created by Jack_shen on 2022/9/12.
//

#include "LoginScene.h"
#include "LoginScene.h"

LoginScene::LoginScene() {
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