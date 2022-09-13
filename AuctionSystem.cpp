//
// Created by Jack_shen on 2022/9/12.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include "AuctionSystem.h"


void AuctionSystem::loadCommodityInfo() {
    //写文件
    std::fstream fin;
    fin.open("../res/commodityInfo.txt", std::ios::in);
    if(!fin) {
        printf("commodityInfo file not exists!\n");
        std::fstream fout;
        fout.open("../res/commodityInfo.txt", std::ios::out);
        std::string head = "commodityID,commodityName,floorPrice,number,description,sellerID,addedDate,state";
        fout << head << std::endl;
        fout.close();
    }
    fin.close();
    fin.open("../res/commodityInfo.txt", std::ios::in);
    std::string buffer;
    fin >> buffer; //先去掉标题行
    while(!fin.eof()) {
        buffer.clear();
        fin >> buffer;
        if(buffer.empty()) {
            break;
        }
        if(this->commodityIdx >= COMMODITYCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->commodityInfoList[this->commodityIdx++] = this->createCommodity(buffer);
        }
    }
    fin.close();
}

AuctionSystem::AuctionSystem() {
    //获取当前时间
    time_t now = time(0);
    this->ltm = localtime(&now);
    this->_myTimer = new myTimer;
    _myTimer->year = 1900 + ltm->tm_year;
    _myTimer->month = 1 + ltm->tm_mon;
    _myTimer->day = ltm->tm_mday;
    _myTimer->hour = ltm->tm_hour;
    _myTimer->min = ltm->tm_min;
    _myTimer->sec = ltm->tm_sec;
    this->loadCommodityInfo();
    this->loadOrderInfo();
}

commodityInfo *AuctionSystem::createCommodity(std::string &buffer) {
    if(buffer.empty()) {
        printf("error! no input!\n");
        return nullptr;
    }
    //create a new commodityInfo struct
    commodityInfo * cur = new commodityInfo;
    //split
    int l = 0, r = 0;
    //commodityID
    while(buffer[++r] != ',') {}
    cur->commodityID = buffer.substr(l, r-l);
    l = r+1;
    //commodityName
    while(buffer[++r] != ',') {}
    cur->commodityName = buffer.substr(l, r-l);
    l = r+1;
    //floorPrice
    while(buffer[++r] != ',') {}
    cur->floorPrice = atof(buffer.substr(l, r-l).c_str());
    l=r+1;
    //number
    while(buffer[++r] != ',') {}
    cur->number = atoi(buffer.substr(l, r-l).c_str());
    l = r+1;
    //description
    while(buffer[++r] != ',') {}
    cur->description = buffer.substr(l, r-l);
    l = r+1;
    //sellerID
    while(buffer[++r] != ',') {}
    cur->sellerID = buffer.substr(l, r-l);
    l = r+1;
    //addedDate
    while(buffer[++r] != ',') {}
    cur->addedDate = buffer.substr(l, r-l);
    l = r+1;
    //state
    cur->state = buffer.substr(l, buffer.length() - l);
    return cur;
}

AuctionSystem::~AuctionSystem() {
    //写文件
    std::fstream fout;
    fout.open("../res/commodityInfo.txt", std::ios::out | std::ios::trunc);
    // 释放内存, 写入文件: commodityInfo.txt
    fout << "commodityID,commodityName,floorPrice,number,description,sellerID,addedDate,state" << std::endl;
    for(int i = 0; i < this->commodityIdx; i++) {
        if(commodityInfoList[i] != nullptr) {
            fout << commodityInfoList[i]->commodityID << ",";
            fout << commodityInfoList[i]->commodityName << ",";
            fout << std::setiosflags(std::ios::fixed) << std::setprecision(1) << commodityInfoList[i]->floorPrice << ",";
            fout << commodityInfoList[i]->number << ",";
            fout << commodityInfoList[i]->description << ",";
            fout << commodityInfoList[i]->sellerID << ",";
            fout << commodityInfoList[i]->addedDate << ",";
            fout << commodityInfoList[i]->state << std::endl;
            delete commodityInfoList[i];
        }
    }
    fout.close();
    //释放内存, 写入文件: orderInfo.txt
    fout.open("../res/orderInfo.txt", std::ios::out | std::ios::trunc);
    fout << "orderID,commodityID,sellerID,buyerID,bidTime,bidPrice,state" << std::endl;
    for(int i = 0; i < this->orderIdx; i++) {
        fout << orderInfoList[i]->orderID << ",";
        fout << orderInfoList[i]->commodityID << ",";
        fout << orderInfoList[i]->sellerID << ",";
        fout << orderInfoList[i]->buyerID << ",";
        fout << orderInfoList[i]->bidTime << ",";
        fout << std::setiosflags(std::ios::fixed) << std::setprecision(1) << orderInfoList[i]->bidPrice << ",";
        fout << orderInfoList[i]->state << std::endl;
        delete orderInfoList[i];
    }
    fout.close();
}

