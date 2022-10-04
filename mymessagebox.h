#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>
#include "config.h"
#include "auctionsystem.h"
namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QWidget
{
    Q_OBJECT
    commodityInfo* cur;
    AuctionSystem * auctionSystem;
    userInfo *curUser;
    bool isDigitString(const QString& src) {
        const char *s = src.toUtf8().data();
        while(*s && ((*s>='0' && *s<='9') || *s == '.'))s++;
        return !bool(*s);
    }
public:
    explicit MyMessageBox(QWidget *parent, userInfo* curUser, commodityInfo* cur, AuctionSystem* auctionSystem);
    ~MyMessageBox();
    void showCommodityInfo();
    void purchase();

private:
    Ui::MyMessageBox *ui;
signals:
    void exitSignal();
};

#endif // MYMESSAGEBOX_H
