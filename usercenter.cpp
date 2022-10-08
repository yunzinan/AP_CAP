#include "usercenter.h"
#include "ui_usercenter.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include "config.h"
#include <QCryptographicHash>

UserCenter::UserCenter(QWidget *parent, userInfo *curUser, AuctionSystem *auctionSystem): QMainWindow(parent), ui(new Ui::UserCenter)
{
    this->_myTimer = new myTimer;
    this->curUser = curUser;
    ui->setupUi(this);
    this->setWindowTitle("用户界面");
    this->setMinimumSize(2000, 1500);
    this->auctionSystem = auctionSystem;
    this->showUserInfo();
//    this->showOrderList_b();
//    this->showOrderList_s();
//    this->searchCommodityList_b();
//    this->searchCommodityList_s();
    ui->lineEdit_number->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$"), this));
    ui->lineEdit_address->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,40}$"), this));
    ui->lineEdit_balance->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[\.]?[0-9]?$"), this));
    ui->lineEdit_username->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,10}$"), this));
    ui->lineEdit_userPwd->setValidator(new QRegExpValidator(QRegExp("^[a-z0-9]{1,20}$"), this));
    ui->lineEdit_floorPrice->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[\.]?[0-9]?$"), this));
    ui->lineEdit_Description->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,200}$"), this));
    ui->lineEdit_phoneNumber->setValidator(new QRegExpValidator(QRegExp("^[0-9]{1,20}$"), this));
    ui->lineEdit_commodityName->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,20}$"), this));
    ui->lineEdit_commoditySearch_b->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]*$"), this));
    ui->lineEdit_commoditySearch_s->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]*$"), this));
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, [=](int idx){
        if(idx == 2) {
            this->showUserInfo();
            qDebug() << "刷新用户信息";
        }
    });
    connect(ui->pushButton_username, &QPushButton::clicked, [=](){
        curUser->username = ui->lineEdit_username->text();
        QMessageBox::information(this, "个人信息", "修改成功!");
    });
    connect(ui->pushButton_userPwd, &QPushButton::clicked, [=](){
        QString pwd = ui->lineEdit_userPwd->text();
        curUser->password = pwdEncrpt(pwd);
        QMessageBox::information(this, "个人信息", "修改成功!");
    });
    connect(ui->pushButton_phoneNumber, &QPushButton::clicked, [=](){
        curUser->phonenumber = ui->lineEdit_phoneNumber->text();
        QMessageBox::information(this, "个人信息", "修改成功!");
    });
    connect(ui->pushButton_address, &QPushButton::clicked, [=](){
        curUser->address = ui->lineEdit_address->text();
        QMessageBox::information(this, "个人信息", "修改成功!");
    });
    connect(ui->pushButton_balance, &QPushButton::clicked, [=](){
        curUser->balance += QString::number(ui->lineEdit_balance->text().toFloat(), 'f', 1).toFloat();
        QMessageBox::information(this, "充值", "充值成功!");
        this->showUserInfo();//刷新
    });
    connect(ui->searchBtn_b, &QPushButton::clicked, [=](){
        this->searchCommodityList_b();
    });
    connect(ui->searchBtn_s, &QPushButton::clicked, [=](){
        this->searchCommodityList_s();
    });
    connect(ui->tabWidget_2, &QTabWidget::tabBarClicked, [=](int idx){
        if(idx == 1) {
            this->showOrderList_b();
        }
    });
    connect(ui->tabWidget_3, &QTabWidget::tabBarClicked, [=](int idx){
        if(idx == 1) {
            this->showOrderList_s();
        }
    });
    connect(ui->pushButton_commodityAdd, &QPushButton::clicked, [=](){
        this->addCommodity();
    });
    //卖家商品双击后弹出商品竞拍界面
    connect(ui->commodityTab_b, &QTableWidget::itemDoubleClicked, [=](QTableWidgetItem *item){
       int row = item->row();
       QString text = this->ui->commodityTab_b->item(row, 0)->text();
       commodityInfo *selectedCommodity = this->auctionSystem->getCommodity(text);
       this->bidScene = new MyMessageBox(nullptr, curUser, selectedCommodity, this->auctionSystem);
       connect(bidScene, &MyMessageBox::exitSignal, [=](){
           bidScene->hide();
//           this->show();
           qDebug() << "retrun signal emitted!";
   //        delete bidScene;
       });
       bidScene->show();
       qDebug() << "------show!!!!";
//       this->hide();
    });
    //卖家商品界面点击后弹出修改窗口
    connect(ui->commodityTab_s, &QTableWidget::cellDoubleClicked, [=](int row, int col){
        qDebug() << "row: " << row << "col: " << col;
        this->commodityBox = new CommodityBox(nullptr, this->auctionSystem->getCommodity(ui->commodityTab_s->item(row, 0)->text()));
        connect(commodityBox, &CommodityBox::exitSignal, [=](){
            commodityBox->hide();
            //刷新一下表格
            this->searchCommodityList_s();
            qDebug() << "return signal emitted!";
        });
        commodityBox->show();
        qDebug() << "-----show!!!!!!";
    });
    connect(ui->lineEdit_commodityName, &QLineEdit::editingFinished, [=](){
        QString text = ui->lineEdit_commodityName->text();
        if(text.length() > 20) {
            ui->label_nameCheck->setText(QString("太长啦!"));
        }
//        else if(text.indexOf()))/*regex判断是否只由数字和小写字母*/
        else ui->label_nameCheck->setText(QString("可用!"));
    });
    connect(ui->lineEdit_Description, &QLineEdit::editingFinished, [=](){
        QString text = ui->lineEdit_Description->text();
        if(text.length() >= 200) {
            ui->label_dscrptCheck->setText(QString("太长啦!"));
        }
        else ui->label_dscrptCheck->setText(QString("可用!"));
    });
    connect(ui->lineEdit_floorPrice, &QLineEdit::editingFinished, [=](){
        QString text = ui->lineEdit_floorPrice->text();
        if(!this->isDigitString(text)) {
            ui->label_floorPriceCheck->setText(QString("请输入纯数字!"));
        }
        else ui->label_floorPriceCheck->setText(QString("可用!"));
    });
    connect(ui->lineEdit_number, &QLineEdit::editingFinished, [=](){
        QString text = ui->lineEdit_number->text();
        if(!this->isDigitString(text)) {
            ui->numberCheck->setText(QString("请输入纯数字!"));
        }
        else ui->numberCheck->setText(QString("可用!"));
    });
}

