#include "auctionsystem.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegExp>
AuctionSystem::AuctionSystem(userInfo **userInfoList, int userIdx)
{
    this->userIdx = userIdx;
    this->userInfoList = userInfoList;
    this->loadOrderInfo();
    this->loadCommodityInfo();
    this->_myTimer = new myTimer;
}

void AuctionSystem::loadCommodityInfo()
{
    qDebug() << QDir::currentPath();
    QString filePath = QDir::currentPath() + "/res/commodityInfo.txt";//文件路径
    QFile fin(filePath);
    if (!fin.open(QIODevice::ReadOnly)) {
        qDebug() << "file not exists!";
        QFile fout(filePath);
        fout.open(QIODevice::WriteOnly);
        QTextStream foutWrite(&fout);
        QString head = "commodityID,commodityName,floorPrice,number,description,sellerID,addedDate,state";
        foutWrite << head << endl;
        fout.close();
    }
    fin.close();
    fin.open(QIODevice::ReadOnly);
    QString buffer;
    QTextStream finRead(&fin);
    finRead >> buffer; // 先去掉标题行
    while(!finRead.atEnd()) { //读取
        buffer.clear();
        finRead >>  buffer;
        if(buffer.isEmpty()){
            //说明是因为换行符导致进入到这一行
            break;
        }
        if(this->commodityIdx >= COMMODITYCAPACITY) {
            qDebug() << "out of capacity!";
         }
        else {
            this->commodityInfoList[this->commodityIdx++] = this->createCommodity(buffer);
        }
    }
    fin.close();
}

void AuctionSystem::loadOrderInfo()
{
    qDebug() << QDir::currentPath();
    QString filePath = QDir::currentPath() + "/res/orderInfo.txt";//文件路径
    QFile fin(filePath);
    if (!fin.open(QIODevice::ReadOnly)) {
        qDebug() << "file not exists!";
        QFile fout(filePath);
        fout.open(QIODevice::WriteOnly);
        QTextStream foutWrite(&fout);
        QString head = "orderID,commodityID,sellerID,buyerID,bidTime,bidPrice,state";
        foutWrite << head << endl;
        fout.close();
    }
    fin.close();
    fin.open(QIODevice::ReadOnly);
    QString buffer;
    QTextStream finRead(&fin);
    finRead >> buffer; // 先去掉标题行
    while(!finRead.atEnd()) { //读取
        buffer.clear();
        finRead >>  buffer;
        if(buffer.isEmpty()){
            //说明是因为换行符导致进入到这一行
            break;
        }
        if(this->commodityIdx >= COMMODITYCAPACITY) {
            qDebug() << "out of capacity!";
         }
        else {
            this->orderInfoList[this->orderIdx++] = this->createOrder(buffer);
        }
    }
    fin.close();
}

commodityInfo *AuctionSystem::createCommodity(const QString &buffer)
{
    if(buffer.isEmpty()) {
        qDebug() << "error! no input!";
        return nullptr;
    }
    commodityInfo* cur = new commodityInfo;
    QStringList list = buffer.split(",");
    cur->commodityID = list[0];
    cur->commodityName = list[1];
    cur->floorPrice = list[2].toFloat();
    cur->number = list[3].toInt();
    cur->description = list[4];
    cur->sellerID = list[5];
    cur->addedDate = list[6];
    cur->state = list[7];
    qDebug() << cur->commodityName << " " << cur->state;
    return cur;
}

orderInfo *AuctionSystem::createOrder(const QString &buffer)
{
    if(buffer.isEmpty()) {
        qDebug() << "error! no input!";
        return nullptr;
    }
    orderInfo* cur = new orderInfo;
    QStringList list = buffer.split(",");
    cur->orderID = list[0];
    cur->commodityID = list[1];
    cur->sellerID = list[2];
    cur->buyerID = list[3];
    cur->bidTime = list[4];
    cur->bidPrice = list[5].toFloat();
    cur->state = list[6];
    qDebug() << cur->orderID << " " << cur->state;
    return cur;
}

