//
// Created by Jack_shen on 2022/9/12.
//

#ifndef CAP_AUCTIONSYSTEM_H
#define CAP_AUCTIONSYSTEM_H

#include <cstdio>
#include <string>
#include <ctime>

#define COMMODITYCAPACITY 20
#define ORDERCAPACITY 50

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

typedef struct orderInfo{
    std::string orderID;
    std::string commodityID;
    std::string sellerID;
    std::string buyerID;
    std::string bidTime; //yyyy-mm-dd-hh-mm-ss
    float bidPrice;
    std::string state; // succeeded, failed, inProcess, cancelled
}orderInfo;

typedef struct myTimer{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}myTimer;

class AuctionSystem {
    commodityInfo *commodityInfoList[COMMODITYCAPACITY];
    orderInfo *orderInfoList[ORDERCAPACITY];
    int commodityIdx = 0;
    int orderIdx = 0;
    tm *ltm;
    myTimer *_myTimer;
public:
    AuctionSystem();
    void loadCommodityInfo();//初始化, 将commodityInfo.txt信息写入
    void loadOrderInfo();
    commodityInfo *createCommodity(std::string &buffer); //根据string信息创建商品对象(初始化
    orderInfo *createOrder(std::string &buffer);
    void addCommodity(commodityInfo *_commodityInfo);//添加新的商品
    void addOrder(std::string commodityID, std::string sellerID, std::string buyerID, float bidPrice);
    std::string addCommodityCheck(std::string commodityName); // 主要是创造commodityID返回, 因为不同商家可以起相同的名字.
    commodityInfo * findCommodity(std::string _commodityID); // 买家功能: 根据商品ID查找对应的商品指针
    commodityInfo * findCommodity(std::string _commodityID, std::string _sellerID); //卖家功能: 查找某个用户的商家商品
    void searchCommodity(std::string _commodityName); //买家功能: 完全匹配, 理论上讲应该要传值回去而不是在这里显示的.
    void showCommodityList(std::string _sellerID);// 卖家功能: 只展示属于卖家的商品
    void showCommodityList(); //买家功能, 展示所有在售的商品
    ~AuctionSystem();
    bool bidCheck(std::string _buyerID, std::string _commodityID); //检查这个买家是否之前已经有状态为"inProcess"的订单
    std::string generateTime(); //返回yyyy-mm-dd-hh:mm:ss的字符串
    void viewOrderList(std::string buyerID); //买家功能, 查看属于该买家的订单
    void viewOrderList_S(std::string sellerID); //卖家功能, 查看属于该卖家的订单
};


#endif //CAP_AUCTIONSYSTEM_H
