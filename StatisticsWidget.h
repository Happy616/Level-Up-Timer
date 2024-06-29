// StatisticsWidget.h
#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextEdit>

class StatisticsWidget : public QWidget {
    Q_OBJECT

public:
    explicit StatisticsWidget(QWidget *parent = nullptr);
    void loadStatisticsData();
    void reloadStatisticsData();

private:
    QTextEdit *textEdit;
    QLabel *totalDurationLabel;
};

#endif // STATISTICSWIDGET_H