AuctionSystem::~AuctionSystem()
{
    // 写文件
    QString filePath = QDir::currentPath() + "/res/commodityInfo.txt";//文件路径
    QFile fout(filePath);
    fout.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream foutWrite(&fout);
    foutWrite << "commodityID,commodityName,floorPrice,number,description,sellerID,addedDate,state" << endl;
    for(int i = 0; i < this->commodityIdx; i++) {
        if(commodityInfoList[i] != nullptr) {
            qDebug() << "delete: " << commodityInfoList[i]->commodityID << this->commodityInfoList[i]->commodityName;
            foutWrite << commodityInfoList[i]->commodityID << ",";
            foutWrite << commodityInfoList[i]->commodityName << ",";
            foutWrite << QString::number(commodityInfoList[i]->floorPrice, 'f', 1) << ",";
            foutWrite << QString::number(commodityInfoList[i]->number) << ",";
            foutWrite << commodityInfoList[i]->description << ",";
            foutWrite << commodityInfoList[i]->sellerID << ",";
            foutWrite << commodityInfoList[i]->addedDate << ",";
            foutWrite << commodityInfoList[i]->state << endl;
            qDebug() << commodityInfoList[i]->commodityName;
            delete commodityInfoList[i];
        }
    }
    fout.close();
    filePath = QDir::currentPath() + "/res/orderInfo.txt";
    QFile fout_2(filePath);
    fout_2.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream foutWrite_2(&fout_2);
    foutWrite_2 << "orderID,commodityID,sellerID,buyerID,bidTime,bidPrice,state" << endl;
    for(int i = 0; i < this->orderIdx; i++) {
        if(orderInfoList[i] != nullptr) {
            foutWrite_2 << orderInfoList[i]->orderID << ",";
            foutWrite_2 << orderInfoList[i]->commodityID << ",";
            foutWrite_2 << orderInfoList[i]->sellerID << ",";
            foutWrite_2 << orderInfoList[i]->buyerID << ",";
            foutWrite_2 << orderInfoList[i]->bidTime << ",";
            foutWrite_2 << QString::number(orderInfoList[i]->bidPrice, 'f', 1) << ",";
            foutWrite_2 << orderInfoList[i]->state << endl;
            delete orderInfoList[i];
        }
    }

}

