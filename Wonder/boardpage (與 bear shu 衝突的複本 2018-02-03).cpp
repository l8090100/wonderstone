#include "boardpage.h"
#include "ui_boardpage.h"

BoardPage::BoardPage(QWidget *parent): QWidget(parent),  ui(new Ui::BoardPage)
{
    ui->setupUi(this);

};

BoardPage::~BoardPage()
{
    delete ui;
}
