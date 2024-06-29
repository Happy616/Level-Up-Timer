// TaskItem.cpp
#include "TaskItem.h"
#include <QFile>
#include <QTextStream>

TaskItem::TaskItem(const QDateTime &time, const QString &subject, const QString &content,
                   int id, bool needwrite,QWidget *parent)
    : QWidget(parent), time_(time), subject_(subject), content_(content),
    id_(id){
    isFinished_ = false;
    if(needwrite)
        writeToFile();
}

void TaskItem::writeToFile() const {
    QFile file(QString("task_data/task_%1.txt").arg(id_));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        if(isFinished_==true) stream << QString("已完成") << Qt::endl;
        else stream << QString("未完成") << Qt::endl;
        stream << time_.toString("yyyy-MM-dd HH:mm:ss") << Qt::endl;
        stream << id_ << Qt::endl;
        stream << subject_ << Qt::endl;
        stream << content_ << Qt::endl;
        qDebug() << content_;
        file.close();
    }
}

void TaskItem::setFinished(bool finished) {
    isFinished_ = finished;
    qDebug() << "isFinished set as:" << isFinished_ ;
}