commodityList *AuctionSystem::getCommodity_b(const QString &commodityName)
{
    commodityList *ret = new commodityList;
    ret->size = 0;
    if(commodityName.isEmpty()) {//说明要求显示所有在售的商品
        for(int i = 0; i < this->commodityIdx; i++) {
            qDebug() << this->commodityInfoList[i]->state;
            if(this->commodityInfoList[i]->state == "onAuction") {
                ret->list[ret->size++] = commodityInfoList[i];
            }
        }
    }
    else {
        QRegExp regex(commodityName);
        QRegExp idxReg("^M[0-9]{3}$");
        if(idxReg.exactMatch(commodityName)) {//说明输入的是商品ID
            for(int i = 0; i < this->commodityIdx; i++) {
                if(this->commodityInfoList[i]->commodityID == commodityName && this->commodityInfoList[i]->state == "onAuction") {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
            }
        }
        else {//否则匹配商品名
            for(int i = 0; i < this->commodityIdx; i++) {
                if(regex.indexIn(this->commodityInfoList[i]->commodityName)!= -1 && this->commodityInfoList[i]->state == "onAuction") {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
                else {
                    qDebug() << regex.exactMatch(this->commodityInfoList[i]->commodityName);
                }
            }
        }
    }
    return ret;
}

commodityList *AuctionSystem::getCommodity_s(const QString &commodityName, const QString &sellerID)
{
    commodityList *ret = new commodityList;
    ret->size = 0;
    if(commodityName.isEmpty()) {//说明要求显示所有在售的商品
        for(int i = 0; i < this->commodityIdx; i++) {
//            qDebug() << this->commodityInfoList[i]->state;
            if(this->commodityInfoList[i]->sellerID == sellerID) {
                ret->list[ret->size++] = commodityInfoList[i];
            }
        }
    }
    else {
        QRegExp regex(commodityName);
        QRegExp idxReg("^M[0-9]{3}$");
        if(idxReg.exactMatch(commodityName)) {//匹配商品ID
            for(int i = 0; i < this->commodityIdx; i++) {
                if(this->commodityInfoList[i]->commodityID == commodityName && this->commodityInfoList[i]->sellerID == sellerID) {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
            }
        }
        else {
            for(int i = 0; i < this->commodityIdx; i++) {
                if(regex.indexIn(this->commodityInfoList[i]->commodityName)!= -1 && this->commodityInfoList[i]->sellerID == sellerID) {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
            }
        }
    }
    return ret;
}

commodityList *AuctionSystem::getCommodity_a(const QString &commodityName)
{
    auto *ret = new commodityList;
    ret->size = 0;
    if(commodityName.isEmpty()) {
        for(int i = 0; i < this->commodityIdx; i++) {
            ret->list[ret->size++] = commodityInfoList[i];
        }
    }
    else {
        QRegExp regex(commodityName);
        QRegExp idxReg("^M[0-9]{3}$");
        if(idxReg.exactMatch(commodityName)) {//匹配商品ID
            for(int i = 0; i < this->commodityIdx; i++) {
                if(this->commodityInfoList[i]->commodityID == commodityName) {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
            }
        }
        else {
            for(int i = 0; i < this->commodityIdx; i++) {
                if(regex.indexIn(this->commodityInfoList[i]->commodityName)!= -1) {
                    ret->list[ret->size++] = commodityInfoList[i];
                }
            }
        }
    }
    return ret;
}

orderList *AuctionSystem::getOrderList_b(const QString &buyerID)
{
    auto *ret = new orderList;
    ret->size = 0;
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->buyerID == buyerID) {
            ret->list[ret->size++] = orderInfoList[i];
        }
    }
    return ret;
}

orderList *AuctionSystem::getOrderList_s(const QString &sellerID)
{
    auto *ret = new orderList;
    ret->size = 0;
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->sellerID == sellerID) {
            ret->list[ret->size++] = orderInfoList[i];
        }
    }
    return ret;
}

orderList *AuctionSystem::getOrderList_a()
{
    auto *ret = new orderList;
    ret->size = 0;
    for(int i = 0; i < this->orderIdx; i++) {
        ret->list[ret->size++] = orderInfoList[i];
    }
    return ret;
}

QString AuctionSystem::addCommoditycheck()
{
    QString ret = "";
    if(this->commodityIdx >= COMMODITYCAPACITY) {
        return ret;
    }
    QString num = QString::number(this->commodityIdx+1);
    if(num.length() == 1) {
        ret += "M00";
    }
    else if(num.length() == 2) {
        ret += "M0";
    }
    else {
        ret += "M";
    }
    ret += num;
    return ret;
}

void AuctionSystem::addCommodity(commodityInfo *cur)
{
    this->commodityInfoList[this->commodityIdx++] = cur;
}

bool AuctionSystem::bidCheck(const QString &buyerID, const QString &commodityID) {
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->buyerID == buyerID && this->orderInfoList[i]->commodityID == commodityID
            && this->orderInfoList[i]->state == "inProcess") {
            return false;
        }
    }
    return true;
}

void AuctionSystem::addOrder(const QString &commodityID, const QString &sellerID, const QString &buyerID, float bidPrice)
{
    //get orderID
    QString orderID;
    QString num = QString::number(this->orderIdx+1);
    if(num.length() == 1) {
        orderID += "T00";
    }
    else if(num.length() == 2) {
        orderID += "T0";
    }
    else {
        orderID += "T";
    }
    orderID += num;
    orderInfo * cur = new orderInfo;
    cur->orderID = orderID;
    cur->commodityID = commodityID;
    cur->sellerID = sellerID;
    cur->buyerID = buyerID;
    cur->bidTime = generateTime();
    cur->bidPrice = bidPrice;
    cur->state = "inProcess";
    this->orderInfoList[this->orderIdx++] = cur;
}

