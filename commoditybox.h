#ifndef COMMODITYBOX_H
#define COMMODITYBOX_H

#include <QWidget>
#include "config.h"

namespace Ui {
class CommodityBox;
}

class CommodityBox : public QWidget
{
    Q_OBJECT
    commodityInfo* cur;
public:
    CommodityBox(QWidget *parent, commodityInfo* cur);
    ~CommodityBox();
    void modifyCommodity();
    void showCommodity();
private:
    Ui::CommodityBox *ui;
    bool isDigitString(const QString& src) {
        const char *s = src.toUtf8().data();
        while(*s && ((*s>='0' && *s<='9') || *s == '.'))s++;
        return !bool(*s);
    }
    bool isValid();
signals:
    void exitSignal();
};

#endif // COMMODITYBOX_H
