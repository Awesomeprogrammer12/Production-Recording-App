#include "statisticspage.h"

StatisticsPage::StatisticsPage(QWidget *parent) : QWidget(parent)
{
    mainUI = new QQuickWidget(this);

    // These two lines are the most important for filling
    mainUI->setResizeMode(QQuickWidget::SizeRootObjectToView);
    mainUI->setSource(QUrl("qrc:/qml/statistics.qml"));

    // Make sure the QQuickWidget itself expands fully
    mainUI->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);   // remove any padding
    mainLayout->setSpacing(0);

    mainLayout->addWidget(mainUI, 1);             // stretch factor 1 = take all space

    setLayout(mainLayout);
}
