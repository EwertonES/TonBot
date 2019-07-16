#include "calendario.h"
#include "ui_calendario.h"

#include <QDir>
#include <QPushButton>
#include <QIcon>
#include <QTextCharFormat>
#include <QDateTime>

Calendario::Calendario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Calendario)
{
    ui->setupUi(this);
    setWindowTitle("Calendário");
    setWindowIcon(QIcon(":/imgs/imgs/calendario.png"));
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QString diretorio = QDir::homePath().append("/Documents/TonBot/");

    QDir dir1, dir2, dir3;
    dir1 = diretorio;
    QStringList anos, meses, eventos;
    int i,j,k;
    QTextCharFormat formato;
    formato.setBackground(Qt::darkGreen);
    formato.setForeground(Qt::white);
    int ano, mes,dia;
    QString dataevento;

    anos = dir1.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs, QDir::DirsFirst);
    for (i=anos.size()-1; i>=0; i--){
        dir2 = (diretorio + anos[i] + ("/"));
        meses = dir2.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs, QDir::DirsFirst);
        for (j=meses.size()-1; j>=0; j--){
            dir3 = (diretorio + anos[i] + ("/") + meses[j] + ("/"));
            dir3.setNameFilters(QStringList()<<"* Dados.txt");
            eventos = dir3.entryList();
            for (k=0; k<eventos.size(); ++k){
                if (eventos[k].contains("-")){
                    dataevento = eventos[k].remove(5,16);
                    ano=anos[i].toInt();
                    mes=dataevento.split("-").first().toInt();
                    dia=dataevento.split("-").last().toInt();
                    QDate data(ano,mes,dia);
                    ui->calendarWidget->setDateTextFormat(data,formato);
                    datas << data;
                }
            }
        }
    }
    ano=QDateTime::currentDateTime().toString("yyyy").toInt();
    mes=QDateTime::currentDateTime().toString("MM").toInt();
    dia=QDateTime::currentDateTime().toString("dd").toInt();
    QDate data(ano,mes,dia);
    ui->calendarWidget->setSelectedDate(data);

}

Calendario::~Calendario()
{
    delete ui;
}

QString Calendario::AbrirData() const {
    return abrirdata;
}

void Calendario::on_calendarWidget_clicked(const QDate &date)
{
    if (datas.contains(date)){
        abrirdata=date.toString("yyyy/MMMM/ MM-dd");
        Calendario::AbrirData();
        this->close();
    }
}
