#include "TimerApp.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>

TimerApp::TimerApp(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    label(new QLabel("00:00:00", this)),
    pomodoroButton(new QPushButton("开始番茄钟", this)),
    customButton(new QPushButton("开始自定义计时", this)),
    pauseStartTime(QTime(0, 0, 0)),
    totalPauseDuration(QTime(0, 0, 0))
{
    setupUI();
    connect(timer, &QTimer::timeout, this, &TimerApp::updateTime);
    resize(400, 300);
}

void TimerApp::startPomodoro() {
    // 设定番茄钟时间为25分钟
    countdownTime.setHMS(0, 25, 0);
    duration = countdownTime;
    startTime = QTime::currentTime();
    label->setText(countdownTime.toString("hh:mm:ss"));
    timer->start(1000);
    pomodoroButton->setEnabled(false); // 禁用按钮以防止重复点击
    customButton->setEnabled(false); // 禁用自定义计时按钮
    timeEdit->setEnabled(false);
    pauseButton->setEnabled(true); // 启用暂停按钮
    pauseButton->setText("暂停");
    isPaused = false;
    stopButton->setEnabled(true);
}

void TimerApp::startCustomTimer() {
    // 使用 timeEdit 控件中的时间值
    countdownTime = timeEdit->time();
    duration = countdownTime;
    label->setText(countdownTime.toString("hh:mm:ss"));
    startTime = QTime::currentTime();
    timer->start(1000);
    pomodoroButton->setEnabled(false);
    customButton->setEnabled(false);
    timeEdit->setEnabled(false); // 禁用时间编辑控件以防止计时期间更改时间
    pauseButton->setEnabled(true); // 启用暂停按钮
    pauseButton->setText("暂停");
    isPaused = false;
    stopButton->setEnabled(true);
}

void TimerApp::updateTime() {
    countdownTime = countdownTime.addSecs(-1);
    if (countdownTime == QTime(0, 0, 0)) {
        timer->stop();
        label->setText("计时结束！");
        // 获取结束时间
        QTime endTime = QTime::currentTime();
        saveTimingData(startTime, endTime, duration); // 这里直接使用 duration 成员变量
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
        messageBox->setWindowTitle("计时结束");
        messageBox->setText("好棒！又完成了一个计时任务啦~");
        messageBox->setModal(false); // 设置为非模态
        messageBox->setWindowFlags(messageBox->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
        messageBox->show();
        messageBox->raise(); // 提升窗口层级
        messageBox->activateWindow(); // 激活窗口

        // 重新启用按钮
        pomodoroButton->setEnabled(true);
        customButton->setEnabled(true);
        stopButton->setEnabled(false);
        timeEdit->setEnabled(true);
    } else {
        label->setText(countdownTime.toString("hh:mm:ss"));
    }
}

void TimerApp::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 定义样式
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
                         "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                         "}";

    QString timeEditStyle = "QTimeEdit {"
                            "border: 2px solid pink;"
                            "border-radius: 5px;"
                            "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                            "font-size: 18px;"
                            "padding: 10px;"
                            "}";

    // 应用样式
    timeEdit = new QTimeEdit(this);
    timeEdit->setDisplayFormat("hh:mm:ss");
    timeEdit->setTime(QTime(0, 45, 0)); // 设置默认时间为 45 分钟
    timeEdit->setStyleSheet(timeEditStyle);
    layout->addWidget(timeEdit);

    label->setStyleSheet(labelStyle);
    layout->addWidget(label);

    pomodoroButton->setStyleSheet(buttonStyle);
    layout->addWidget(pomodoroButton);

    customButton->setStyleSheet(buttonStyle);
    layout->addWidget(customButton);

    pauseButton = new QPushButton("暂停", this);
    pauseButton->setStyleSheet(buttonStyle);
    layout->addWidget(pauseButton);

    stopButton = new QPushButton("结束计时", this);
    stopButton->setStyleSheet(buttonStyle);
    layout->addWidget(stopButton);
    stopButton->setEnabled(false);

    // 连接信号和槽
    connect(stopButton, &QPushButton::clicked, this, &TimerApp::stopTimer);
    connect(pauseButton, &QPushButton::clicked, this, &TimerApp::pauseOrResumeTimer);
    connect(pomodoroButton, &QPushButton::clicked, this, &TimerApp::startPomodoro);
    connect(customButton, &QPushButton::clicked, this, &TimerApp::startCustomTimer);

    setLayout(layout);
}

void TimerApp::pauseOrResumeTimer() {
    if (timer->isActive()) {
        timer->stop();
        pauseButton->setText("继续");
        isPaused = true;
        pauseStartTime = QTime::currentTime(); // 记录暂停开始时间
    } else if (isPaused) {
        QTime pauseEndTime = QTime::currentTime();
        int pauseDuration = pauseStartTime.secsTo(pauseEndTime);
        totalPauseDuration = totalPauseDuration.addSecs(pauseDuration); // 累加暂停时长
        timer->start(1000);
        pauseButton->setText("暂停");
        isPaused = false;
    }
}

void TimerApp::stopTimer() {
    if (timer->isActive() || isPaused) {
        QTime stopTime = QTime::currentTime();
        if (isPaused) {
            // 如果在暂停状态下结束计时，还需要计算最后一次暂停的时长
            int pauseDuration = pauseStartTime.secsTo(stopTime);
            totalPauseDuration = totalPauseDuration.addSecs(pauseDuration);
        }
        timer->stop();
        countdownTime.setHMS(0, 0, 0);
        label->setText("计时已结束");
        pomodoroButton->setEnabled(true);
        customButton->setEnabled(true);
        timeEdit->setEnabled(true);
        pauseButton->setEnabled(false); // 禁用暂停按钮
        stopButton->setEnabled(false); // 禁用结束按钮
        totalPauseDuration = QTime(0, 0, 0); // 重置累计的暂停时长
        isPaused = false;
    }
}

void TimerApp::saveTimingData(const QTime &startTime, const QTime &endTime, const QTime &originalDuration) {
    // 指定文件路径。如果您的应用程序在不同的目录中运行，请调整此路径。
    QString filePath = QDir::currentPath() + "/timing_data.txt";
    QFile file(filePath);
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out.setCodec("UTF-8");
    out << QStringLiteral("开始时间: ") << startTime.toString("HH:mm:ss") << " "
        << QStringLiteral("结束时间: ") << endTime.toString("HH:mm:ss") << " "
        << QStringLiteral("计时时长: ") << originalDuration.toString("HH:mm:ss") << "\n";
    file.close();
}
