#include "commoditybox.h"
#include "ui_commoditybox.h"
#include <QMessageBox>
#include <QRadioButton>

CommodityBox::CommodityBox(QWidget *parent, commodityInfo* cur) :
    QWidget(parent),
    ui(new Ui::CommodityBox)
{
    ui->setupUi(this);
    setWindowTitle("修改商品属性");
    this->cur = cur;
    connect(ui->confirmBtn, &QPushButton::clicked, [=](){
        if(QMessageBox::information(this, "提醒", "确认修改?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            this->modifyCommodity();
        }
        emit exitSignal();
    });
    connect(ui->cancelBtn, &QPushButton::clicked, [=](){
        emit exitSignal();
    });
    this->showCommodity();
}
CommodityBox::~CommodityBox()
{
    delete ui;
}

void CommodityBox::modifyCommodity()
{
    cur->commodityName = ui->lineEdit_name->text();
    cur->description = ui->lineEdit_description->text();
    if(ui->radio_onAuction->isChecked()) cur->state = "onAuction";
    else cur->state = "removed";
    cur->number = ui->lineEdit_number->text().toInt();
    cur->floorPrice = ui->lineEdit_floorPrice->text().toFloat();
}

void CommodityBox::showCommodity()
{
    ui->lineEdit_name->setText(cur->commodityName);
    if(cur->state == "onAuction") ui->radio_onAuction->setChecked(true);
    else ui->radio_removed->setChecked(true);
    ui->lineEdit_number->setText(QString::number(cur->number));
    ui->lineEdit_floorPrice->setText(QString::number(cur->floorPrice, 'f', 1));
    ui->lineEdit_description->setText(cur->description);
}
