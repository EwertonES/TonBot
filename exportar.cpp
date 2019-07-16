#include "exportar.h"
#include "ui_exportar.h"
#include <QDir>
#include <QSettings>

Exportar::Exportar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Exportar)
{
    ui->setupUi(this);
    setWindowTitle("Exportar...");
    setWindowIcon(QIcon(":/imgs/imgs/imprimir.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    ui->Construcao->setEnabled(false);

    Exportar::Carregar();

    QString dir1 = QDir::homePath().append("/Documents/TonBot/");

    QDir diretorio = dir1;
    QDir dir2;
    QStringList meses;

    QStringList anos = diretorio.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs, QDir::DirsFirst);

    for (int i=anos.size()-1; i>=0; i--){
        ui->Ano->addItem(anos[i]);
        dir2 = (dir1 + anos[i] + ("/"));
        meses = dir2.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs, QDir::DirsFirst | QDir::Time);
        for (int j=meses.size()-1; j>=0; j--){
            ui->Mes->addItem(meses[j] + ("/") + anos[i]);
        }
    }

    connect(ui->ListaDizimistas, SIGNAL(toggled(bool)), ui->Construcao, SLOT(setEnabled(bool)));
}

Exportar::~Exportar()
{
    delete ui;
}
void Exportar::Carregar(){
    QSettings settings("Configuracoes 2");
    QCheckBox checkboxes;
    settings.beginGroup("Preferencias 2");
    ui->ListaDizimistas->setChecked(settings.value("ListaDizimistas").toBool());
    ui->Diario->setChecked(settings.value("Diario").toBool());
    ui->CapaMensal->setChecked(settings.value("CapaMensal").toBool());
    ui->RelatorioMensal->setChecked(settings.value("RelatorioMensal").toBool());
    ui->RelatorioAnual->setChecked(settings.value("RelatorioAnual").toBool());
    if (ui->ListaDizimistas->isChecked()){
        ui->Construcao->setEnabled(true);
        ui->Construcao->setChecked(settings.value("Construcao").toBool());
    }
    settings.endGroup();
}

int Exportar::ListaDizimistas() const {
    if (ui->ListaDizimistas->isChecked()){return 1;};
    return 0;
}

int Exportar::Construcao() const {
    if (ui->Construcao->isChecked()){return 1;};
    return 0;
}

int Exportar::Diario() const {
    if (ui->Diario->isChecked()){return 1;};
    return 0;
}
int Exportar::CapaMensal() const {
    if (ui->CapaMensal->isChecked()){return 1;};
    return 0;
}
int Exportar::RelatorioMensal() const {
    if (ui->RelatorioMensal->isChecked()){return 1;};
    return 0;
}
int Exportar::RelatorioAnual() const {
    if (ui->RelatorioAnual->isChecked()){return 1;};
    return 0;
}
QString Exportar::TRelatorioMensal() const {
    return ui->Mes->currentText();
}
QString Exportar::TRelatorioAnual() const {
    return ui->Ano->currentText();
}

void Exportar::on_pushButton_clicked()
{
    QSettings settings("Configuracoes 2");
    settings.beginGroup("Preferencias 2");
    settings.setValue("ListaDizimistas",ui->ListaDizimistas->isChecked());
    settings.setValue("Diario",ui->Diario->isChecked());
    settings.setValue("CapaMensal",ui->CapaMensal->isChecked());
    settings.setValue("RelatorioMensal",ui->RelatorioMensal->isChecked());
    settings.setValue("RelatorioAnual",ui->RelatorioAnual->isChecked());    
    settings.setValue("Construcao",ui->Construcao->isChecked());
    settings.endGroup();

    accept();
}

void Exportar::on_ListaDizimistas_stateChanged() {
    ui->Construcao->setChecked(false);
}
