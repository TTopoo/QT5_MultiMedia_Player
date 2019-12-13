/********************************************************************************
** Form generated from reading UI file 'MP.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MP_H
#define UI_MP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <customslider.h>

QT_BEGIN_NAMESPACE

class Ui_MP
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    CustomSlider *horizontalSlider;
    QPushButton *pushButton_Volume;
    QPushButton *pushButton_Player;
    QPushButton *pushButton_Open;
    QPushButton *pushButton_Speed;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MP)
    {
        if (MP->objectName().isEmpty())
            MP->setObjectName(QString::fromUtf8("MP"));
        MP->resize(502, 333);
        centralWidget = new QWidget(MP);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSlider = new CustomSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);

        pushButton_Volume = new QPushButton(centralWidget);
        pushButton_Volume->setObjectName(QString::fromUtf8("pushButton_Volume"));

        horizontalLayout->addWidget(pushButton_Volume);

        pushButton_Player = new QPushButton(centralWidget);
        pushButton_Player->setObjectName(QString::fromUtf8("pushButton_Player"));

        horizontalLayout->addWidget(pushButton_Player);

        pushButton_Open = new QPushButton(centralWidget);
        pushButton_Open->setObjectName(QString::fromUtf8("pushButton_Open"));

        horizontalLayout->addWidget(pushButton_Open);

        pushButton_Speed = new QPushButton(centralWidget);
        pushButton_Speed->setObjectName(QString::fromUtf8("pushButton_Speed"));

        horizontalLayout->addWidget(pushButton_Speed);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addLayout(verticalLayout_2);

        MP->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MP);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 502, 23));
        MP->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MP);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MP->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MP);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MP->setStatusBar(statusBar);

        retranslateUi(MP);

        QMetaObject::connectSlotsByName(MP);
    } // setupUi

    void retranslateUi(QMainWindow *MP)
    {
        MP->setWindowTitle(QApplication::translate("MP", "MP", nullptr));
        label->setText(QApplication::translate("MP", "\350\257\267\346\211\223\345\274\200\350\247\206\351\242\221\346\226\207\344\273\266", nullptr));
        pushButton_Volume->setText(QApplication::translate("MP", "\351\237\263\351\207\217", nullptr));
        pushButton_Player->setText(QApplication::translate("MP", "\346\222\255\346\224\276", nullptr));
        pushButton_Open->setText(QApplication::translate("MP", "\346\211\223\345\274\200", nullptr));
        pushButton_Speed->setText(QApplication::translate("MP", "\345\200\215\351\200\237*1", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MP: public Ui_MP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MP_H
