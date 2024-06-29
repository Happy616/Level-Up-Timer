#include "userhome.h"
#include "ui_userhome.h"
#include "mapp.h"
#include <QString>
#include <QRect>
#include <QInputDialog>
#include <QDebug>
#include <QTime>
#include <QFile>
#include <QTextStream>

UserHome::UserHome(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserHome)
{
    ui->setupUi(this);
    ui->info_layout->setGeometry(QRect(200, 150, 400, 300));
    resize(400, 300);
    user_name = QString("default");
    user_gender = QString("default");
    level = 1;
    loadUserData();

    // 设置样式
    QString buttonStyle = "QPushButton {"
                          "border: 2px solid pink;"
                          "background-color: white;"
                          "color: black;"
                          "border-radius: 5px;"
                          "padding: 5px;"
                          "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                          "font-size: 16px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: pink;"
                          "color: white;"
                          "}";
    QString labelStyle = "QLabel {"
                         "color: black;"  // 将颜色设置为黑色
                         "font-size: 18px;"
                         "font-weight: bold;"
                         "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                         "}";

    ui->NameLabel->setStyleSheet(labelStyle);
    ui->GenderLabel->setStyleSheet(labelStyle);
    ui->LevelLabel->setStyleSheet(labelStyle);
    ui->name->setStyleSheet(labelStyle);
    ui->gender->setStyleSheet(labelStyle);

    ui->editbt->setStyleSheet(buttonStyle);
    ui->pushButton->setStyleSheet(buttonStyle);
}

UserHome::~UserHome()
{
    delete ui;
}

void UserHome::on_editbt_clicked()
{
    bool ok;
    QString tmp;
    tmp = QInputDialog::getText(this, tr("用户名设置"), tr("请输入用户名:"), QLineEdit::Normal, tr("admin"), &ok);
    if (!ok) {
        qDebug() << "no ok" << Qt::endl;
    } else {
        user_name = tmp;
        ui->name->setText(user_name);
    }

    QStringList items;
    items << tr("男") << tr("女") << tr("苦逼程序猿");
    tmp = QInputDialog::getItem(this, tr("性别输入"), tr("请选择性别:"), items, 0, false, &ok);
    if (!ok) {
        qDebug() << "error occurs!" << Qt::endl;
    } else {
        user_gender = tmp;
        ui->gender->setText(user_gender);
    }
    rewrite();
}

void UserHome::loadUserData()
{
    QFile file("user_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8

        if (file.size() != 0) { // 不是空文件
            user_name = in.readLine().trimmed();
            user_gender = in.readLine().trimmed();
            level = in.readLine().trimmed().toInt();
        }
        ui->name->setText(user_name);
        ui->gender->setText(user_gender);
        ui->LevelLabel->setText(QString("等级：%1").arg(level));

        file.close();
    } else {
        qDebug() << "open user_data.txt failed";
    }

    QFile file2("timing_data.txt");
    QTime totalDurationn(0, 0, 0);
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file2);
        in.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8
        while (!in.atEnd()) {
            QString line = in.readLine();

            // 分析每行数据并计算总时长
            QStringList parts = line.split(" ");
            if (parts.size() == 3) {
                QTime duration = QTime::fromString(parts[2], "HH:mm:ss");
                totalDurationn = totalDurationn.addSecs(QTime(0, 0, 0).secsTo(duration));
            }
        }
        file2.close();
    } else {
        qDebug() << "open timing_data.txt failed";
    }

    int total = totalDurationn.hour() * 60 * 60 + totalDurationn.minute() * 60 + totalDurationn.second();
    setlevel(total / 300);
    exp = total % 300;
    ui->LevelLabel->setText(QString("等级：%1").arg(level));
}

void UserHome::setlevel(int n)
{
    level = n;
    ui->LevelLabel->setText(QString("等级：%1").arg(level));
    rewrite();
}

void UserHome::rewrite()
{
    QFile file("user_data.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8

        out << user_name << Qt::endl;
        out << user_gender << Qt::endl;
        out << level << Qt::endl;

        file.close();
    } else {
        qDebug() << "open user_data.txt failed";
    }
}

void UserHome::on_pushButton_clicked()
{
    loadUserData();
    MAP = new mapp(nullptr, user_name, level, exp);
    MAP->setAttribute(Qt::WA_DeleteOnClose);
    MAP->loadmappdata();
}
