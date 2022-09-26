#include "loginscene.h"
#include "ui_loginscene.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

LoginScene::LoginScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginScene)
{
    ui->setupUi(this);
    this->setWindowTitle("登录界面");
    this->setMinimumSize(400, 800);
    this->setWindowOpacity(0.95);
    connect(ui->loginBtn_user, &QPushButton::clicked, [=](){
        qDebug() << "user loginBtn clicked!";
        this->userLogin();
    });
    connect(ui->loginBtn_admin, &QPushButton::clicked, [=](){
       qDebug() << "admin loginBtn clicked!";
       this->adminLogin();
    });
    connect(ui->registBtn, &QPushButton::clicked, [=](){
        qDebug() << "registBtn clicked!";
        this->userRegister();
    });
    connect(ui->exitBtn_user, &QPushButton::clicked, [=](){
        this->close();
    });
    connect(ui->exitBtn_admin, &QPushButton::clicked, [=](){
        this->close();
    });
    connect(ui->exitBtn_regist, &QPushButton::clicked, [=](){
        this->close();
    });
    this->loadUserInfo();
    this->auctionSystem = new AuctionSystem(this->userInfoList, this->idx);
}

LoginScene::~LoginScene()
{
    delete ui;
    // 写文件
    QString filePath = QDir::currentPath() + "/res/userInfo.txt";//userInfo文件路径
    QFile fout(filePath);
    fout.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream foutWrite(&fout);
    foutWrite << "userID,username,password,phoneNumber,address,balance,userState" << endl;
    for(int i = 0; i < this->idx; i++) {
        if(userInfoList[i] != nullptr) {
            qDebug() << "delete: " << userInfoList[i]->userID << QString::number(userInfoList[i]->balance, 'f', 1);
            foutWrite << userInfoList[i]->userID << ",";
            foutWrite << userInfoList[i]->username << ",";
            foutWrite << userInfoList[i]->password << ",";
            foutWrite << userInfoList[i]->phonenumber << ",";
            foutWrite <<  userInfoList[i]->address << ",";
            foutWrite <<  QString::number(userInfoList[i]->balance, 'f', 1) << ",";
            foutWrite << userInfoList[i]->userState << endl;
            delete userInfoList[i];
        }
    }
    fout.close();
    delete auctionSystem;
}

void LoginScene::loadUserInfo() {
    qDebug() << QDir::currentPath();
    QString filePath = QDir::currentPath() + "/res/userInfo.txt";//userInfo文件路径
    QFile fin(filePath);
    if (!fin.open(QIODevice::ReadOnly)) {
        qDebug() << "file not exists!";
        QFile fout(filePath);
        fout.open(QIODevice::WriteOnly);
        QTextStream foutWrite(&fout);
        QString head = "userID,username,password,phoneNumber,address,balance,userState";
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
        if(this->idx >= USERCAPACITY) {
            printf("out of capacity!\n");
        }
        else {
            this->userInfoList[this->idx++] = this->createUser(buffer);
//            std::cout << this->userInfoList[this->idx-1]->username << this->userInfoList[this->idx-1]->password << std::endl;
        }
    }
    fin.close();
}

userInfo* LoginScene::createUser(QString &buffer) {
    if(buffer.isEmpty()) {
        printf("error! no input!\n");
        return nullptr;
    }
    //create a new userInfo struct
    userInfo * cur = new userInfo;
    //split
    QStringList list = buffer.split(",");
    cur->userID = list[0];
    cur->username = list[1];
    cur->password = list[2];
    cur->phonenumber = list[3];
    cur->address = list[4];
    cur->balance = list[5].toFloat();
    cur->userState = list[6];
    qDebug() << cur->userID << " " << cur->username << " " << cur->balance;
    return cur;
}

void LoginScene::userRegister()
{
    QString username = ui->lineEdit_registName->text();
    QString password = ui->lineEdit_registPwd->text();
    QString phoneNumber = ui->lineEdit_registPhoneNumber->text();
    QString address = ui->lineEdit_registAddress->text();
    QString userID = this->userRegisterCheck(username);
    if(userID.isEmpty()) {
        QMessageBox::critical(this, "注册失败", "用户名已存在!");
        ui->lineEdit_registName->clear();
        ui->lineEdit_registPwd->clear();
        ui->lineEdit_registPhoneNumber->clear();
        ui->lineEdit_registAddress->clear();
        return ;
    }
    if(this->idx >= USERCAPACITY) {
        QMessageBox::critical(this, "注册失败", "超出注册用户上限!");
        ui->lineEdit_registName->clear();
        ui->lineEdit_registPwd->clear();
        ui->lineEdit_registPhoneNumber->clear();
        ui->lineEdit_registAddress->clear();
        return ;
    }
    else {
        QMessageBox::information(this, "注册成功", "恭喜你, 注册成功!");
        userInfo *cur = new userInfo;
        cur->userID = userID;
        cur->username = username;
        cur->password = password;
        cur->phonenumber = phoneNumber;
        cur->address = address;
        cur->balance = 0.0;
        cur->userState = "active";
        this->userInfoList[this->idx++] = cur;
    }
}

QString LoginScene::userRegisterCheck(const QString &username)
{
    QString ret;
    for(int i = 0; i < this->idx; i++) {
        if(username == this->userInfoList[i]->username) {
            return ret;
        }
    }
    //说明不重复, 指派一个userID
    QString num = QString::number(this->idx+1);
    if(num.length() == 1) {
        ret += "U00";
    }
    else if(num.length() == 2) {
        ret += "U0";
    }
    else {
        ret += "U";
    }
    ret += num;
    return ret;
}

void LoginScene::userLogin()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_userpwd->text();
    this->curUser = this->userLoginCheck(username, password);
    if(this->curUser != nullptr) {
        if(this->curUser->userState == "inactive") {
            QMessageBox::warning(this, "登录失败", "对不起, 您已被封禁!");
            ui->lineEdit_username->clear();
            ui->lineEdit_userpwd->clear();
            return ;
        }
        QMessageBox::about(this, "登录成功", "恭喜你, 登录成功!");
        qDebug() << "进入用户界面";
        UserCenter *usercenter = new UserCenter(this, this->curUser, this->auctionSystem);
        usercenter->show();
//        this->hide();
    }
    else {
        QMessageBox::warning(this, "登录失败", "用户账号/密码错误!");
    }
    ui->lineEdit_username->clear();
    ui->lineEdit_userpwd->clear();
}

userInfo *LoginScene::userLoginCheck(const QString &username, const QString &password)
{
    for(int i = 0; i < this->idx; i++) {
        if(username == this->userInfoList[i]->username && password == this->userInfoList[i]->password) {
            return this->userInfoList[i];
        }
    }
    return nullptr;
}

void LoginScene::adminLogin()
{
    QString adminID = ui->lineEdit_adminName->text();
    QString adminPwd = ui->lineEdit_adminPwd->text();
    if(adminID == "admin" && adminPwd == "root") {
        QMessageBox::about(this, "管理员登录", "登录成功!");
        qDebug() << "进入管理员中心";
        AdminCenter *adminCenter = new AdminCenter(nullptr, this->auctionSystem);
        adminCenter->show();
    }
    else {
        QMessageBox::warning(this, "管理员登录", "管理员账号/密码输入错误!");
    }
    ui->lineEdit_adminName->clear();
    ui->lineEdit_adminPwd->clear();
}

