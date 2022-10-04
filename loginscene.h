#ifndef LOGINSCENE_H
#define LOGINSCENE_H

#include <QMainWindow>
#include <cstdio>
#include <string>
#include "config.h"
#include "usercenter.h"
#include "auctionsystem.h"
#include "admincenter.h"
QT_BEGIN_NAMESPACE
namespace Ui { class LoginScene; }
QT_END_NAMESPACE

class LoginScene : public QMainWindow
{
    Q_OBJECT
    userInfo *userInfoList[USERCAPACITY];// 预设用户量上限为20
    userInfo *curUser;//记录当前登录的用户指针
    int idx = 0; //记录当前存在的用户数量, 数组记得要减1!
    AuctionSystem *auctionSystem;
public:
    LoginScene(QWidget *parent = nullptr);
    ~LoginScene();
    void loadUserInfo(); //在初始化的时候从文件中读取信息或创建新文件
    userInfo* createUser(QString &buffer); //接收完整的一行信息并创建一个用户结构体, 返回其地址(初始化时读取)
    void userRegister();
    QString userRegisterCheck(const QString& username); //检查用户名是否重复
    void userLogin();
    userInfo *userLoginCheck(const QString &username, const QString &password);
    void adminLogin();
private:
    Ui::LoginScene *ui;
};
#endif // LOGINSCENE_H
