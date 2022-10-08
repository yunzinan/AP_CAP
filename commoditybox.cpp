#include "commoditybox.h"
#include "ui_commoditybox.h"
#include <QMessageBox>
#include <QRadioButton>
#include <QRegExpValidator>

CommodityBox::CommodityBox(QWidget *parent, commodityInfo* cur) :
    QWidget(parent),
    ui(new Ui::CommodityBox)
{
    ui->setupUi(this);
    setWindowTitle("修改商品属性");
    this->cur = cur;
    ui->lineEdit_name->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,20}$"), this));
    ui->lineEdit_number->setValidator(new QRegExpValidator(QRegExp("^[0-9]+$"), this));
    ui->lineEdit_floorPrice->setValidator(new QRegExpValidator(QRegExp("^[0-9]+[\.]?[0-9]?$"), this));
    ui->lineEdit_description->setValidator(new QRegExpValidator(QRegExp("^[a-zA-Z0-9]{1,200}$"), this));
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
    if(this->isValid()) {
        cur->commodityName = ui->lineEdit_name->text();
        cur->description = ui->lineEdit_description->text();
        if(ui->radio_onAuction->isChecked()) cur->state = "onAuction";
        else cur->state = "removed";
        cur->number = ui->lineEdit_number->text().toInt();
        cur->floorPrice = ui->lineEdit_floorPrice->text().toFloat();
    }
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

bool CommodityBox::isValid()
{
    QString name = ui->lineEdit_name->text();
    if(name.length() >= 20) {
        QMessageBox::critical(this, "错误", "太长啦!");
        return false;
    }
    QString description = ui->lineEdit_description->text();
    if(description.length() >= 200) {
        QMessageBox::critical(this, "错误", "太长啦!");
        return false;
    }
    QString floorPrice = ui->lineEdit_floorPrice->text();
    qDebug() << floorPrice;
    if(!this->isDigitString(floorPrice)) {
        QMessageBox::critical(this, "错误", "请输入纯数字!");
        return false;
    }
    QString number = ui->lineEdit_number->text();
    if(!this->isDigitString(number)) {
        QMessageBox::critical(this, "错误", "请输入纯数字!");
        return false;
    }
    return true;
}
