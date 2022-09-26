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

signals:
    void exitSignal();
};

#endif // COMMODITYBOX_H
