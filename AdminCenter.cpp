//
// Created by Jack_shen on 2022/9/13.
//

#include "AdminCenter.h"
#include <iomanip>
#include <iostream>
#include <fstream>

AdminCenter::AdminCenter(userInfo *_userInfoList[USERCAPACITY], int _idx) {
    this->auctionSystem = new AuctionSystem;
    this->userInfoList = _userInfoList;
    this->userIdx = _idx;
    //this->loadUserInfo();
}

void AdminCenter::selectOpt() {
    int ans;
    bool isValid = false;
    while(!isValid) {
        //        system("cls");
        printf("------------------------------------------------------------\n");
        printf("***************************Admin Center*********************\n");
        printf("------------------------------------------------------------\n");
        printf("1. View CommodityList 2. Search Commodity\n"
                    "3. Cancel Commodity 4. View OrderList\n"
                    "5. View UserList 6. Ban User\n"
                    "7. End Auction 8. Exit\n");
        printf("type a number to continue: ");
        std::cin >> ans;
        switch (ans) {
            case 1:
                this->viewCommodityList();
                break;
            case 2:
                this->searchCommodity();
                break;
            case 3:
                this->cancelCommodity();
                break;
            case 4:
                this->viewOrderList();
                break;
            case 5:
                this->viewUserList();
                break;
            case 6:
                this->banUser();
                break;
            case 7:
                this->endAuction();
                break;
            case 8: // exit
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                std::cin >> ans;
                break;
        }
    }
}

AdminCenter::~AdminCenter() {
    delete this->auctionSystem;
//    // 写文件
//    std::fstream fout;
//    fout.open("../res/userInfo.txt", std::ios::out | std::ios::trunc);//覆盖写入
//    // 释放内存, 写入文件
//    fout << "userID,username,password,phoneNumber,address,balance,userState" << std::endl;
//    for(int i = 0; i < this->userIdx; i++) {
//        if(userInfoList[i] != nullptr) {
//            fout << userInfoList[i]->userID << ",";
//            fout << userInfoList[i]->username << ",";
//            fout << userInfoList[i]->password << ",";
//            fout << userInfoList[i]->phonenumber << ",";
//            fout <<  userInfoList[i]->address << ",";
//            fout << std::setiosflags(std::ios::fixed) << std::setprecision(1) << userInfoList[i]->balance << ",";
//            fout << userInfoList[i]->userState << std::endl;
//            delete userInfoList[i];
//        }
//    }
//    fout.close();
}

void AdminCenter::loadUserInfo() {
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
        if(this->userIdx >= USERCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->userInfoList[this->userIdx++] = this->createUser(buffer);
//            std::cout << this->userInfoList[this->idx-1]->username << this->userInfoList[this->idx-1]->password << std::endl;
        }
    }
    fin.close();
}

userInfo* AdminCenter::createUser(std::string &buffer) {
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

void AdminCenter::viewUserList() {
    printf("------------------------------------------------------------\n");
    printf("****************************User List***********************\n");
    printf("------------------------------------------------------------\n");
    printf("userID username password balance userState\n");
    for(int i = 0; i < this->userIdx; i++) {
        std::cout << this->userInfoList[i]->userID << " "
                << this->userInfoList[i]->username << " "
                << this->userInfoList[i]->password << " "
                << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->userInfoList[i]->balance << " "
                << this->userInfoList[i]->userState << std::endl;
    }
}

void AdminCenter::viewCommodityList() {
    this->auctionSystem->showCommodityListAll();
}

void AdminCenter::viewOrderList() {
    this->auctionSystem->viewOrderList();
}

void AdminCenter::searchCommodity() {
    printf("please type in the commodityName you want to search: ");
    std::string _commodityName;
    std::cin >> _commodityName;
    this->auctionSystem->searchCommodity(_commodityName);
}

void AdminCenter::cancelCommodity() {
    printf("type in the commodityID you want to cancel: ");
    std::string _commodityID;
    std::cin >> _commodityID;
    //find
    commodityInfo *response = this->auctionSystem->findCommodity(_commodityID);
    if(response == nullptr) {
        printf("failed! commodity not find!\n");
        return ;
    }
    printf("************************************************************\n");
    std::cout << "commodityID: " << response->commodityID << std::endl
              << "commodityName: " << response->commodityName << std::endl
              << "floorPrice: " << response->floorPrice << std::endl
              << "number: " << response->number << std::endl
              << "description: " << response->description << std::endl;
    printf("************************************************************\n");
    printf("1. cancelCommodity 2. re-releaseCommodity\n");
    printf("select a number: ");
    int ans;
    scanf("%d", &ans);
    if(ans == 1) {
        if(response->state == "onAuction") {
            response->state = "removed";
            printf("success!\n");
        }
        else printf("failed! already removed!\n");
    }
    else if(ans == 2) {
        if(response->state == "removed") {
            response->state = "onAuction";
            printf("success!\n");
        }
        else printf("failed! already onAuction!\n");
    }
    else {
        printf("failed! wrong input!\n");
    }
}

void AdminCenter::banUser() {
    std::string _userID;
    printf("please type in the userID you want to ban: ");
    std::cin >> _userID;
    userInfo * cur = nullptr;
    //find
    for(int i = 0; i < this->userIdx; i++) {
        if(this->userInfoList[i]->userID == _userID) {
            cur = this->userInfoList[i];
        }
    }
    if(cur == nullptr) {
        printf("error! user not find!\n");
        return ;
    }
    printf("are you sure to ban this user?(y/n)\n");
    std::string ans;
    std::cin >> ans;
    while(ans != "y" && ans != "n") {
        printf("error! type again!\n");
        std::cin >> ans;
    }
    if(ans == "n") {
        return ;
    }
    if(cur->userState == "removed") {
        printf("error! user already banned!\n");
    }
    else {
        cur->userState = "inactive";
        printf("success!\n");
    }
}

void AdminCenter::endAuction() {
    printf("are you sure to end auction? (y/n)\n");
    std::string ans;
    std::cin >> ans;
    while(ans != "y" && ans != "n") {
        printf("error! type again!\n");
        std::cin >> ans;
    }
    if(ans == "n") return ; // ensure command
    this->auctionSystem->setUserInfo(this->userInfoList, this->userIdx);
    this->auctionSystem->calcResult();
    //筛选所有状态为inProcess的订单
    //按照commodityID进行分类
    //获取该商品的库存, 若充足, 则全部success
    //否则对订单的bidPrice和bidTime进行排序, 选择前number名succeeded, others failed
    //succeeded: 1. seller.balance++ 2. commodity.number--(0->removed) 3. order.state = "succeeded"
    //failed: 1. buyer.balance++ 2. order.state = "failed"
}



