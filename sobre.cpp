#include "sobre.h"
#include "ui_sobre.h"

Sobre::Sobre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sobre)
{
    ui->setupUi(this);
    setWindowTitle("Sobre");
    setWindowIcon(QIcon(":/imgs/imgs/moneybag.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

Sobre::~Sobre()
{
    delete ui;
}

void Sobre::on_pushButton_clicked()
{
    QApplication::quit();
}