void AuctionSystem::addCommodity(commodityInfo *_commodityInfo) {
    this->commodityInfoList[this->commodityIdx++] = _commodityInfo;
}

std::string AuctionSystem::addCommodityCheck(std::string commodityName) {
    std::string ret;
    std::string num = std::to_string(this->commodityIdx+1);
    if(num.length() == 1) {
        ret += "M00";
    }
    else if(num.length() == 2) {
        ret += "M0";
    }
    else {
        ret += "M";
    }
    ret += num;
    return ret;
}

void AuctionSystem::showCommodityList(std::string _sellerID) {
    printf("------------------------------------------------------------\n");
    printf("***********************Commodity List***********************\n");
    printf("------------------------------------------------------------\n");
    printf("ID Name FloorPrice Number AddedDate State\n");
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->sellerID == _sellerID) {
            std::cout << this->commodityInfoList[i]->commodityID << " "
                    << this->commodityInfoList[i]->commodityName << " "
                    << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->commodityInfoList[i]->floorPrice << " "
                    << this->commodityInfoList[i]->number << " "
                    << this->commodityInfoList[i]->addedDate << " "
                    << this->commodityInfoList[i]->state << std::endl;
        }
    }
}

void AuctionSystem::showCommodityList() {
    printf("------------------------------------------------------------\n");
    printf("***********************Commodity List***********************\n");
    printf("------------------------------------------------------------\n");
    printf("ID Name FloorPrice Number AddedDate State\n");
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->state == "onAuction") {
            std::cout << this->commodityInfoList[i]->commodityID << " "
                      << this->commodityInfoList[i]->commodityName << " "
                      << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->commodityInfoList[i]->floorPrice << " "
                      << this->commodityInfoList[i]->number << " "
                      << this->commodityInfoList[i]->addedDate << " "
                      << this->commodityInfoList[i]->state << std::endl;
        }
    }
}

commodityInfo *AuctionSystem::findCommodity(std::string _commodityID) {
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->commodityID == _commodityID) {
            return this->commodityInfoList[i];
        }
    }
    return nullptr;
}

commodityInfo *AuctionSystem::findCommodity(std::string _commodityID, std::string _sellerID) {
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->commodityID == _commodityID && this->commodityInfoList[i]->sellerID == _sellerID) {
            return this->commodityInfoList[i];
        }
    }
    return nullptr;
}

void AuctionSystem::searchCommodity(std::string _commodityName) {
    printf("------------------------------------------------------------\n");
    printf("************************Search Result***********************\n");
    printf("------------------------------------------------------------\n");
    printf("ID Name FloorPrice Number AddedDate State\n");
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->commodityName == _commodityName && this->commodityInfoList[i]->state == "onAuction") {
            std::cout << this->commodityInfoList[i]->commodityID << " "
                      << this->commodityInfoList[i]->commodityName << " "
                      << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->commodityInfoList[i]->floorPrice << " "
                      << this->commodityInfoList[i]->number << " "
                      << this->commodityInfoList[i]->addedDate << " "
                      << this->commodityInfoList[i]->state << std::endl;
        }
    }
}

void AuctionSystem::loadOrderInfo() {
    //写文件
    std::fstream fin;
    fin.open("../res/orderInfo.txt", std::ios::in);
    if(!fin) {
        printf("orderInfo file not exists!\n");
        std::fstream fout;
        fout.open("../res/orderInfo.txt", std::ios::out | std::ios::trunc);
        std::string head = "orderID,commodityID,sellerID,buyerID,bidTime,bidPrice,state";
        fout << head << std::endl;
        fout.close();
    }
    fin.close();
    fin.open("../res/orderInfo.txt", std::ios::in);
    std::string buffer;
    fin >> buffer;
    while(!fin.eof()) {
        buffer.clear();
        fin >> buffer;
        if(buffer.empty()) {
            break;
        }
        if(this->orderIdx >= ORDERCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->orderInfoList[this->orderIdx++] = this->createOrder(buffer);
        }
    }
}

