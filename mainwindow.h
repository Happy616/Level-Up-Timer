#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include "TimerApp.h"  // 假设 TimerApp 是番茄钟界面的类
#include "StatisticsWidget.h"  // 假设 StatisticsWidget 是统计数据界面的类
#include "userhome.h"
#include "board.h"
#include "Schedule.h"
#include "mapp.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openPomodoroTimer();
    void openStatisticsView();  // 新增槽函数，用于打开统计数据界面
    void openUserhomeView();
    void openBoardView();
    void openScheduleView();

private:
    QStackedWidget *stackedWidget;
    TimerApp *pomodoroTimer;  // 番茄钟界面
    StatisticsWidget *statisticsView;  // 统计数据界面
    QPushButton *pomodoroButton;  // 打开番茄钟界面的按钮
    QPushButton *statisticsButton;  // 打开统计数据界面的按钮
    // 如果有其他功能，可以继续添加其他界面指针和按钮
    UserHome *user;
    QPushButton *userhomeButton;
    Board *board;
    QPushButton *boardButton;
    Schedule *schedule;
    QPushButton *scheduleButton;
};

#endif // MAINWINDOW_H
