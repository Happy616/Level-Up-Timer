#include "mainwindow.h"
#include "qboxlayout.h"
#include <QTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // 创建堆栈小部件
    stackedWidget = new QStackedWidget(this);

    // 创建番茄钟界面
    pomodoroTimer = new TimerApp();
    stackedWidget->addWidget(pomodoroTimer);
    // 创建其他功能界面
    // ...

    // 创建功能选择按钮
    pomodoroButton = new QPushButton("番茄钟", this);
    connect(pomodoroButton, &QPushButton::clicked, this, &MainWindow::openPomodoroTimer);

    // 设置按钮样式
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
    pomodoroButton->setStyleSheet(buttonStyle);

    // 创建其他功能的按钮
    // ...
    // 设置功能选择按钮的布局
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(pomodoroButton);
    // 添加其他功能的按钮到布局
    // ...

    // 创建统计界面
    statisticsView = new StatisticsWidget();  // 使用成员变量
    stackedWidget->addWidget(statisticsView);
    // ...
    // 创建并添加统计数据查看按钮
    statisticsButton = new QPushButton("统计数据查看", this);
    connect(statisticsButton, &QPushButton::clicked, this, &MainWindow::openStatisticsView);
    statisticsButton->setStyleSheet(buttonStyle);
    buttonLayout->addWidget(statisticsButton);

    //LIN_YI down here
    //账户信息相关
    user = new UserHome();
    stackedWidget->addWidget(user);
    userhomeButton = new QPushButton("我的家", this);
    buttonLayout->addWidget(userhomeButton);
    connect(userhomeButton, &QPushButton::clicked, this, &MainWindow::openUserhomeView);
    userhomeButton->setStyleSheet(buttonStyle);

    //心情日志相关
    board = new Board();
    stackedWidget->addWidget(board);
    boardButton = new QPushButton("心情语录", this);
    buttonLayout->addWidget(boardButton);
    connect(boardButton, &QPushButton::clicked, this, &MainWindow::openBoardView);
    boardButton->setStyleSheet(buttonStyle);

    schedule = new Schedule();
    stackedWidget->addWidget(schedule);
    scheduleButton = new QPushButton("日程规划", this);
    buttonLayout->addWidget(scheduleButton);
    connect(scheduleButton, &QPushButton::clicked, this, &MainWindow::openScheduleView);
    scheduleButton->setStyleSheet(buttonStyle);

    //LIN_YI up here

    // 创建一个包含所有按钮的小部件
    QWidget *buttonWidget = new QWidget(this);
    buttonWidget->setLayout(buttonLayout);
    // 创建一个水平布局来放置按钮小部件和堆栈小部件
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(buttonWidget);
    mainLayout->addWidget(stackedWidget);

    // 创建中心小部件并设置布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    resize(400, 300);

    // 应用整体风格
    QString mainStyle = "QWidget {"
                        "background-color: #FFF0F5;"  // 浅粉红色背景
                        "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                        "}";
    centralWidget->setStyleSheet(mainStyle);
}

void MainWindow::openPomodoroTimer() {
    // 切换到番茄钟界面
    stackedWidget->setCurrentWidget(pomodoroTimer);
}

// 添加其他功能的槽函数实现
// ...
void MainWindow::openStatisticsView() {
    statisticsView->reloadStatisticsData(); // 在显示统计数据之前重新加载数据
    stackedWidget->setCurrentWidget(statisticsView);
}

void MainWindow::openUserhomeView() {
    stackedWidget->setCurrentWidget(user);
}

void MainWindow::openBoardView() {
    stackedWidget->setCurrentWidget(board);
}

void MainWindow::openScheduleView() {
    stackedWidget->setCurrentWidget(schedule);
}
