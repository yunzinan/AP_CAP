//
// Created by Jack_shen on 2022/9/12.
//

#include "SellerCenter.h"

SellerCenter::SellerCenter(userInfo *_curUser) {
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
    this->curUser = _curUser;
    //创建auctionSystem对象
    this->auctionSystem = new AuctionSystem;
//    this->selectOpt();
}

void SellerCenter::selectOpt() {
    int ans;
    bool isValid = false;
    while(!isValid) {
        //        system("cls");
        printf("------------------------------------------------------------\n");
        printf("*****************************LOGIN**************************\n");
        printf("------------------------------------------------------------\n");
        printf("1. Release Commodity 2. View Commodity List\n"
               " 3. Modify Commodity 4. Cancel Commodity 5. View Order List 6. Exit\n");
        printf("type a number to continue: ");
        scanf("%d", &ans);
        switch (ans) {
            case 1:
                this->releaseCommodity();
                break;
            case 2:
                this->viewCommodityList();
                break;
            case 3:
//                this->modifyCommodityInfo();
                break;
            case 4:
//                this->cancelCommodity();
                break;
            case 5:
                this->viewCommodityList();
                break;
            case 6: // exit
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                break;
        }
    }
}

SellerCenter::~SellerCenter() {
    delete this->auctionSystem;
}

void SellerCenter::releaseCommodity() {
    bool isValid = false;
    std::string _commodityName;
    std::string _commodityID;
    std::string _description;
    float _floorPrice;
    int _number;
    while(!isValid) {
        printf("commodityName: ");
        std::cin >> _commodityName;
        printf("floorPrice: ");
        std::cin >> _floorPrice;
        printf("number: ");
        std::cin >> _number;
        printf("description: ");
        std::cin >> _description;
        _commodityID = this->auctionSystem->addCommodityCheck(_commodityName);
        if(_commodityID.empty()) {//先保留着, 后面迟早要写check
            printf("error! type again\n");
        }
        else {
            isValid = true;
            printf("success!\n");
            commodityInfo *cur = new commodityInfo;
            cur->number = _number;
            cur->description = _description;
            cur->commodityID = _commodityID;
            cur->commodityName = _commodityName;
            cur->state = "onAuction";
            cur->sellerID = this->curUser->userID;
            cur->addedDate = this->generateDate();
            cur->floorPrice = _floorPrice;
            this->auctionSystem->addCommodity(cur);
        }
    }
}

std::string SellerCenter::generateTime() {
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

    timeStr += "-";

    if(this->_myTimer->min <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->min);
    return timeStr;
}

std::string SellerCenter::generateDate() {
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
    return timeStr;
}

void SellerCenter::viewCommodityList() {
    this->auctionSystem->showCommodityList(this->curUser->userID);
}