UserCenter::~UserCenter()
{
    delete ui;
}

void UserCenter::showUserInfo()
{
    ui->lineEdit_userID->setText(curUser->userID);
    ui->lineEdit_username->setText(curUser->username);
//    ui->lineEdit_userPwd->setText(curUser->password);
    ui->lineEdit_userPwd->clear();
    ui->lineEdit_phoneNumber->setText(curUser->phonenumber);
    ui->lineEdit_address->setText(curUser->address);
    ui->label_balance->setText(QString::number(curUser->balance, 'f', 1));
}

void UserCenter::searchCommodityList_b()
{
    commodityList *ret = this->auctionSystem->getCommodity_b(ui->lineEdit_commoditySearch_b->text());
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到您搜索的商品!");
    }
    else {
        ui->commodityTab_b->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_spid = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_spmc = new QTableWidgetItem(ret->list[i]->commodityName);
            auto tab_dj = new QTableWidgetItem(QString::number(ret->list[i]->floorPrice, 'f', 1));
            auto tab_number = new QTableWidgetItem(QString::number(ret->list[i]->number));
            auto tab_addedDate = new QTableWidgetItem(ret->list[i]->addedDate);
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->commodityTab_b->setItem(i, 0, tab_spid);
            ui->commodityTab_b->setItem(i, 1, tab_spmc);
            ui->commodityTab_b->setItem(i, 2, tab_dj);
            ui->commodityTab_b->setItem(i, 3, tab_number);
            ui->commodityTab_b->setItem(i, 4, tab_addedDate);
            ui->commodityTab_b->setItem(i, 5, tab_state);
            qDebug() << tab_dj << tab_spmc;
        }
    }
}

void UserCenter::searchCommodityList_s()
{
    commodityList *ret = this->auctionSystem->getCommodity_s(ui->lineEdit_commoditySearch_s->text(), this->curUser->userID);
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到您搜索的商品!");
    }
    else {
        ui->commodityTab_s->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_spid = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_spmc = new QTableWidgetItem(ret->list[i]->commodityName);
            auto tab_dj = new QTableWidgetItem(QString::number(ret->list[i]->floorPrice, 'f', 1));
            auto tab_number = new QTableWidgetItem(QString::number(ret->list[i]->number));
            auto tab_addedDate = new QTableWidgetItem(ret->list[i]->addedDate);
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->commodityTab_s->setItem(i, 0, tab_spid);
            ui->commodityTab_s->setItem(i, 1, tab_spmc);
            ui->commodityTab_s->setItem(i, 2, tab_dj);
            ui->commodityTab_s->setItem(i, 3, tab_number);
            ui->commodityTab_s->setItem(i, 4, tab_addedDate);
            ui->commodityTab_s->setItem(i, 5, tab_state);
            qDebug() << tab_dj << tab_spmc;
        }
    }
}

