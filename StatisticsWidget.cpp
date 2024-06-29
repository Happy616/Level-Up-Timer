// StatisticsWidget.cpp
#include "StatisticsWidget.h"
#include <QFile>
#include <QTextStream>
#include <QTime>

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    textEdit(new QTextEdit(this)),
    totalDurationLabel(new QLabel("计时的总时长: 00:00:00", this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    textEdit->setReadOnly(true); // 只读模式
    QFont font = textEdit->font();
    font.setFamily("微软雅黑"); // 选择一个支持中文的字体
    textEdit->setFont(font);
    layout->addWidget(textEdit);
    layout->addWidget(totalDurationLabel);
    setLayout(layout);
    loadStatisticsData();
}

void StatisticsWidget::loadStatisticsData() {
    QFile file("timing_data.txt");
    QTime totalDuration(0, 0, 0);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8"); // 显式设置文本流的编码为 UTF-8
        while (!in.atEnd()) {
            QString line = in.readLine();
            textEdit->append(line);

            // 分析每行数据并计算总时长
            QStringList parts = line.split(" ");
            if (parts.size() == 3) {
                QTime duration = QTime::fromString(parts[2], "HH:mm:ss");
                totalDuration = totalDuration.addSecs(QTime(0, 0, 0).secsTo(duration));
            }
        }
        file.close();
    }
    double total = totalDuration.hour() * 60.0 + totalDuration.minute() + totalDuration.second() / 60.0;
    QString m = QString::number(total, 'f', 2); // 保留两位小数
    totalDurationLabel->setText("你已经计时了 " + m + " 分钟啦！继续加油吧！");
}
void StatisticsWidget::reloadStatisticsData() {
    textEdit->clear(); // 清除当前显示的数据
    loadStatisticsData(); // 重新加载数据
}
