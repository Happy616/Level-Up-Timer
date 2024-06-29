#include "board.h"
#include "ui_board.h"
#include <QInputDialog>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QCoreApplication>
#include <QMessageBox>

Board::Board(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Board)
{
    ui->setupUi(this);
    resize(400, 300);
    loadBoardData();

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
                         "color: black;"
                         "font-size: 16px;"
                         "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                         "}";

    QString textEditStyle = "QTextEdit {"
                            "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                            "font-size: 16px;"
                            "}";

    ui->addfeelingsbt->setStyleSheet(buttonStyle);
    ui->clearbt->setStyleSheet(buttonStyle);
    ui->mainBoard->setStyleSheet(textEditStyle);
}

Board::~Board()
{
    delete ui;
}

void Board::on_addfeelingsbt_clicked()
{
    QInputDialog dlg;
    QString raw = dlg.getMultiLineText(this, tr("我的心情"), tr("直抒胸臆吧！"));
    QStringList proc = raw.split('\n');
    QDateTime curdatetime = QDateTime::currentDateTime();

    QFile file("board_data.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8

        out << curdatetime.toString("yyyy-MM-dd HH:mm:ss") << Qt::endl;
        for (int i = 0; i < proc.size(); i++) {
            out << proc[i] << Qt::endl;
        }

        file.close();
    }

    reloadBoardData();
}

void Board::loadBoardData() {
    QFile file("board_data.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8
        while (!in.atEnd()) {
            QString line = in.readLine();
            ui->mainBoard->append(line);
        }
        file.close();
    }
}

void Board::reloadBoardData() {
    ui->mainBoard->clear(); // 清除当前显示的数据
    loadBoardData(); // 重新加载数据
}

void Board::on_clearbt_clicked()
{
    int ret = QMessageBox::question(this,
                                    tr("警告"),
                                    tr("你确定要继续清空操作吗？"),
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::No); // 默认按钮为“No”

    if (ret == QMessageBox::No) {
        return;
    }

    QFile file("board_data.txt");
    // 打开文件用于写入和截断
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        // 清空文件内容
        file.resize(0);
        file.close(); // 关闭文件
    } else {
        qDebug() << "Unable to open file for truncating";
    }

    reloadBoardData();
}
