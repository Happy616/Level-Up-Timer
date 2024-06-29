// Schedule.h
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QTextBrowser>
#include "TaskItem.h"

class Schedule : public QWidget {
    Q_OBJECT

public:
    explicit Schedule(QWidget *parent = nullptr);
    void setidIT(int num);
    void loadTaskData();
    friend QString processFile(Schedule *sche,const QString &filePath);

private slots:
    void onAddTask();
    void onRemoveTask();
    void onTaskDoubleClicked(QListWidgetItem *item);

private:
    int IDiter;
    QListWidget *taskListWidget_;
    QPushButton *addTaskButton_;
    QPushButton *removeTaskButton_;

    void setupUI();
};

#endif // SCHEDULE_H
