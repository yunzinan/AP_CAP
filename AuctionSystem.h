//
// Created by Jack_shen on 2022/9/12.
//

#ifndef CAP_AUCTIONSYSTEM_H
#define CAP_AUCTIONSYSTEM_H

#include <cstdio>
#include <string>
#include "MyNode.h"

#define COMMODITYCAPACITY 20

typedef struct commodityInfo{
   std::string commodityID;
   std::string sellerID;
   std::string commodityName;
   std::string description;
   std::string addedDate; // yyyy-mm-dd
   std::string state; // onAuction, removed
   float floorPrice; // 底价
   int number;
}commodityInfo;

typedef struct auctionInfo{
    std::string commodityID;
    float floorPrice;
    std::string sellerID;
    MyNode myNode; // buyerID bidPrice bidTime
}auctionInfo;

class AuctionSystem {
    commodityInfo *commodityInfoList[COMMODITYCAPACITY];
    auctionInfo *auctionInfoList[COMMODITYCAPACITY];
    int commodityIdx = 0;
    int auctionIdx = 0;
public:
    AuctionSystem();
    void loadCommodityInfo();//初始化, 将commodityInfo.txt信息写入
    commodityInfo *createCommodity(std::string &buffer); //根据string信息创建商品对象(初始化
    void addCommodity(commodityInfo *_commodityInfo);//添加新的商品
    std::string addCommodityCheck(std::string commodityName); // 主要是创造commodityID返回, 因为不同商家可以起相同的名字.
    commodityInfo * findCommodity(std::string _commodityID); // 买家功能: 根据商品ID查找对应的商品指针
    commodityInfo * findCommodity(std::string _commodityID, std::string _sellerID); //卖家功能: 查找某个用户的商家商品
    void showCommodityList(std::string _sellerID);// 卖家功能: 只展示属于卖家的商品
    void showCommodityList(); //买家功能, 展示所有在售的商品
    ~AuctionSystem();
};


#endif //CAP_AUCTIONSYSTEM_H
