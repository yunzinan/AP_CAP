#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "config.h"
class MyVector
{
    commodityInfo * commodity;
    userInfo * seller;
    int num = 0; //commodity->number
    orderNode orderList[USERCAPACITY];
    int idx = 0;
public:
    void ini(commodityInfo *_commodity, userInfo *_seller);
    void addNode(orderInfo *_order, userInfo *_buyer);
    void swap(int i, int j);//比较两个竞拍者的优先度
    void rank();//给出最后的排名
    bool timeLess(QString time1, QString time2);
    void update();//确定succeeded和failed 处理后事
    bool empty();
    void clear();
};

#endif // MYVECTOR_H
