#ifndef MAPP_H
#define MAPP_H

#include <QObject>
#include <QQuickItem>
#include <QWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include "ui_mapp.h"

namespace Ui {
class mapp;
}

class mapp : public QWidget
{
    Q_OBJECT
public:
    explicit mapp(QWidget *parent = nullptr,QString username_=QString("default"),int level_=1,int exp_=0);
    void loadmappdata();

private slots:
    void on_place1_clicked();
    void on_place2_clicked();
    void on_place3_clicked();
    void on_place4_clicked();
    void on_place5_clicked();
    void on_place6_clicked();
    void startRotationAnimation();
    void on_pushButton_clicked();

private:
    Ui::mapp *ui;
    int level;
    QString user_name;
    QString place;
    QPropertyAnimation *qanme,*qanop;
};

#endif // MAPP_H
