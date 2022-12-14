#include "myvector.h"

void MyVector::ini(commodityInfo *_commodity, userInfo *_seller) {
    this->commodity = _commodity;
    this->seller = _seller;
    this->num = this->commodity->number;
}

void MyVector::addNode(orderInfo *_order, userInfo *_buyer) {
    orderList[this->idx].order = _order;
    orderList[this->idx].buyer = _buyer;
    this->idx++;
}

void MyVector::swap(int i, int j) {
    orderNode tmp = orderList[i];
    orderList[i] = orderList[j];
    orderList[j] = tmp;
}

void MyVector::rank() {//按照node.orderInfo->bidPrice, bidTime排序, BubbleSort
    for(int i = this->idx-1; i >=0; i--) {//降序
        for(int j = 0; j < i; j++) {
            if(orderList[j].order->bidPrice < orderList[j+1].order->bidPrice) swap(j, j+1);
            else if(orderList[j].order->bidPrice == orderList[j+1].order->bidPrice) {
                if(!timeLess(orderList[j].order->bidTime, orderList[j+1].order->bidTime)) swap(j, j+1);
            }
        }
    }
}

bool MyVector::timeLess(QString time1, QString time2) {//如果time1 < time2 return true;
    //split
    int y1 = time1.mid(0, 4).toInt();
    int y2 = time2.mid(0, 4).toInt();
    int m1 = time1.mid(5, 2).toInt();
    int m2 = time2.mid(5, 2).toInt();
    int d1 = time1.mid(8, 2).toInt();
    int d2 = time2.mid(8, 2).toInt();
    int h1 = time1.mid(11, 2).toInt();
    int h2 = time2.mid(11, 2).toInt();
    int M1 = time1.mid(14, 2).toInt();
    int M2 = time2.mid(14, 2).toInt();
    int s1 = time1.mid(17, 2).toInt();
    int s2 = time2.mid(17, 2).toInt();
    if(y1 != y2) return y1 < y2;
    if(m1 != m2) return m1 < m2;
    if(d1 != d2) return d1 < d2;
    if(h1 != h2) return h1 < h2;
    if(M1 != M2) return M1 < M2;
    if(s1 != s2) return s1 < s2;
    return true;
}

bool MyVector::empty() {
    if(this->idx == 0) return true;
    else return false;
}

void MyVector::update() {
    //确定success / fail
    if(this->num >= this->idx ) {
        for(int i = 0; i < idx; i++) {
            orderList[i].order->state = "succeeded";
        }
    }
    else {
        for(int i = 0; i < num; i++) {
            orderList[i].order->state = "succeeded";
        }
        for(int i = num; i < idx; i++) {
            orderList[i].order->state = "failed";
        }
    }
    //处理后事
    for(int i = 0; i < idx; i++) {
        if(orderList[i].order->state == "succeeded") {
            // 卖家得款
            this->seller->balance += orderList[i].order->bidPrice;
            // 商品减少
            this->commodity->number--;
            if(this->commodity->number == 0) this->commodity->state = "removed";
        }
        else {
            // 买家还款
            orderList[i].buyer->balance += orderList[i].order->bidPrice;
        }
    }
}

void MyVector::clear() {
    idx = 0;
}
