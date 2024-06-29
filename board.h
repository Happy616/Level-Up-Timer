#ifndef BOARD_H
#define BOARD_H

#include <QWidget>

namespace Ui {
class Board;
}

class Board : public QWidget
{
    Q_OBJECT

public:
    explicit Board(QWidget *parent = nullptr);
    ~Board();

private slots:
    void on_addfeelingsbt_clicked();
    void on_clearbt_clicked();

private:
    Ui::Board *ui;
    void loadBoardData();
    void reloadBoardData();
};

#endif // BOARD_H
