//
// Created by Jack_shen on 2022/9/12.
// 自建的链表数据结构,  用于存放竞拍信息

#ifndef CAP_MYNODE_H
#define CAP_MYNODE_H

#include <cstdio>
#include <string>

typedef struct node{
    std::string buyerID;
    std::string bidTime; // yy-mm-dd-hh-mm
    std::string bidPrice;
    node *next;
}node;

class MyNode {
    node *head = nullptr;
    int size = 0;
public:
    void append(std::string _buyerID, std::string _bidTime, std::string _bidPrice) {
        if(head == nullptr) {// 第一次加入
            head = new node;
            this->size++;
            head->buyerID = _buyerID;
            head->bidPrice = _bidPrice;
            head->bidTime = _bidTime;
            head->next = nullptr;
            return ;
        }
        //除了第一次, 后面都不能修改head的值
        node *cur = head;
        while(cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = new node;
        cur = cur->next;
        this->size++;
        cur->buyerID = _buyerID;
        cur->bidPrice = _bidPrice;
        cur->bidTime = _bidTime;
        cur->next = nullptr;
    }
    node* findNode(std::string _buyerID) { //按买家查找, 返回nullptr就说明不存在
        node *cur = head;
        if(cur == nullptr) {
            return nullptr;
        }
        while(cur != nullptr) {
            if(cur->buyerID == _buyerID) return cur;
            else cur = cur->next;
        }
        return cur;
    }
    ~MyNode(){
        //释放变量
        node *cur = head;
        while(cur != nullptr) {
            node *tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }
};


#endif //CAP_MYNODE_H
