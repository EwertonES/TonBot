#include "envelopes.h"
#include "ui_envelopes.h"
#include <QPushButton>

Envelopes::Envelopes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Envelopes)
{
    ui->setupUi(this);
    setWindowTitle("Envelopes");
    setWindowIcon(QIcon(":/imgs/imgs/adicionarenv.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->Botoes->button(QDialogButtonBox::Ok)->setText("Adicionar");
    ui->Botoes->button(QDialogButtonBox::Cancel)->setText("Fechar");

    QRegExp cond0("^[A-Za-z][A-Za-z\\s]*$");
    QValidator *val0 = new QRegExpValidator(cond0, this);
    ui->Nome->setValidator(val0);
}

Envelopes::~Envelopes() {
    delete ui;
}

QString Envelopes::Nome() const {
    return ui->Nome->text().toUpper();
}
double Envelopes::Dizimo() const {
    return ui->Dizimo->value();
}
double Envelopes::Oferta() const{
    return ui->Oferta->value();
}
double Envelopes::Construcao() const {
    return ui->Construcao->value();
}
double Envelopes::Missao() const {
    return ui->Missao->value();
}
double Envelopes::Voto() const {
    return ui->Voto->value();
}

void Envelopes::on_Botoes_accepted() {
    accept();
}
void Envelopes::on_Botoes_rejected() {
    reject();
}
