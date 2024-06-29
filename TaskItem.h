// TaskItem.h
#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>
#include <QDateTime>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDebug>

class TaskItem : public QWidget {
    Q_OBJECT

public:
    TaskItem(const QDateTime &time, const QString &subject, const QString &content,
             int id, bool needwrite,QWidget *parent = nullptr);

    // 成员变量的访问接口
    QDateTime getTime() const { return time_; }
    QString getSubject() const { return subject_; }
    QString getContent() const { return content_; }
    int getId() const { return id_; }
    bool isFinished() const { return isFinished_; }

    // 改变 isFinished 值的接口
    void setFinished(bool finished);
    void writeToFile() const; // 写入成员变量到文本文件

private:
    QDateTime time_;
    QString subject_;
    QString content_;
    int id_;
    bool isFinished_;

};

#endif // TASKITEM_H

