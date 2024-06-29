#include "mapp.h"
#include "ui_mapp.h"
#include <QFile>
#include <QWidget>
#include <QDir>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QLabel>
#include <QDebug>
#include <QTextEdit>
#include <QMessageBox>
#include <QRadioButton>
#include <QPixmap>
#include <QTimer>
#include <QSlider>

mapp::mapp(QWidget *parent, QString username_, int level_, int exp_)
: QWidget(parent)
, ui(new Ui::mapp), level(level_), user_name(username_)
{
	ui->setupUi(this);
	place = QString("default");
	ui->place1->setEnabled(false);
	ui->place2->setEnabled(false);
	ui->place3->setEnabled(false);
	ui->place4->setEnabled(false);
	ui->place5->setEnabled(false);
	ui->place6->setEnabled(false);
	
	// 设置样式
	QString widgetStyle = "QWidget#mapp {"
	"background-color: #FFF0F5;"  // 浅粉色背景
	"}";
	
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
	"color: black;"
	"font-size: 16px;"
	"font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
	"}";
	
	QString radioButtonStyle = "QRadioButton {"
	"font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
	"font-size: 16px;"
	"}";
	
	// 应用样式
	this->setStyleSheet(widgetStyle);
	ui->place1->setStyleSheet(radioButtonStyle);
	ui->place2->setStyleSheet(radioButtonStyle);
	ui->place3->setStyleSheet(radioButtonStyle);
	ui->place4->setStyleSheet(radioButtonStyle);
	ui->place5->setStyleSheet(radioButtonStyle);
	ui->place6->setStyleSheet(radioButtonStyle);
	
	ui->pushButton->setStyleSheet(buttonStyle);
	ui->label->setStyleSheet(labelStyle);
	
	QImage imgme = QImage(":/photome.png");
	ui->lbme->setPixmap(QPixmap::fromImage(imgme).scaled(130, 130));
	ui->lbme->setScaledContents(true);
	ui->lbme->setFixedSize(130, 130);
	ui->lbme->move(50, 50);
	ui->lbme->show();
	
	QImage imgop = QImage(":/photoop.png");
	ui->lbop->setPixmap(QPixmap::fromImage(imgop).scaled(150, 150));
	ui->lbop->setScaledContents(true);
	ui->lbop->setFixedSize(150, 150);
	ui->lbop->move(200, 175);
	
	ui->label->move(30, 30);
	ui->label->resize(40, 20);
	ui->label->setText("Lv. " + QString::number(level, 10));
	ui->label->setFont(QFont("Cambria"));

    ui->lbusername->setText(username_);
    ui->lbusername->setFont(QFont("Cambria"));
    ui->lbusername->move(160,30);
	
	ui->exp->setMinimum(0);
	ui->exp->setMaximum(300);
    QString style = "QSlider {"
                    "background-color: #FFFFFF;"   // 滑块背景色
                    "}"
                    "QSlider::groove:horizontal {"
                    "height: 30px;"                  // 滑槽高度
                    "background-color: #ebebeb;"     // 滑槽背景色
                    "}"
                    "QSlider::handle:horizontal {"
                    "width: 0px;"                   // 滑块宽度
                    "background-color: #fdff44;"      // 滑块颜色
                    "}"
                    "QSlider::sub-page:horizontal{"
                    "background-color: #ea6151;"
                    "}";
    ui->exp->setStyleSheet(style);
	ui->exp->setValue(exp_);
	ui->exp->setEnabled(false);
	ui->exp->move(70, 30);
	ui->exp->resize(80, 20);
	
	qanme = new QPropertyAnimation(ui->lbme, "rotation");
	qanme->setDuration(750);
	qanme->setStartValue(0);
	qanme->setEndValue(360);
	qanme->setEasingCurve(QEasingCurve::OutQuart);
	qanop = new QPropertyAnimation(ui->lbop, "rotation");
	qanop->setDuration(750);
	qanop->setStartValue(0);
	qanop->setEndValue(360);
	qanop->setEasingCurve(QEasingCurve::OutQuart);
	
	QTimer *tmr = new QTimer(this);
	connect(tmr, &QTimer::timeout, this, &mapp::startRotationAnimation);
	tmr->start(5000);
}

void mapp::loadmappdata() {
	QRadioButton *tpp(nullptr);
	if (level == 0) {
		QMessageBox *tpb = new QMessageBox(this);
		tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
		tpb->setWindowTitle("暗夜来临！");
		tpb->setText("北京大学不幸被邪恶的怪兽侵占了。你要通过自己的努力，提升打怪能力，救出同学和老师，还北大一份光明！");
		tpb->setModal(false); // 设置为非模态
		tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
		tpb->setStyleSheet("QMessageBox {"
			"font-family: 'Comic Sans MS', 'Microsoft YaHei', sans-serif;" // 可爱字体
			"font-size: 16px;"
			"border: 2px solid pink;"
			"border-radius: 10px;"
			"}");
		tpb->exec();
	}
	if (level >= 1) {
		tpp = ui->place1;
		ui->place1->setEnabled(true);
		ui->place1->setChecked(true);
		place = ui->place1->text();
	}
	if (level >= 2) {
		tpp = ui->place2;
		ui->place2->setEnabled(true);
		ui->place2->setChecked(true);
		place = ui->place2->text();
	}
	if (level >= 3) {
		tpp = ui->place3;
		ui->place3->setEnabled(true);
		ui->place3->setChecked(true);
		place = ui->place3->text();
	}
	if (level >= 4) {
		tpp = ui->place4;
		ui->place4->setEnabled(true);
		ui->place4->setChecked(true);
		place = ui->place4->text();
	}
	if (level >= 5) {
		tpp = ui->place5;
		ui->place5->setEnabled(true);
		ui->place5->setChecked(true);
		place = ui->place5->text();
	}
	if (level >= 6) {
		tpp = ui->place6;
		ui->place6->setEnabled(true);
		ui->place6->setChecked(true);
		place = ui->place6->text();
	}
	if (tpp != nullptr) {
		QLabel *tlb = new QLabel("你在这里", this);
		tlb->move(tpp->geometry().x() - 20, tpp->geometry().y() - 30);
		tlb->resize(100, 30);
		tlb->setFont(QFont("Comic Sans MS", 10)); // 设置可爱的字体
	}
	show();
}

void mapp::on_place1_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place1->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}


void mapp::on_place2_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place2->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}


void mapp::on_place3_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place3->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}


void mapp::on_place4_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place4->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}


void mapp::on_place5_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place5->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}


void mapp::on_place6_clicked()
{
    QMessageBox *tpb=new QMessageBox(this);
    tpb->setAttribute(Qt::WA_DeleteOnClose); // 确保消息框关闭时删除
    tpb->setWindowTitle("成就");
    tpb->setText("已达成成就：解放" + ui->place6->text());
    tpb->setModal(false); // 设置为非模态
    tpb->setWindowFlags(tpb->windowFlags() | Qt::WindowStaysOnTopHint); // 确保窗口保持在最前面
    //tpb->show();
    tpb->exec();
}

void mapp::on_pushButton_clicked()
{
	this->close();
}

void mapp::startRotationAnimation() {
	qanme->start();
	qanop->start();
	show();
}

