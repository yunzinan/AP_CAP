#ifndef CONFIG_H
#define CONFIG_H

#include <cstdio>
#include <string>
#include <QDebug>
#define USERCAPACITY 20


typedef struct commodityInfo{
    QString commodityID;
    QString sellerID;
    QString commodityName;
    QString description;
    QString addedDate; // yyyy-mm-dd
    QString state; // onAuction, removed
    float floorPrice; // 底价
    int number;
}commodityInfo;

typedef struct orderInfo{
    QString orderID;
    QString commodityID;
    QString sellerID;
    QString buyerID;
    QString bidTime; //yyyy-mm-dd-hh-mm-ss
    float bidPrice;
    QString state; // succeeded, failed, inProcess, cancelled
}orderInfo;

typedef struct userInfo

{
    QString userID; // U001
    QString username; // no more than 10
    QString password; // no more than 20
    QString phonenumber; // no more than 40, numbers only
    QString address; // no more than 40,
    float balance; // set precision 1
    QString userState; // activate, inactivate
}userInfo;

#define COMMODITYCAPACITY 20
#define ORDERCAPACITY 50

typedef struct myTimer{
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
}myTimer;

typedef struct orderNode{
    userInfo * buyer;
    orderInfo * order;
}orderNode;

typedef struct commodityList{
    commodityInfo *list[COMMODITYCAPACITY];
    int size;
}commodityList;

typedef struct orderList{
    orderInfo* list[ORDERCAPACITY];
    int size;
}orderList;

typedef struct userList{
    userInfo* list[USERCAPACITY];
    int size;
}userList;

#endif // CONFIG_H

