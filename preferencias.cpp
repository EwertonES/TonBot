#include "preferencias.h"
#include "ui_preferencias.h"
#include <QSettings>

Preferencias::Preferencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferencias)
{
    ui->setupUi(this);
    setWindowTitle("Preferências");
    setWindowIcon(QIcon(":/imgs/imgs/configuracoes.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    Preferencias::Carregar();
}

Preferencias::~Preferencias()
{
    delete ui;
}


void Preferencias::VerificarConfiguracoes(){
    if (ui->Igreja->text().isEmpty() ||
            ui->Rua->text().isEmpty() ||
            ui->Bairro->text().isEmpty() ||
            ui->Cidade->text().isEmpty() ||
            ui->UF->text().isEmpty() ||
            ui->Pastor->text().isEmpty() ||
            ui->Responsavel->text().isEmpty())
    {
        exec();
    }
}

void Preferencias::on_pushButton_clicked()
{
    Preferencias::VerificarConfiguracoes();

    QSettings settings("Configuracoes");
    settings.beginGroup("Preferencias");
    settings.setValue("igreja",ui->Igreja->text());
    settings.setValue("rua",ui->Rua->text());
    settings.setValue("bairro",ui->Bairro->text());
    settings.setValue("cidade",ui->Cidade->text());
    settings.setValue("uf",ui->UF->text());
    settings.setValue("pastor",ui->Pastor->text());
    settings.setValue("responsavel",ui->Responsavel->text());
    settings.endGroup();

    accept();
}

void Preferencias::Carregar(){
    QSettings settings("Configuracoes");
    settings.beginGroup("Preferencias");
    ui->Igreja->setText(settings.value("igreja").toString());
    ui->Rua->setText(settings.value("rua").toString());
    ui->Bairro->setText(settings.value("bairro").toString());
    ui->Cidade->setText(settings.value("cidade").toString());
    ui->UF->setText(settings.value("uf").toString());
    ui->Pastor->setText(settings.value("pastor").toString());
    ui->Responsavel->setText(settings.value("responsavel").toString());
    settings.endGroup();
}


QString Preferencias::Igreja() const {
    return ui->Igreja->text();
}

QString Preferencias::Rua() const {
    return ui->Rua->text();
}

QString Preferencias::UF() const {
    return ui->UF->text();
}

QString Preferencias::Cidade() const {
    return ui->Cidade->text();
}

QString Preferencias::Bairro() const {
    return ui->Bairro->text();
}

QString Preferencias::Pastor() const {
    return ui->Pastor->text();
}

QString Preferencias::Responsavel() const {
    return ui->Responsavel->text();
}
