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
        printf("file not exists!\n");
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
    this->loadCommodityInfo();
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
    // 释放内存, 写入文件
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


