#include "impressoes.h"
#include "ui_impressoes.h"

Impressoes::Impressoes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Impressoes)
{
    ui->setupUi(this);
    setWindowTitle("Impressões");
    setWindowIcon(QIcon(":/imgs/imgs/imprimir.png"));
}

Impressoes::~Impressoes()
{
    delete ui;
}

void Impressoes::on_Fechar_clicked()
{
    close();
}
