#include "Schedule.h"
#include "TaskDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QCheckBox>
#include <QLabel>
#include <QTextBrowser>
#include <QDialogButtonBox>

// Schedule构造函数
Schedule::Schedule(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    loadTaskData();
}

void Schedule::setupUI() {
    // 创建控件
    taskListWidget_ = new QListWidget(this);
    addTaskButton_ = new QPushButton("添加", this);
    removeTaskButton_ = new QPushButton("删除", this);

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

    addTaskButton_->setStyleSheet(buttonStyle);
    removeTaskButton_->setStyleSheet(buttonStyle);

    // 设置列表样式
    QString listWidgetStyle = "QListWidget {"
                              "border: 2px solid pink;"
                              "border-radius: 5px;"
                              "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                              "font-size: 16px;"
                              "}";

    taskListWidget_->setStyleSheet(listWidgetStyle);

    // 创建展示平台
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(taskListWidget_);
    layout->addWidget(addTaskButton_);
    layout->addWidget(removeTaskButton_);

    // 建立槽函数
    connect(addTaskButton_, &QPushButton::clicked, this, &Schedule::onAddTask);
    connect(removeTaskButton_, &QPushButton::clicked, this, &Schedule::onRemoveTask);
    connect(taskListWidget_, &QListWidget::itemDoubleClicked, this, &Schedule::onTaskDoubleClicked);
}

void Schedule::onAddTask() {
    // 创建自定义TaskItem
    TaskDialog tdlg;
    tdlg.setStyleSheet("QDialog {"
                       "background-color: #FFF0F5;"  // 浅粉色背景
                       "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                       "font-size: 16px;"
                       "border: 2px solid pink;"
                       "border-radius: 10px;"
                       "}");

    if (tdlg.exec() == QDialog::Accepted) {
        TaskItem *newTaskItem = new TaskItem(tdlg.getTime(), tdlg.getTopic(), tdlg.getContent(), IDiter++, true);
        // 创建用于列表跟踪的item
        QListWidgetItem *item = new QListWidgetItem(newTaskItem->getSubject() + (newTaskItem->isFinished() ? "(已完成)" : "(未完成)"));
        taskListWidget_->addItem(item);
        // 连接控件
        taskListWidget_->setItemWidget(item, newTaskItem);
    }
}

void Schedule::onRemoveTask() {
    QListWidgetItem *selectedItem = taskListWidget_->currentItem();
    if (selectedItem) {
        int tempid = qobject_cast<TaskItem *>(taskListWidget_->itemWidget(selectedItem))->getId();
        if (QFile::remove(QString("task_data/task_%1.txt").arg(tempid))) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("操作成功");
            msgBox.setText("任务已被删除。");
            msgBox.setStyleSheet("QMessageBox {"
                                 "background-color: #FFF0F5;"  // 浅粉色背景
                                 "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                                 "font-size: 16px;"
                                 "border: 2px solid pink;"
                                 "border-radius: 10px;"
                                 "}"
                                 "QPushButton {"
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
                                 "}");
            msgBox.exec();
        } else {
            QMessageBox msgBox;
            msgBox.setWindowTitle("操作失败");
            msgBox.setText("文件删除失败。");
            msgBox.setStyleSheet("QMessageBox {"
                                 "background-color: #FFF0F5;"  // 浅粉色背景
                                 "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                                 "font-size: 16px;"
                                 "border: 2px solid pink;"
                                 "border-radius: 10px;"
                                 "}"
                                 "QPushButton {"
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
                                 "}");
            msgBox.exec();
        }
        taskListWidget_->takeItem(taskListWidget_->row(selectedItem));
    }
}

