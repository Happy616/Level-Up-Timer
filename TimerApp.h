#ifndef TIMERAPP_H
#define TIMERAPP_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QSpinBox>
#include <QTimeEdit>

class TimerApp : public QWidget {
    Q_OBJECT

public:
    explicit TimerApp(QWidget *parent = nullptr);

private slots:
    void startPomodoro();
    void startCustomTimer();
    void updateTime();
    void pauseOrResumeTimer();
    void stopTimer();

private:
    QTimer *timer;
    QLabel *label;
    QPushButton *pomodoroButton;
    QPushButton *customButton;
    QPushButton *pauseButton; // 暂停/继续按钮
    QPushButton *stopButton; // 新增的提前结束按钮
    bool isPaused; // 暂停状态标志
    QTime countdownTime;
    QTimeEdit *timeEdit;
    void setupUI();
    QTime duration; // 添加这个变量来跟踪计时的时长
    void saveTimingData(const QTime &startTime, const QTime &endTime, const QTime &duration);
    QTime startTime;
    QTime pauseStartTime; // 暂停开始时间
    QTime totalPauseDuration; // 累计的暂停时长
};

#endif // TIMERAPP_H
