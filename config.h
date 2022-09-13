//
// Created by Jack_shen on 2022/9/13.
//

#ifndef CAP_CONFIG_H
#define CAP_CONFIG_H

#include <cstdio>
#include <string>

#define USERCAPACITY 20


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

typedef struct userInfo

{
    std::string userID; // U001
    std::string username; // no more than 10
    std::string password; // no more than 20
    std::string phonenumber; // no more than 40, numbers only
    std::string address; // no more than 40,
    float balance; // set precision 1
    std::string userState; // activate, inactivate
}userInfo;

#endif //CAP_CONFIG_H
