#ifndef USERHOME_H
#define USERHOME_H

#include <QWidget>
#include <QFile>
#include <QDebug>
#include "mapp.h"

namespace Ui {
class UserHome;
}

class UserHome : public QWidget
{
    Q_OBJECT

public:
    explicit UserHome(QWidget *parent = nullptr);
    void loadUserData();
    void rewrite();
    int getlevel(){ return level;}
    int getexp(){return exp;}
    QString getusername(){return user_name;}
    void setlevel(int n);
    ~UserHome();

private slots:
    void on_editbt_clicked();
    void on_pushButton_clicked();

private:
    Ui::UserHome *ui;
    QString user_name;
    QString user_gender;
    int level,exp;
    mapp *MAP;
};

#endif // USERHOME_H
