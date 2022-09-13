//
// Created by Jack_shen on 2022/9/12.
//
#include <iostream>
#include <iomanip>
#include "AccountCenter.h"


void AccountCenter::selectOpt() {
    int ans;
    bool isValid = false;
    while(!isValid) {
        //        system("cls");
        printf("------------------------------------------------------------\n");
        printf("************************Account Center**********************\n");
        printf("------------------------------------------------------------\n");
        printf("1. View UserInfo 2. Modify UserInfo 3. Recharge 4. exit\n");
        printf("type a number to continue: ");
        scanf("%d", &ans);
        switch (ans) {
            case 1:
                this->viewUserInfo();
                break;
            case 2:
                this->modifyUserInfo();
                break;
            case 3:
                this->recharge();
                break;
            case 4:
                isValid = true;
                break;
            default:
                printf("error! type again!...\n");
                break;
        }
    }
}

//AccountCenter::AccountCenter(LoginScene *_parent, userInfo *_curUser)
//{
//    this->curUser = _curUser;
//    this->parent = _parent;
//    this->selectOpt();
//}

void AccountCenter::viewUserInfo() {
    printf("************************************************************\n");
    std::cout << "userID: " << this->curUser->userID << std::endl;
    std::cout << "username: " << this->curUser->username << std::endl;
    std::cout << "password: " << this->curUser->password << std::endl;
    std::cout << "phoneNumber: " << this->curUser->phonenumber << std::endl;
    std::cout << "address: " << this->curUser->address << std::endl;
    std::cout << "balance: " <<  std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->curUser->balance << std::endl;
    std::cout << "userState: " << this->curUser->userState << std::endl;
    printf("************************************************************\n");
}

void AccountCenter::modifyUserInfo() {
    printf("1. username 2. password 3. phoneNumber 4. address\n");
    printf("please type in the index of the property you want to modify: ");
    int ans;
    std::string _username;
    std::string response;
    std::string _password;
    std::string _phoneNumber;
    std::string _address;
    scanf("%d", &ans);
    switch (ans) {
        case 1:
            std::cout << "your current username:" << this->curUser->username << std::endl;
            printf("new username: ");
            std::cin >> _username;
            response = parent->userRegisterCheck(_username);
            if(response.empty()) {
                printf("failed! username already used! try another name!\n");
            }
            else {
                printf("modification success!\n");
                this->curUser->username = _username;
                std::cout << "now your current username:" << this->curUser->username << std::endl;
            }
            break;

        case 2:
            std::cout << "your current password:" << this->curUser->password << std::endl;
            printf("new password: ");
            std::cin >> _password;
            this->curUser->password = _password;
            std::cout << "now your current password:" << this->curUser->password << std::endl;
            break;
        case 3:
            std::cout << "your current phoneNumber:" << this->curUser->phonenumber << std::endl;
            printf("new phoneNumber: ");
            std::cin >> _phoneNumber;
            this->curUser->phonenumber = _phoneNumber;
            std::cout << "now your current phoneNumber:" << this->curUser->phonenumber << std::endl;
            break;
        case 4:
            std::cout << "your current address:" << this->curUser->address << std::endl;
            printf("new address: ");
            std::cin >> _address;
            this->curUser->address = _address;
            std::cout << "now your current address:" << this->curUser->address << std::endl;
            break;
        default:
            printf("error! type again!\n");
    }
}

void AccountCenter::recharge() {
    std::cout << "your current account balance: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->curUser->balance << std::endl;
    float inc = 0.0;
    printf("recharge amount: ");
    scanf("%f", &inc);
    this->curUser->balance += inc;
    std::cout << "now your current account balance: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->curUser->balance << std::endl;
}

void AccountCenter::init(LoginScene *_parent, userInfo *_userInfo) {
    this->curUser = _userInfo;
    this->parent = _parent;
}