void Schedule::onTaskDoubleClicked(QListWidgetItem *item) {
    if (item == nullptr) return;

    TaskItem *taskItem = qobject_cast<TaskItem *>(taskListWidget_->itemWidget(item));
    if (taskItem) {
        QDialog *dialog = new QDialog(this);
        dialog->setWindowTitle("任务详情");
        dialog->setAttribute(Qt::WA_DeleteOnClose);

        QVBoxLayout *layout = new QVBoxLayout(dialog);

        // 显示 TaskItem 信息
        QLabel *timeLabel = new QLabel("时间：" + taskItem->getTime().toString("yyyy-MM-dd HH:mm:ss"));
        QLabel *subjectLabel = new QLabel("主题：" + taskItem->getSubject());
        QLabel *contentLabel = new QLabel("内容：");
        QTextBrowser *contentBrowser = new QTextBrowser;
        contentBrowser->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
        contentBrowser->setText(taskItem->getContent());
        QLabel *finishedLabel = new QLabel("下面是完成情况，完成勾选确定");

        layout->addWidget(timeLabel);
        layout->addWidget(subjectLabel);
        layout->addWidget(contentLabel);
        layout->addWidget(contentBrowser);
        layout->addWidget(finishedLabel);

        // 设置样式
        QString labelStyle = "QLabel {"
                             "color: black;"  // 将颜色设置为黑色
                             "font-size: 16px;"
                             "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                             "}";

        timeLabel->setStyleSheet(labelStyle);
        subjectLabel->setStyleSheet(labelStyle);
        contentLabel->setStyleSheet(labelStyle);
        finishedLabel->setStyleSheet(labelStyle);

        // 任务完成状态的复选框
        QCheckBox *finishedCheckbox = new QCheckBox;
        finishedCheckbox->setChecked(taskItem->isFinished());
        layout->addWidget(finishedCheckbox);

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        connect(buttonBox, &QDialogButtonBox::accepted, dialog, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, dialog, &QDialog::reject);
        layout->addWidget(buttonBox);

        QString buttonBoxStyle = "QDialogButtonBox {"
                                 "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                                 "font-size: 16px;"
                                 "}"
                                 "QPushButton {"
                                 "border: 2px solid pink;"
                                 "background-color: white;"
                                 "color: black;"
                                 "border-radius: 5px;"
                                 "padding: 5px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: pink;"
                                 "color: white;"
                                 "}";

        buttonBox->setStyleSheet(buttonBoxStyle);
        dialog->setStyleSheet("QDialog {"
                              "background-color: #FFF0F5;"  // 浅粉色背景
                              "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                              "font-size: 16px;"
                              "border: 2px solid pink;"
                              "border-radius: 10px;"
                              "}");

        dialog->setLayout(layout);
        if (dialog->exec() == QDialog::Accepted) {
            taskItem->setFinished(finishedCheckbox->checkState()); // 根据勾选框修改完成情况
            taskItem->writeToFile(); // 重写到文件
            item->setText(taskItem->getSubject() + (taskItem->isFinished() ? "(已完成)" : "(未完成)")); // 实时展示到窗口
        }
    }
}

void Schedule::setidIT(int num) {
    IDiter = num;
}

