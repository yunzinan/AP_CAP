//
// Created by Jack_shen on 2022/9/12.
//

#include <iomanip>
#include "SellerCenter.h"


SellerCenter::SellerCenter(userInfo *_curUser, AuctionSystem *_system) {
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
    this->auctionSystem = _system;
//    this->selectOpt();
}

void SellerCenter::selectOpt() {
    int ans;
    bool isValid = false;
    while(!isValid) {
        //        system("cls");
        printf("------------------------------------------------------------\n");
        printf("**************************Seller Center*********************\n");
        printf("------------------------------------------------------------\n");
        printf("1. Release Commodity 2. View Commodity List\n"
               "3. Modify Commodity 4. Cancel Commodity 5. View Order List 6. Exit\n");
        printf("type a number to continue: ");
        std::cin >> ans;
        switch (ans) {
            case 1:
                this->releaseCommodity();
                break;
            case 2:
                this->viewCommodityList();
                break;
            case 3:
                this->modifyCommodityInfo();
                break;
            case 4:
                this->cancelCommodity();
                break;
            case 5:
                this->viewOrderList();
                break;
            case 6: // exit
                isValid = true;
                break;
            default:
                printf("error! type again!\n");
                std::cin >> ans;
                break;
        }
    }
}

SellerCenter::~SellerCenter() {
//    delete this->auctionSystem;
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

void SellerCenter::modifyCommodityInfo() {
    printf("type in the commodityID you want to modify: ");
    std::string _commodityID;
    std::cin >> _commodityID;
    //find
    commodityInfo * response = this->auctionSystem->findCommodity(_commodityID, this->curUser->userID);
    if(response == nullptr) {
        printf("failed! commodity not find!\n");
        return ;
    }
    printf("************************************************************\n");
    std::cout << "commodityID: " << response->commodityID << std::endl
            << "commodityName: " << response->commodityName << std::endl
            << "floorPrice: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << response->floorPrice << std::endl
            << "number: " << response->number << std::endl
            << "description: " << response->description << std::endl;
    printf("************************************************************\n");
    printf("1. commodityName 2. floorPrice 3. number 4. description\n");
    printf("select a number of the property you want to modify: ");
    int ans;
    scanf("%d", &ans);
    std::string _commodityName, _description;
    float _floorPrice;
    int _number;
    switch (ans) {
        case 1:
            printf("new commodityName: ");
            std::cin >> _commodityName;
            response->commodityName = _commodityName;
            std::cout << "now commodityName: " << response->commodityName << std::endl;
            break;
        case 2:
            printf("new floorPrice: ");
            std::cin >> _floorPrice;
            response->floorPrice = _floorPrice;
            std::cout << "now floorPrice: " << std::setiosflags(std::ios::fixed) << std::setprecision(1) << response->floorPrice << std::endl;
            break;
        case 3:
            printf("new number: ");
            scanf("%d", &_number);
            response->number = _number;
            std::cout << "now number: " << response->number << std::endl;
            break;
        case 4:
            printf("new description: ");
            std::cin >> _description;
            response->description = _description;
            std::cout << "now description: " << response->description << std::endl;
            break;
        default:
            printf("failed! wrong input!\n");
            break;
    }
}

void SellerCenter::cancelCommodity() {
    printf("type in the commodityID you want to cancel: ");
    std::string _commodityID;
    std::cin >> _commodityID;
    //find
    commodityInfo *response = this->auctionSystem->findCommodity(_commodityID, this->curUser->userID);
    if(response == nullptr) {
        printf("failed! commodity not find!\n");
        return ;
    }
    printf("************************************************************\n");
    std::cout << "commodityID: " << response->commodityID << std::endl
              << "commodityName: " << response->commodityName << std::endl
              << "floorPrice: " << response->floorPrice << std::endl
              << "number: " << response->number << std::endl
              << "description: " << response->description << std::endl;
    printf("************************************************************\n");
    printf("1. cancelCommodity 2. re-releaseCommodity\n");
    printf("select a number: ");
    int ans;
    std::cin >> ans;
    if(ans == 1) {
        if(response->state == "onAuction") {
            response->state = "removed";
            printf("success!\n");
        }
        else printf("failed! already removed!\n");
    }
    else if(ans == 2) {
        if(response->state == "removed") {
            response->state = "onAuction";
            printf("success!\n");
        }
        else printf("failed! already onAuction!\n");
    }
    else {
        printf("failed! wrong input!\n");
        std::cin >> ans;
    }
}

void SellerCenter::viewOrderList() {
    this->auctionSystem->viewOrderList_S(this->curUser->userID);
}
