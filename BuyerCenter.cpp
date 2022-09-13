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
    delete this->auctionSystem;
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
               " 3. View DetailedCommodity 4. Bid Commodity\n"
               " 5. View Order List 6. Exit\n");
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
//                this->bidCommodity();
                break;
            case 5:
//                this->viewOrderList();
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




