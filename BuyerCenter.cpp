//
// Created by Jack_shen on 2022/9/12.
//

#include <iostream>
#include <cstdio>
#include <iomanip>
#include "BuyerCenter.h"

BuyerCenter::BuyerCenter(userInfo *_curUser, AuctionSystem *_system) {
    this->curUser = _curUser;
    this->auctionSystem = _system;
}

BuyerCenter::~BuyerCenter() {
//    delete this->auctionSystem;
}

void BuyerCenter::selectOpt() {
    int ans;
    bool isValid = false;
    while(!isValid) {
        //        system("cls");
        printf("------------------------------------------------------------\n");
        printf("**************************Seller Center*********************\n");
        printf("------------------------------------------------------------\n");
        printf("1. View CommodityList 2. Search Commodity\n"
               "3. View DetailedCommodity 4. Bid Commodity\n"
               "5. View Order List 6. Exit\n");
        printf("type a number to continue: ");
        scanf("%d", &ans);
        switch (ans) {
            case 1:
                this->viewCommodityList();
                break;
            case 2:
                this->searchCommodity();
                break;
            case 3:
                this->viewDetailedCommodity();
                break;
            case 4:
                this->bidCommodity();
                break;
            case 5:
                this->viewOrderList();
                break;
            case 6: // exit
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                break;
        }
    }
}

void BuyerCenter::viewCommodityList() {
    this->auctionSystem->showCommodityList();
}

void BuyerCenter::searchCommodity() {
    std::string _commodityName;
    printf("please type in the commodityName you want to search: ");
    std::cin >> _commodityName;
    this->auctionSystem->searchCommodity(_commodityName);
}

void BuyerCenter::viewDetailedCommodity() {
    std::string _commodityID;
    printf("please type in the commodityID you want to view: ");
    std::cin >> _commodityID;
    commodityInfo *response = this->auctionSystem->findCommodity(_commodityID);
    if(response == nullptr) {
        printf("error! commodity not find!\n");
        return;
    }
    printf("************************************************************\n");
    std::cout << "commodityID: " << response->commodityID << std::endl
              << "commodityName: " << response->commodityName << std::endl
              << "floorPrice: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << response->floorPrice << std::endl
              << "number: " << response->number << std::endl
              << "description: " << response->description << std::endl;
    printf("************************************************************\n");
}

void BuyerCenter::bidCommodity() {
    printf("please type in the commodityID you want to bid: ");
    std::string _commodityID;
    std::cin >> _commodityID;
    commodityInfo * response = this->auctionSystem->findCommodity(_commodityID);
    if(response == nullptr) {
        printf("failed! commodity not find!\n");
        return ;
    }
    printf("************************************************************\n");
    std::cout << "commodityID: " << response->commodityID << std::endl
              << "commodityName: " << response->commodityName << std::endl
              << "floorPrice: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << response->floorPrice << std::endl
              << "number: " << response->number << std::endl
              << "description: " << response->description << std::endl;
    printf("************************************************************\n");
    printf("do you want to bid ?(y/n): ");
    char input;
    std::cin >> input;
    while(input != 'y' && input != 'n') {
        printf("wrong input! type again!\n");
        scanf("%c", &input);
    }
    if(input == 'n') {
        printf("bid cancelled!\n");
        return ;
    }
    printf("please type in your bid price: ");
    float _bidPrice;
    std::cin >> _bidPrice;
    if(_bidPrice < response->floorPrice) {
        printf("failed! your bid price is below the floorPrice!\n");
        return ;
    }
    if(!this->auctionSystem->bidCheck(this->curUser->userID, _commodityID)) {
        printf("failed! you've already bid once for this commodity!\n");
        return ;
    }
    if(this->curUser->balance < _bidPrice) {
        printf("failed! you don't have enough money!\n");
        return ;
    }
    printf("bid success!\n");
    //生成订单
    this->auctionSystem->addOrder(response->commodityID, response->sellerID, this->curUser->userID, _bidPrice);
    //买家扣款
    this->curUser->balance -= _bidPrice;
}

void BuyerCenter::viewOrderList() {
    this->auctionSystem->viewOrderList(this->curUser->userID);
}




