#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStackedWidget>
#include "widget.h"
#include <QtQuickWidgets/QQuickWidget>

class StatisticsPage:public QWidget{
public:
    explicit StatisticsPage(QWidget *parent = nullptr);

public:
    //Widget *root = qobject_cast<Widget*>(this->parentWidget());
    QQuickWidget *mainUI;
    QVBoxLayout *mainLayout;
//public slots:
};

#endif // STATISTICSPAGE_H
