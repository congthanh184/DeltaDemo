/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Mar 15 17:35:51 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *btLoadCircle;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QDoubleSpinBox *doubleBoxTheta1;
    QLabel *label_5;
    QDoubleSpinBox *doubleBoxTheta2;
    QLabel *label_6;
    QDoubleSpinBox *doubleBoxTheta3;
    QPushButton *btSetAngles;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label;
    QDoubleSpinBox *doubleBoxX;
    QLabel *label_2;
    QDoubleSpinBox *doubleBoxY;
    QLabel *label_3;
    QDoubleSpinBox *doubleBoxZ;
    QPushButton *btSetPosition;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(337, 353);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btLoadCircle = new QPushButton(centralWidget);
        btLoadCircle->setObjectName(QString::fromUtf8("btLoadCircle"));
        btLoadCircle->setGeometry(QRect(190, 60, 75, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 140, 131, 171));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        doubleBoxTheta1 = new QDoubleSpinBox(groupBox);
        doubleBoxTheta1->setObjectName(QString::fromUtf8("doubleBoxTheta1"));
        doubleBoxTheta1->setMinimumSize(QSize(70, 0));
        doubleBoxTheta1->setDecimals(3);
        doubleBoxTheta1->setMinimum(-360);
        doubleBoxTheta1->setMaximum(360);

        gridLayout->addWidget(doubleBoxTheta1, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        doubleBoxTheta2 = new QDoubleSpinBox(groupBox);
        doubleBoxTheta2->setObjectName(QString::fromUtf8("doubleBoxTheta2"));
        doubleBoxTheta2->setMinimumSize(QSize(70, 0));
        doubleBoxTheta2->setDecimals(3);
        doubleBoxTheta2->setMinimum(-360);
        doubleBoxTheta2->setMaximum(360);

        gridLayout->addWidget(doubleBoxTheta2, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        doubleBoxTheta3 = new QDoubleSpinBox(groupBox);
        doubleBoxTheta3->setObjectName(QString::fromUtf8("doubleBoxTheta3"));
        doubleBoxTheta3->setMinimumSize(QSize(70, 0));
        doubleBoxTheta3->setDecimals(3);
        doubleBoxTheta3->setMinimum(-360);
        doubleBoxTheta3->setMaximum(360);

        gridLayout->addWidget(doubleBoxTheta3, 2, 1, 1, 1);

        btSetAngles = new QPushButton(groupBox);
        btSetAngles->setObjectName(QString::fromUtf8("btSetAngles"));

        gridLayout->addWidget(btSetAngles, 3, 0, 1, 2);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 131, 134));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        doubleBoxX = new QDoubleSpinBox(groupBox_2);
        doubleBoxX->setObjectName(QString::fromUtf8("doubleBoxX"));
        doubleBoxX->setMinimumSize(QSize(70, 0));
        doubleBoxX->setDecimals(3);
        doubleBoxX->setMinimum(-300);
        doubleBoxX->setMaximum(300);

        gridLayout_2->addWidget(doubleBoxX, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        doubleBoxY = new QDoubleSpinBox(groupBox_2);
        doubleBoxY->setObjectName(QString::fromUtf8("doubleBoxY"));
        doubleBoxY->setMinimumSize(QSize(70, 0));
        doubleBoxY->setDecimals(3);
        doubleBoxY->setMinimum(-300);
        doubleBoxY->setMaximum(300);

        gridLayout_2->addWidget(doubleBoxY, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 2, 0, 1, 1);

        doubleBoxZ = new QDoubleSpinBox(groupBox_2);
        doubleBoxZ->setObjectName(QString::fromUtf8("doubleBoxZ"));
        doubleBoxZ->setMinimumSize(QSize(70, 0));
        doubleBoxZ->setDecimals(3);
        doubleBoxZ->setMinimum(-300);
        doubleBoxZ->setMaximum(300);

        gridLayout_2->addWidget(doubleBoxZ, 2, 1, 1, 1);

        btSetPosition = new QPushButton(groupBox_2);
        btSetPosition->setObjectName(QString::fromUtf8("btSetPosition"));

        gridLayout_2->addWidget(btSetPosition, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(doubleBoxX, doubleBoxY);
        QWidget::setTabOrder(doubleBoxY, doubleBoxZ);
        QWidget::setTabOrder(doubleBoxZ, doubleBoxTheta1);
        QWidget::setTabOrder(doubleBoxTheta1, doubleBoxTheta2);
        QWidget::setTabOrder(doubleBoxTheta2, doubleBoxTheta3);
        QWidget::setTabOrder(doubleBoxTheta3, btSetPosition);
        QWidget::setTabOrder(btSetPosition, btLoadCircle);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        btLoadCircle->setText(QApplication::translate("MainWindow", "Load Circle", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Theta 1", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Theta 2", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Theta 3", 0, QApplication::UnicodeUTF8));
        btSetAngles->setText(QApplication::translate("MainWindow", "Set Angles", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "GroupBox", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "x", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "y", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "z", 0, QApplication::UnicodeUTF8));
        btSetPosition->setText(QApplication::translate("MainWindow", "Set Position", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