orderInfo *AuctionSystem::createOrder(std::string &buffer) {
    if(buffer.empty()) {
        printf("error! no input!\n");
        return nullptr;
    }
    //create a new orderInfo struct
    orderInfo * cur = new orderInfo;
    //split
    int l = 0, r = 0;
    //orderID
    while(buffer[++r] != ',') {}
    cur->orderID = buffer.substr(l, r-l);
    l = r+1;
    //commodityID
    while(buffer[++r] != ',') {}
    cur->commodityID = buffer.substr(l, r-l);
    l = r+1;
    //sellerID
    while(buffer[++r] != ',') {}
    cur->sellerID = buffer.substr(l, r-l);
    l = r+1;
    //buyerID
    while(buffer[++r] != ',') {}
    cur->buyerID = buffer.substr(l, r-l);
    l = r+1;
    //bidTime
    while(buffer[++r] != ',') {}
    cur->bidTime = buffer.substr(l, r-l);
    l = r+1;
    //bidPrice
    while(buffer[++r] != ',') {}
    cur->bidPrice = atof(buffer.substr(l, r-l).c_str());
    l = r+1;
    //state
    cur->state = buffer.substr(l, buffer.length() - l);
    return cur;
}

bool AuctionSystem::bidCheck(std::string _buyerID, std::string _commodityID) {
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->buyerID == _buyerID && this->orderInfoList[i]->commodityID == _commodityID
            && this->orderInfoList[i]->state == "inProcess") {
            return false;
        }
    }
    return true;
}

void AuctionSystem::addOrder(std::string commodityID, std::string sellerID, std::string buyerID, float bidPrice) {
    //get orderID
    std::string orderID;
    std::string num = std::to_string(this->orderIdx+1);
    if(num.length() == 1) {
        orderID += "T00";
    }
    else if(num.length() == 2) {
        orderID += "T0";
    }
    else {
        orderID += "T";
    }
    orderID += num;
    orderInfo * cur = new orderInfo;
    cur->orderID = orderID;
    cur->commodityID = commodityID;
    cur->sellerID = sellerID;
    cur->buyerID = buyerID;
    cur->bidTime = generateTime();
    cur->bidPrice = bidPrice;
    cur->state = "inProcess";
    this->orderInfoList[this->orderIdx++] = cur;
}

std::string AuctionSystem::generateTime() {
    std::string timeStr;
    timeStr += std::to_string(this->_myTimer->year);

    timeStr += "-";

    if(this->_myTimer->month <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->month);

    timeStr += "-";

    if(this->_myTimer->day <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->day);

    timeStr += "-";

    if(this->_myTimer->hour <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->hour);

    timeStr += ":";

    if(this->_myTimer->min <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->min);

    timeStr += ":";

    if(this->_myTimer->sec <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->sec);
    return timeStr;
}

void AuctionSystem::viewOrderList(std::string buyerID) {
    printf("------------------------------------------------------------\n");
    printf("**************************Order List************************\n");
    printf("------------------------------------------------------------\n");
    printf("OrderID CommodityID SellerID BuyerID BidTime BidPrice State\n");
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->buyerID == buyerID) {
            std::cout << this->orderInfoList[i]->orderID << " "
                    << this->orderInfoList[i]->commodityID << " "
                    << this->orderInfoList[i]->sellerID << " "
                    << this->orderInfoList[i]->buyerID << " "
                    << this->orderInfoList[i]->bidTime << " "
                    << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->orderInfoList[i]->bidPrice << " "
                    << this->orderInfoList[i]->state << std::endl;
        }
    }
}

void AuctionSystem::viewOrderList_S(std::string sellerID) {
    printf("------------------------------------------------------------\n");
    printf("**************************Order List************************\n");
    printf("------------------------------------------------------------\n");
    printf("OrderID CommodityID SellerID BuyerID BidTime BidPrice State\n");
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->sellerID == sellerID) {
            std::cout << this->orderInfoList[i]->orderID << " "
                      << this->orderInfoList[i]->commodityID << " "
                      << this->orderInfoList[i]->sellerID << " "
                      << this->orderInfoList[i]->buyerID << " "
                      << this->orderInfoList[i]->bidTime << " "
                      << std::setiosflags(std::ios::fixed) << std::setprecision(1) << this->orderInfoList[i]->bidPrice << " "
                      << this->orderInfoList[i]->state << std::endl;
        }
    }
}



