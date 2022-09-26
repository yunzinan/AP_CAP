#include "mymessagebox.h"
#include "ui_mymessagebox.h"
#include <QMessageBox>
MyMessageBox::MyMessageBox(QWidget *parent, userInfo *curUser, commodityInfo *cur, AuctionSystem *auctionSystem): QWidget(parent),
    ui(new Ui::MyMessageBox)
{
    this->cur = cur;
    this->auctionSystem = auctionSystem;
    this->curUser = curUser;
    ui->setupUi(this);
    setWindowTitle("竞拍界面");
    setMinimumSize(600, 800);
    this->showCommodityInfo();
    connect(ui->pushButton, &QPushButton::clicked, [=](){
        qDebug() << "确认购买";
        this->purchase();
        emit exitSignal();
    });
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        emit exitSignal();
    });
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

void MyMessageBox::showCommodityInfo()
{
    ui->tableWidget->setColumnCount(1);
    auto tab_name = new QTableWidgetItem(cur->commodityName);
    auto tab_id = new QTableWidgetItem(cur->commodityID);
    auto tab_date = new QTableWidgetItem(cur->addedDate);
    auto tab_description = new QTableWidgetItem(cur->description);
    auto tab_floorPrice = new QTableWidgetItem(QString::number(cur->floorPrice, 'f', 1));
    auto tab_number = new QTableWidgetItem(QString::number(cur->number));
    auto tab_sellerID = new QTableWidgetItem(cur->sellerID);
    ui->tableWidget->setItem(0, 0, tab_id);
    ui->tableWidget->setItem(1, 0, tab_name);
    ui->tableWidget->setItem(2, 0, tab_description);
    ui->tableWidget->setItem(3, 0, tab_sellerID);
    ui->tableWidget->setItem(4, 0, tab_floorPrice);
    ui->tableWidget->setItem(5, 0, tab_date);
    ui->tableWidget->setItem(6, 0, tab_number);
}

void MyMessageBox::purchase()
{
    float bidPrice = ui->lineEdit->text().toFloat();
    if(bidPrice < cur->floorPrice) {
        QMessageBox::warning(this, "错误", "出价失败, 出价金额应高于底价!");
    }
    else if(!this->auctionSystem->bidCheck(curUser->userID, cur->commodityID)) {
        QMessageBox::warning(this, "错误", "您已经对该商品出价过了!");

    }
    else if(this->curUser->balance < bidPrice) {
        QMessageBox::warning(this, "错误", "兄弟, 你钱没带够!");
    }
    else {
        QMessageBox::information(this, "成功", "恭喜你, 出价成功!");
        this->curUser->balance -= bidPrice;
        this->auctionSystem->addOrder(this->cur->commodityID, this->cur->sellerID, this->curUser->userID, bidPrice);
    }
    ui->lineEdit->clear();
}
