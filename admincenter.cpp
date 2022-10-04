#include "admincenter.h"
#include "ui_admincenter.h"
#include <QMessageBox>

AdminCenter::AdminCenter(QWidget *parent, AuctionSystem *auctionSystem) :
    QMainWindow(parent),
    ui(new Ui::AdminCenter)
{
    ui->setupUi(this);
    setWindowTitle("管理员界面");
    setMinimumSize(2000, 1500);
    this->auctionSystem = auctionSystem;
    connect(ui->pushButton_commodity, &QPushButton::clicked, [=](){
        this->showCommodityList();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        this->showUserList();
    });
    connect(ui->pushButton_endAuction, &QPushButton::clicked, [=](){
        if(QMessageBox::warning(this, "提醒", "您确定终止竞拍吗?", QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes) {
            auto *ret = this->auctionSystem->calcResult();
            this->showAuctionRes(ret);
        }
    });
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, [=](int idx){
        if(idx == 2) this->showOrderList();
    });
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, [=](int row, int col){
        qDebug() << "row: " << row << "col: " << col;
        this->commodityBox = new CommodityBox(nullptr, this->auctionSystem->getCommodity(ui->tableWidget->item(row, 0)->text()));
        connect(commodityBox, &CommodityBox::exitSignal, [=](){
            commodityBox->hide();
            //刷新一下表格
            this->showCommodityList();
            qDebug() << "return signal emitted!";
        });
        commodityBox->show();
        qDebug() << "-----show!!!!!!";
    });
    connect(ui->tableWidget_2, &QTableWidget::cellDoubleClicked, [=](int row, int col){
        if(col == 4) {
            if(QMessageBox::information(this, "提醒", "确定封禁/激活该用户?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                if(!this->auctionSystem->banUser(row)) {
                    QMessageBox::warning(this, "错误", "什么鬼?!");
                }
                else QMessageBox::information(this, "提示", "用户状态修改成功!");
                this->showUserList();//刷新
            }
        }
    });
    this->showCommodityList();
    this->showOrderList();
    this->showUserList();
}

AdminCenter::~AdminCenter()
{
    delete ui;
}

void AdminCenter::showUserList()
{
    userList *ret = this->auctionSystem->getUserList(ui->lineEdit_user->text());
    ui->tableWidget_2->setRowCount(ret->size);
    for(int i = 0; i < ret->size; i++) {
        auto tab_userID = new QTableWidgetItem(ret->list[i]->userID);
        auto tab_username = new QTableWidgetItem(ret->list[i]->username);
        auto tab_password = new QTableWidgetItem(ret->list[i]->password);
        auto tab_balance = new QTableWidgetItem(QString::number(ret->list[i]->balance, 'f', 1));
        auto tab_state = new QTableWidgetItem(ret->list[i]->userState);
        ui->tableWidget_2->setItem(i, 0, tab_userID);
        ui->tableWidget_2->setItem(i, 1, tab_username);
        ui->tableWidget_2->setItem(i, 2, tab_password);
        ui->tableWidget_2->setItem(i, 3, tab_balance);
        ui->tableWidget_2->setItem(i, 4, tab_state);
    }
}

void AdminCenter::showCommodityList()
{
    commodityList *ret = this->auctionSystem->getCommodity_a(ui->lineEdit_commodity->text());
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到您搜索的商品!");
    }
    else {
        ui->tableWidget->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_spid = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_spmc = new QTableWidgetItem(ret->list[i]->commodityName);
            auto tab_dj = new QTableWidgetItem(QString::number(ret->list[i]->floorPrice, 'f', 1));
            auto tab_number = new QTableWidgetItem(QString::number(ret->list[i]->number));
            auto tab_addedDate = new QTableWidgetItem(ret->list[i]->addedDate);
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->tableWidget->setItem(i, 0, tab_spid);
            ui->tableWidget->setItem(i, 1, tab_spmc);
            ui->tableWidget->setItem(i, 2, tab_dj);
            ui->tableWidget->setItem(i, 3, tab_number);
            ui->tableWidget->setItem(i, 4, tab_addedDate);
            ui->tableWidget->setItem(i, 5, tab_state);
//            qDebug() << tab_dj << tab_spmc;
        }
    }
}

void AdminCenter::showOrderList()
{
    orderList *ret = this->auctionSystem->getOrderList_a();
    if(ret->size == 0) {
        QMessageBox::warning(this, "错误", "未找到订单!");
    }
    else {
        ui->tableWidget_3->setRowCount(ret->size);
        for(int i = 0; i < ret->size; i++) {
            auto tab_order = new QTableWidgetItem(ret->list[i]->orderID);
            auto tab_commodity = new QTableWidgetItem(ret->list[i]->commodityID);
            auto tab_seller = new QTableWidgetItem(ret->list[i]->sellerID);
            auto tab_buyer = new QTableWidgetItem(ret->list[i]->buyerID);
            auto tab_bidTime = new QTableWidgetItem(ret->list[i]->bidTime);
            auto tab_bidPrice = new QTableWidgetItem(QString::number(ret->list[i]->bidPrice, 'f', 1));
            auto tab_state = new QTableWidgetItem(ret->list[i]->state);
            ui->tableWidget_3->setItem(i, 0, tab_order);
            ui->tableWidget_3->setItem(i, 1, tab_commodity);
            ui->tableWidget_3->setItem(i, 2, tab_seller);
            ui->tableWidget_3->setItem(i, 3, tab_buyer);
            ui->tableWidget_3->setItem(i, 4, tab_bidTime);
            ui->tableWidget_3->setItem(i, 5, tab_bidPrice);
            ui->tableWidget_3->setItem(i, 6, tab_state);
        }
    }
}

void AdminCenter::showAuctionRes(orderList *ret)
{
    if(ret->size == 0) {
        QMessageBox::warning(this, "提醒", "当前没有任何竞拍信息哦");
        return;
    }
    ui->tableWidget_4->setRowCount(ret->size);
    for(int i = 0; i < ret->size; i++) {
        auto tab_order = new QTableWidgetItem(ret->list[i]->orderID);
        auto tab_commodity = new QTableWidgetItem(ret->list[i]->commodityID);
        auto tab_seller = new QTableWidgetItem(ret->list[i]->sellerID);
        auto tab_buyer = new QTableWidgetItem(ret->list[i]->buyerID);
        auto tab_bidTime = new QTableWidgetItem(ret->list[i]->bidTime);
        auto tab_bidPrice = new QTableWidgetItem(QString::number(ret->list[i]->bidPrice, 'f', 1));
        auto tab_state = new QTableWidgetItem(ret->list[i]->state);
        auto tab_commodityName = new QTableWidgetItem(this->auctionSystem->getCommodity(ret->list[i]->commodityID)->commodityName);
        ui->tableWidget_4->setItem(i, 0, tab_order);
        ui->tableWidget_4->setItem(i, 1, tab_commodity);
        ui->tableWidget_4->setItem(i, 2, tab_seller);
        ui->tableWidget_4->setItem(i, 3, tab_buyer);
        ui->tableWidget_4->setItem(i, 4, tab_commodityName);
        ui->tableWidget_4->setItem(i, 5, tab_bidTime);
        ui->tableWidget_4->setItem(i, 6, tab_bidPrice);
        ui->tableWidget_4->setItem(i, 7, tab_state);
//        qDebug() << ret->list[i]->orderID << " " << ret->list[i]->bidPrice;
    }
}


