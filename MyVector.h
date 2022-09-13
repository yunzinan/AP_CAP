//
// Created by Jack_shen on 2022/9/13.
//

#ifndef CAP_MYVECTOR_H
#define CAP_MYVECTOR_H

#include "config.h"

//每一个vector只保存一个商品的所有信息

typedef struct orderNode{
    userInfo * buyer;
    orderInfo * order;
}orderNode;

class MyVector {
    commodityInfo * commodity;
    userInfo * seller;
    int num = 0; //commodity->number
    orderNode orderList[USERCAPACITY];
    int idx = 0;
public:
    void ini(commodityInfo *_commodity, userInfo *_seller);
    void addNode(orderInfo *_order, userInfo *_buyer);
    void swap(int i, int j);
    void rank();
    bool timeLess(std::string &time1, std::string &time2);
    void update();//确定succeeded和failed 处理后事
    bool empty();
    void clear();
};

#endif //CAP_MYVECTOR_H