void Schedule::loadTaskData() {
    QStringList Out, In;
    int maxid = 0;

    // 获取当前工作目录
    QDir currentDir = QDir::current();
    // 检查文件夹
    QString folderName = "task_data";
    if (!currentDir.exists(folderName)) {
        // 如果文件夹不存在，创建它
        if (currentDir.mkdir(folderName)) {
            qDebug() << "Folder created:" << folderName;
        } else {
            qDebug() << "Failed to create folder:" << folderName;
        }
    } else {
        qDebug() << "Folder already exists:" << folderName;
    }
    // 对txt逐个处理
    QDir dir(folderName);
    // 过滤只获取.txt文件
    QStringList filters;
    filters << "*.txt";
    // 遍历文件夹中的所有.txt文件
    foreach (const QString &file, dir.entryList(filters, QDir::Files)) {
        QString filePath = dir.filePath(file);
        QString result = processFile(this, filePath); // 处理每个文件

        QStringList parts = result.split('-');

        if (parts.size() == 3) {
            QString action = parts[0];
            QString data = parts[1];
            bool ok;
            int id = parts[2].toInt(&ok);

            if (ok) { // 确保转换为整数成功
                if (action == "O") {
                    Out.append(data); // 将数据添加到 Out
                } else if (action == "I") {
                    In.append(data); // 将数据添加到 In
                }

                // 更新 maxid
                if (id > maxid) {
                    maxid = id;
                }
            }
        }
    }

    // 更新IDiter
    setidIT(maxid + 1);
    // 发出提示
    QMessageBox messageBox;
    messageBox.setWindowTitle("任务提醒");
    messageBox.setMinimumSize(400, 200); // 设置最小大小

    // 设置文本，这里使用了 QString::fromUtf8() 来确保文本正确显示
    QString text = QString::fromUtf8("<html><head/><body>"
                                     "<p>已过期:</p>"
                                     "<p>%1</p>"
                                     "<p>待完成:</p>"
                                     "<p>%2</p>"
                                     "</body></html>")
                       .arg(Out.join("<br/>"), In.join("<br/>"));
    messageBox.setText(text);

    // 设置对话框样式
    QString messageBoxStyle = "QMessageBox {"
                              "font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
                              "font-size: 16px;"
                              "background-color: #FFF0F5;"  // 浅粉色背景
                              "border: 2px solid pink;"
                              "border-radius: 10px;"
                              "}"
                              "QPushButton {"
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

    messageBox.setStyleSheet(messageBoxStyle);

    // 设置图标，这里使用信息图标作为示例
    messageBox.setIcon(QMessageBox::Information);
    // 显示对话框并等待用户响应
    messageBox.exec();
}

QString processFile(Schedule *sche, const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        in.setCodec("UTF-8");

        QString finish = in.readLine().trimmed();
        QString format = "yyyy-MM-dd HH:mm:ss";
        QDateTime cur = QDateTime::currentDateTime();
        QDateTime tar = QDateTime::fromString(in.readLine().trimmed(), format);
        int tmpid = in.readLine().trimmed().toInt();
        QString tmpsub = in.readLine().trimmed();

        // 已经完成则直接删除并返回空串
        if (finish == "已完成") {
            file.close(); // 关闭
            qDebug() << "find a finished task,prepare to delete";
            if (QFile::remove(filePath)) // 删除
                qDebug() << "delete successful";
            else
                qDebug() << "delete unsuccessful";
            return "";
        }

        // 已经过期则删除并返回信息
        if (cur.msecsTo(tar) < 0) { // 已过期
            file.close(); // 关闭
            if (QFile::remove(filePath)) // 删除
                qDebug() << "delete successful";
            else
                qDebug() << "delete unsuccessful";
            return QString("O-") + tmpsub + QString("-%1").arg(tmpid);
        }

        qlonglong msecs = cur.msecsTo(tar);
        // 将毫秒转换为天数、小时数、分钟数
        int days = msecs / (24 * 60 * 60 * 1000);
        msecs %= (24 * 60 * 60 * 1000); // 计算剩余的毫秒数
        int hours = msecs / (60 * 60 * 1000);
        msecs %= (60 * 60 * 1000); // 计算剩余的毫秒数
        int minutes = msecs / (60 * 1000);
        QString result;
        result = QString("(%1days%2hours%3minutesleft)").arg(days).arg(hours).arg(minutes);

        QString tmpcontent;
        // 逐行读取内容
        tmpcontent = in.readAll();
        file.close();

        // 加入任务栏
        TaskItem *tmptsk = new TaskItem(tar, tmpsub, tmpcontent, tmpid, false);
        QListWidgetItem *item = new QListWidgetItem(tmptsk->getSubject() + (tmptsk->isFinished() ? "(已完成)" : "(未完成)"));
        sche->taskListWidget_->addItem(item);
        sche->taskListWidget_->setItemWidget(item, tmptsk);

        return QString("I-") + tmpsub + result + QString("-") + QString("%1").arg(tmpid);
    } else {
        qDebug() << "Failed to open file:" << filePath;
        return "";
    }
}
