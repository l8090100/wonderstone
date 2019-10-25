#ifndef BOARDPAGE_H
#define BOARDPAGE_H

#include <QWidget>


namespace Ui {
class BoardPage;
}

class BoardPage : public QWidget
{
    Q_OBJECT
public:
    explicit BoardPage(QWidget *parent = 0);
    ~BoardPage();
public:
    Ui::BoardPage *ui;


};

#endif // BOARDPAGE_H