void UserCenter::showOrderList_b()
{
    orderList *ret = this->auctionSystem->getOrderList_b(this->curUser->userID);
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到您的订单!");
    }
    else {
        ui->orderTab_b->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_order = new QTableWidgetItem(ret->list[i]->orderID);
            auto tab_commodity = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_seller = new QTableWidgetItem(ret->list[i]->sellerID);
            auto tab_buyer = new QTableWidgetItem(ret->list[i]->buyerID);
            auto tab_bidTime = new QTableWidgetItem(ret->list[i]->bidTime);
            auto tab_bidPrice = new QTableWidgetItem(QString::number(ret->list[i]->bidPrice, 'f', 1));
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->orderTab_b->setItem(i, 0, tab_order);
            ui->orderTab_b->setItem(i, 1, tab_commodity);
            ui->orderTab_b->setItem(i, 2, tab_seller);
            ui->orderTab_b->setItem(i, 3, tab_buyer);
            ui->orderTab_b->setItem(i, 4, tab_bidTime);
            ui->orderTab_b->setItem(i, 5, tab_bidPrice);
            ui->orderTab_b->setItem(i, 6, tab_state);
        }
    }
}

void UserCenter::showOrderList_s()
{
    orderList *ret = this->auctionSystem->getOrderList_s(this->curUser->userID);
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到您的订单!");
    }
    else {
        ui->orderTab_s->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_order = new QTableWidgetItem(ret->list[i]->orderID);
            auto tab_commodity = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_seller = new QTableWidgetItem(ret->list[i]->sellerID);
            auto tab_buyer = new QTableWidgetItem(ret->list[i]->buyerID);
            auto tab_bidTime = new QTableWidgetItem(ret->list[i]->bidTime);
            auto tab_bidPrice = new QTableWidgetItem(QString::number(ret->list[i]->bidPrice, 'f', 1));
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->orderTab_s->setItem(i, 0, tab_order);
            ui->orderTab_s->setItem(i, 1, tab_commodity);
            ui->orderTab_s->setItem(i, 2, tab_seller);
            ui->orderTab_s->setItem(i, 3, tab_buyer);
            ui->orderTab_s->setItem(i, 4, tab_bidTime);
            ui->orderTab_s->setItem(i, 5, tab_bidPrice);
            ui->orderTab_s->setItem(i, 6, tab_state);
        }
    }
}

void UserCenter::addCommodity()
{
    commodityInfo* cur = new commodityInfo;
    cur->commodityName = this->ui->lineEdit_commodityName->text();
    cur->description = ui->lineEdit_Description->text();
    cur->floorPrice = ui->lineEdit_floorPrice->text().toFloat();
    cur->number = ui->lineEdit_number->text().toInt();
    cur->sellerID = curUser->userID;
    cur->addedDate = generateDate();
    cur->commodityID = this->auctionSystem->addCommoditycheck();
    cur->state = "onAuction";
    this->auctionSystem->addCommodity(cur);
    QMessageBox::information(this, "提示", "添加商品成功!");
}

QString UserCenter::generateDate()
{
    time_t now = time(0);
    this->ltm = localtime(&now);
    _myTimer->year = 1900 + ltm->tm_year;
    _myTimer->month = 1 + ltm->tm_mon;
    _myTimer->day = ltm->tm_mday;
    _myTimer->hour = ltm->tm_hour;
    _myTimer->min = ltm->tm_min;
    _myTimer->sec = ltm->tm_sec;
    QString timeStr;
    timeStr.append(QString::number(this->_myTimer->year));

    timeStr += "-";

    if(this->_myTimer->month <= 9) {
        timeStr += "0";
    }
    timeStr.append(QString::number(this->_myTimer->month));

    timeStr += "-";

    if(this->_myTimer->day <= 9) {
        timeStr += "0";
    }
    timeStr.append(QString::number(this->_myTimer->day));
    return timeStr;
}

QString UserCenter::pwdEncrpt(QString &username)
{
    QString md5Str = QCryptographicHash::hash(username.toLatin1(),QCryptographicHash::Md5).toHex();
    qDebug() << "plainText: " << username << " cipherText: " << md5Str;
    return md5Str;
}