QString AuctionSystem::generateTime()
{
    time_t now = time(0);
    this->ltm = localtime(&now);
    _myTimer->year = 1900 + ltm->tm_year;
    _myTimer->month = 1 + ltm->tm_mon;
    _myTimer->day = ltm->tm_mday;
    _myTimer->hour = ltm->tm_hour;
    _myTimer->min = ltm->tm_min;
    _myTimer->sec = ltm->tm_sec;
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

    timeStr += ":";

    if(this->_myTimer->min <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->min);

    timeStr += ":";

    if(this->_myTimer->sec <= 9) {
        timeStr += "0";
    }
    timeStr += std::to_string(this->_myTimer->sec);
    return QString::fromStdString(timeStr);
}

commodityInfo *AuctionSystem::getCommodity(const QString &commodityID)
{
    for(int i = 0; i < this->commodityIdx; i++) {
        if(this->commodityInfoList[i]->commodityID == commodityID) return commodityInfoList[i];
    }
    return nullptr;
}

userList *AuctionSystem::getUserList(const QString &username)
{
    auto *ret = new userList;
    ret->size = 0;
    if(username.isEmpty()) {
        for(int i = 0; i < this->userIdx; i++){
            ret->list[ret->size++] = this->userInfoList[i];
        }
    }
    else {
        QRegExp regex(username);
        QRegExp idxReg("^U[0-9]{3}$");
        if(idxReg.exactMatch(username)) {//说明输入的是ID
            for(int i = 0; i < this->userIdx; i++) {
                if(this->userInfoList[i]->userID == username) {
                    ret->list[ret->size++] = this->userInfoList[i];
                }
            }
        }
        else {
            for(int i = 0; i < this->userIdx; i++) {
                if(regex.indexIn(this->userInfoList[i]->username) != -1) {
                    ret->list[ret->size++] = this->userInfoList[i];
                }
            }
        }
    }
    return ret;
}

orderList* AuctionSystem::calcResult()
{
    auto *ret = new orderList;
    ret->size = 0;
    //clear:避免未释放对象前再次调用该函数, 此时已经存了上一次的node
    for(int i = 0; i < this->commodityIdx; i++) {
        this->vector[i].clear();
    }
    //initialize
    for(int i = 0; i < this->commodityIdx; i++) {
        this->vector[i].ini(commodityInfoList[i], userInfoList[ID2int(commodityInfoList[i]->sellerID)]);
    }
    //filter & categorize
    for(int i = 0; i < this->orderIdx; i++) {
        if(this->orderInfoList[i]->state == "inProcess") {
            this->vector[ID2int(orderInfoList[i]->commodityID)].addNode(orderInfoList[i], userInfoList[ID2int(orderInfoList[i]->buyerID)]);
            ret->list[ret->size++] = orderInfoList[i];
        }
    }
    //rank & update
    for(int i = 0; i < this->commodityIdx; i++) {
        if(vector[i].empty()) continue; //说明没有订单
        vector[i].rank();
        vector[i].update();
    }
    return ret;
}

int AuctionSystem::ID2int(const QString &str) { // "M001"->0
    return str.mid(1, 3).toInt() - 1;
}

bool AuctionSystem::banUser(int idx)
{
    if(idx >= 0 && idx < this->userIdx) {
        this->userInfoList[idx]->userState = this->userInfoList[idx]->userState == "active" ? "inactive" : "active";
        return true;
    }
    return false;
}

bool AuctionSystem::UserNameCheck(QString &username)
{
    for(int i = 0; i < this->userIdx; i++) {
        if(this->userInfoList[i]->username == username) return false;
    }
    return true;
}
