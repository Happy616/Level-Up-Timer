#ifndef TASKDIALOG_H
#define TASKDIALOG_H

#endif // TASKDIALOG_H

#include <QDialog>
#include <QTimeEdit>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QMessageBox>

class TaskDialog : public QDialog {
    Q_OBJECT

public:
    TaskDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setupUI();
    }//一不小心直接在头文件里实现了构造函数

    QDateTime getTime() const {
        return timeEdit->dateTime();
    }

    QString getTopic() const {
        return topicEdit->text();
    }

    QString getContent() const {
        return contentEdit->toPlainText();
    }

private slots:
    void onAccept() {
        if(!getTopic().trimmed().isEmpty())
            accept();
        else{
            QMessageBox::warning(this, "警告", "主题不能为空！");
        }
    }

private:
    QDateTimeEdit *timeEdit;
    QLineEdit *topicEdit;
    QTextEdit *contentEdit;

    void setupUI() {
        QLabel *timeLabel = new QLabel("时间：", this);
        QLabel *topicLabel = new QLabel("主题：", this);
        QLabel *contentLabel = new QLabel("内容及要求：", this);

        timeEdit = new QDateTimeEdit(this);
        timeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss"); // 设置时间显示格式

        topicEdit = new QLineEdit(this);

        contentEdit = new QTextEdit(this);
        contentEdit->setAcceptRichText(false); // 设置为纯文本编辑

        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(timeLabel);
        layout->addWidget(timeEdit);
        layout->addWidget(topicLabel);
        layout->addWidget(topicEdit);
        layout->addWidget(contentLabel);
        layout->addWidget(contentEdit);
        layout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &TaskDialog::onAccept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

        setWindowTitle(tr("任务输入"));
    }
};
