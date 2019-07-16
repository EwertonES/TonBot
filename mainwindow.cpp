#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sobre.h"
#include "envelopes.h"
#include "preferencias.h"
#include "exportar.h"
#include "calendario.h"

#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QTextStream>
#include <QDesktopServices>
#include <QPrinter>
#include <QPainter>
#include <QDirIterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(("TonBot   -   [") + (QDateTime::currentDateTime().toString("MM-dd HH-mm ")) + ("Dados.txt]"));
    setWindowIcon(QIcon(":/imgs/imgs/moneybag.png"));    
    setWindowFlags(windowFlags() | Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    Sobre sobre;
    sobre.exec();

    QStringList nomecolunas;
    nomecolunas << "NOME" << "DÍZIMO" << "MISSÃO" << "OFERTA" << "VOTO" << "CONSTRUÇÃO";

    ui->Tabela->setColumnCount(6);
    ui->Tabela->setHorizontalHeaderLabels(nomecolunas);
    ui->Tabela->setColumnWidth(NOME,(this->width())*25/100);
    ui->Tabela->setColumnWidth(DIZIMO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(MISSAO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(OFERTA,(this->width())*14/100);
    ui->Tabela->setColumnWidth(VOTO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(CONSTRUCAO,(this->width())*14/100);
    ui->Tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Tabela->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->Editar->setCheckable(true);

    timer_1s = new QTimer(this);
    QObject::connect(timer_1s, SIGNAL(timeout()), this, SLOT(UpdateDateTime()));
    timer_1s->start(1000);

    ui->Salvar->setShortcut(Qt::CTRL + Qt::Key_S);
    ui->Adicionar->setShortcut(Qt::CTRL + Qt::Key_Equal);
    ui->Remover->setShortcut(Qt::Key_Delete);
    ui->Exportar->setShortcut(Qt::CTRL + Qt::Key_P);
    ui->Novo->setShortcut(Qt::CTRL + Qt::Key_N);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    ui->Tabela->setColumnWidth(NOME,(this->width())*25/100);
    ui->Tabela->setColumnWidth(DIZIMO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(MISSAO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(OFERTA,(this->width())*14/100);
    ui->Tabela->setColumnWidth(VOTO,(this->width())*14/100);
    ui->Tabela->setColumnWidth(CONSTRUCAO,(this->width())*14/100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::UpdateDateTime() {
    QString TextodaHora = QDateTime::currentDateTime().toString("hh:mm      dddd, dd 'de' MMMM 'de' yyyy");
    TextodaHora.replace(11, 1, TextodaHora[11].toUpper());
    ui->Hora->setText(TextodaHora);
}

void MainWindow::Atualizar(){
    int col = ui->Tabela->columnCount();
    int lin = ui->Tabela->rowCount();
    int i,j,k;
    int l=0;
    QString prefixo, prefixol;

    ui->Tabela->sortItems(0,Qt::AscendingOrder);
    for (i=0; i<(lin); ++i){
        prefixo = ui->Tabela->item(i,0)->text().split(" ").first();
        if ((prefixo=="DC") || (prefixo=="PB") || (prefixo=="EV") || (prefixo=="PR")){

            if (prefixo=="PR"){
                while(l<lin){
                    prefixol = ui->Tabela->item(l,0)->text().split(" ").first() + " ";
                    if (!(prefixol=="PR ") && !(ui->Tabela->item(l,0)->text().contains("OFERTA"))){
                        ui->Tabela->insertRow(l);
                        for (k=0; k<col; ++k){ui->Tabela->setItem(l,k,new QTableWidgetItem(ui->Tabela->item(i+1,k)->text()));}
                        ui->Tabela->removeRow(i+1);
                        l=lin;
                    } l+=1;
                } l=0;
            }

            if (prefixo=="EV"){
                while(l<lin){
                    prefixol = ui->Tabela->item(l,0)->text().split(" ").first() + " ";
                    if ((!(prefixol=="PR ") && !(prefixol=="EV ")) && !(ui->Tabela->item(l,0)->text().contains("OFERTA"))){
                        ui->Tabela->insertRow(l);
                        for (k=0; k<col; ++k){ui->Tabela->setItem(l,k,new QTableWidgetItem(ui->Tabela->item(i+1,k)->text()));}
                        ui->Tabela->removeRow(i+1);
                        l=lin;
                    } l+=1;
                } l=0;
            }

            if (prefixo=="PB"){
                while(l<lin){
                    prefixol = ui->Tabela->item(l,0)->text().split(" ").first() + " ";
                    if ((!(prefixol=="PR ") && !(prefixol=="EV ") && !(prefixol=="PB ")) && !(ui->Tabela->item(l,0)->text().contains("OFERTA"))){
                        ui->Tabela->insertRow(l);
                        for (k=0; k<col; ++k){ui->Tabela->setItem(l,k,new QTableWidgetItem(ui->Tabela->item(i+1,k)->text()));}
                        ui->Tabela->removeRow(i+1);
                        l=lin;
                    } l+=1;
                } l=0;
            }

            if (prefixo=="DC"){
                while(l<lin){
                    prefixol = ui->Tabela->item(l,0)->text().split(" ").first() + " ";
                    if ((!(prefixol=="PR ") && !(prefixol=="EV ") && !(prefixol=="PB ") && !(prefixol=="DC ")) && !(ui->Tabela->item(l,0)->text().contains("OFERTA"))){
                        ui->Tabela->insertRow(l);
                        for (k=0; k<col; ++k){ui->Tabela->setItem(l,k,new QTableWidgetItem(ui->Tabela->item(i+1,k)->text()));}
                        ui->Tabela->removeRow(i+1);
                        l=lin;
                    } l+=1;
                } l=0;
            }

        }
        if (ui->Tabela->item(i,0)->text().contains("OFERTA")){
            ui->Tabela->insertRow(0);
            for (k=0; k<col; ++k){ui->Tabela->setItem(0,k,new QTableWidgetItem(ui->Tabela->item(i+1,k)->text()));}
            ui->Tabela->removeRow(i+1);
        }
    }
    for (i=0; i<(lin); ++i){
        for (j=1; j<(col); ++j){
            if (!(ui->Tabela->item(i,j)->text().contains("R"))){
                if ((ui->Tabela->item(i,j)->text().contains(",",Qt::CaseSensitive))) {
                    ui->Tabela->item(i,j)->setText(ui->Tabela->item(i,j)->text().replace(",", ".", Qt::CaseSensitive));
                }
                QString valores = QLocale().toCurrencyString(ui->Tabela->item(i,j)->text().toDouble());
                ui->Tabela->setItem(i,j,new QTableWidgetItem(valores));
                if ((ui->Tabela->item(i,j)->text().contains(".",Qt::CaseSensitive))) {
                    ui->Tabela->item(i,j)->setText(ui->Tabela->item(i,j)->text().replace(".", "", Qt::CaseSensitive));
                }
            }
            if (ui->Tabela->item(i,j)->text().contains("-")){
                ui->Tabela->item(i,j)->setTextColor(Qt::red);
            }
        }
    }
}

void MainWindow::on_Adicionar_clicked() {
    int val;
    double Dizimo, Oferta, Missao, Construcao, Voto;
    QString Nome;

    Envelopes envelopes;
    val = envelopes.exec();

    if (val == QDialog::Rejected){
        MainWindow::Atualizar();
        return;
    }

    Nome = envelopes.Nome();
    Dizimo = envelopes.Dizimo();
    Oferta = envelopes.Oferta();
    Missao = envelopes.Missao();
    Construcao = envelopes.Construcao();
    Voto = envelopes.Voto();

    ui->Tabela->insertRow(0);
    ui->Tabela->setItem(0,NOME,new QTableWidgetItem(Nome));
    ui->Tabela->setItem(0,DIZIMO,new QTableWidgetItem(QString::number(Dizimo,'f',2)));
    ui->Tabela->setItem(0,OFERTA,new QTableWidgetItem(QString::number(Oferta,'f',2)));
    ui->Tabela->setItem(0,MISSAO,new QTableWidgetItem(QString::number(Missao,'f',2)));
    ui->Tabela->setItem(0,CONSTRUCAO,new QTableWidgetItem(QString::number(Construcao,'f',2)));
    ui->Tabela->setItem(0,VOTO,new QTableWidgetItem(QString::number(Voto,'f',2)));

    if (val == QDialog::Accepted)
        ui->Adicionar->clicked();
}

void MainWindow::on_Editar_toggled(bool toggled) {
    if (toggled){
        ui->Tabela->setEditTriggers(QAbstractItemView::AllEditTriggers);
    } else {
        ui->Tabela->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->Tabela->setEditTriggers(QAbstractItemView::NoEditTriggers);
        MainWindow::Atualizar();
    }
}

void MainWindow::on_Remover_clicked() {
    int Linha = ui->Tabela->currentRow();
    ui->Tabela->removeRow(Linha);
}

void MainWindow::on_Preferencias_clicked() {
    Preferencias preferencias;
    preferencias.exec();
}

void MainWindow::on_Sair_clicked() {
    QApplication::quit();
}

void MainWindow::on_Salvar_clicked() {
    QString diretorio = QDir::homePath();
    diretorio.append("/Documents/TonBot/");

    QDir dir;
    if(!dir.exists(diretorio)){
        dir.mkpath(diretorio);
    }

    QString data = QDateTime::currentDateTime().toString("yyyy/");
    diretorio.append(data);
    if(!dir.exists(diretorio)){
        dir.mkpath(diretorio);
    }

    data = QDateTime::currentDateTime().toString("MMMM/");
    diretorio.append(data);
    if(!dir.exists(diretorio)){
        dir.mkpath(diretorio);
    }

    QString nometabela, dirtabela;
    nometabela = windowTitle().split("[").back().split("]").first();
    dirtabela = diretorio + nometabela;


    int n = ui->Tabela->rowCount();
    int m = 6;

    QString dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirtabela,("Documentos (*.txt)"));

    QFile arquivo(dirarquivo);
    if (arquivo.open(QIODevice::WriteOnly)) {
        QTextStream stream(&arquivo);
        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                stream << '\n';
            }
            for (int j = 0; j < m; ++j) {
               stream << ui->Tabela->item(i, j)->text() << '.';
            }
        }
        arquivo.close();
    }
}

void MainWindow::on_Carregar_clicked()
{
    QTableWidget tabela;
    QString diretorio = QDir::homePath() + ("/Documents/TonBot/");
    QString dirarquivo = QFileDialog::getOpenFileName(this, ("Abrir arquivo"),diretorio,("Documentos (*.txt)"));
    QFile arquivo(dirarquivo);

    if (!dirarquivo.isEmpty()){
        MainWindow::on_Novo_clicked();
        QString nometabela = (("TonBot   -   [") + dirarquivo.split(QDateTime::currentDateTime().toString("MMMM/")).back() + "]");
        setWindowTitle(nometabela);
    }

    QTextStream texto(&arquivo);

    if (arquivo.open(QIODevice::ReadOnly)){
        QList<QStringList> lista;
        QString linha;
        while (!texto.atEnd()) {
            linha = texto.readLine();
            lista << linha.split(".");
        }

        for ( int linha=0; linha<lista.size();++linha ) {
            ui->Tabela->insertRow(linha);
            for (int coluna=0; coluna<lista[linha].size(); ++coluna) {
                ui->Tabela->setItem(linha, coluna, new QTableWidgetItem(lista[linha][coluna]));
            }
        }
    }

    MainWindow::Atualizar();
}

void MainWindow::on_Exportar_clicked()
{
    MainWindow::Atualizar();
    Exportar exportar;
    int val = exportar.exec();

    if (val == QDialog::Accepted){

        QString diretorio = QDir::homePath();
        diretorio.append("/Documents/TonBot/");
        QDir dir;
        if(!dir.exists(diretorio)){dir.mkpath(diretorio);}
        QString data = QDateTime::currentDateTime().toString("yyyy/");
        diretorio.append(data);
        if(!dir.exists(diretorio)){dir.mkpath(diretorio);}
        data = QDateTime::currentDateTime().toString("MMMM/");
        diretorio.append(data);
        if(!dir.exists(diretorio)){dir.mkpath(diretorio);}
        QString nomearquivo;

        if (exportar.ListaDizimistas()==1 && exportar.Construcao()==0){
            nomearquivo = (windowTitle().split("[").last()).split(" Dados").first() + (" Dizimistas.pdf");
            QString dirarquivo = diretorio + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF, Responsavel;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();
            Responsavel = prefs.Responsavel();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            //Início
            QStringList dizimistas;
            QString dizimovalor;

            int i, j;
            int imax = 25;

            for (int k = 0; k<ui->Tabela->rowCount();++k){
                dizimovalor = (ui->Tabela->model()->index(k,1).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                if ((dizimovalor.toFloat())>0){dizimistas.append(ui->Tabela->item(k,0)->text());
                }
            }

            int paginas = (dizimistas.size()/50);
            if (dizimistas.size()%50!=0){
                paginas+=1;
            }

            QPainter painter(&printer);

            for (int pagina=1; pagina<=paginas; ++pagina){
                if (pagina!=1){printer.newPage();}
                //Logo
                QRect rectlogo = QRect(60,20,90,90);
                painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

                //Cabeçalho
                painter.setFont(QFont("Arial",11));
                painter.setPen(Qt::gray);
                painter.drawText(180,70,Igreja);
                painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

                //Rodapé
                painter.drawLine(60,760,510,760);
                painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

                //Titulo
                QFont bold("Arial", 16);
                bold.setBold(true);
                painter.setPen(Qt::black);
                painter.setFont(bold);
                painter.drawLine(60,133,510,133);
                painter.drawLine(60,155,510,155);
                painter.drawText(200,150,"    LISTA DE DIZIMISTAS");
                painter.setFont(QFont("Arial",13));
                QString dataoriginal = dirarquivo.split("Bot/").last().split(" ").first(); dataoriginal.remove(dataoriginal.size()-5,3);
                QDateTime dataoriginal1 = QDateTime::fromString(dataoriginal,"yyyy/MMMM/dd");
                painter.drawText(200,170,dataoriginal1.toString("dddd, dd 'de' MMMM 'de' yyyy"));

                //Nomes
                painter.setFont(QFont("Arial",14));
                dizimistas.append("");
                for (j=0; j<=1; ++j){
                    i=0;
                    while (i<imax){
                        if (!dizimistas[50*(pagina-1)+25*j+i].isEmpty()){
                            painter.drawText(100+(j*240),210+i*22,dizimistas[50*(pagina-1)+25*j+i]);
                        } else {
                            i=imax; j=2;
                        }
                        i=i+1;
                    }
                }
            }
            painter.end();
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));
        }
        if (exportar.Construcao()==1){
            nomearquivo = (windowTitle().split("[").last()).split(" D").first() + (" Dizimistas e Construcao.pdf");
            QString dirarquivo = diretorio + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF, Responsavel;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();
            Responsavel = prefs.Responsavel();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            //Início
            QStringList dizimistas, construcao2;
            QString dizimovalor, construcaovalor;

            int i;
            int imax = 25;

            for (int k = 0; k<ui->Tabela->rowCount();++k){
                dizimovalor = (ui->Tabela->model()->index(k,1).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                if ((dizimovalor.toFloat())>0){dizimistas.append(ui->Tabela->item(k,0)->text());
                }
                construcaovalor = (ui->Tabela->model()->index(k,5).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                if ((construcaovalor.toFloat())>0){construcao2.append(ui->Tabela->item(k,0)->text());
                }
            }

            int paginasa = (dizimistas.size()/25);
            int paginasb = (construcao2.size()/25);
            int paginas;
            if (paginasa>=paginasb){
                paginas=paginasa;
                if (dizimistas.size()%25!=0){paginas+=1;}
            } else{
                paginas=paginasb;
                if (construcao2.size()%25!=0){paginas+=1;}
            }

            QPainter painter(&printer);

            for (int pagina=1; pagina<=paginas; ++pagina){
                if (pagina!=1){printer.newPage();}
                //Logo
                QRect rectlogo = QRect(60,20,90,90);
                painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

                //Cabeçalho
                painter.setFont(QFont("Arial",11));
                painter.setPen(Qt::gray);
                painter.drawText(180,70,Igreja);
                painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

                //Rodapé
                painter.drawLine(60,760,510,760);
                painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

                //Titulo
                QFont bold("Arial", 16);
                bold.setBold(true);
                painter.setPen(Qt::black);
                painter.setFont(bold);
                painter.drawLine(60,133,260,133);
                painter.drawLine(60,155,260,155);
                painter.drawLine(310,133,510,133);
                painter.drawLine(310,155,510,155);
                painter.drawText(120,150,"DIZIMISTAS");
                painter.drawText(355,150,"CONSTRUÇÃO");
                painter.setFont(QFont("Arial",13));
                QString dataoriginal = dirarquivo.split("Bot/").last().split(" ").first(); dataoriginal.remove(dataoriginal.size()-5,3);
                QDateTime dataoriginal1 = QDateTime::fromString(dataoriginal,"yyyy/MMMM/dd");
                painter.drawText(200,170,dataoriginal1.toString("dddd, dd 'de' MMMM 'de' yyyy"));

                //Nomes
                painter.setFont(QFont("Arial",14));
                dizimistas.append("");
                construcao2.append("");
                i=0;
                while (i<imax){
                    if (!dizimistas[25*(pagina-1)+i].isEmpty()){
                        painter.drawText(100,210+i*22,dizimistas[25*(pagina-1)+i]);
                    } else {dizimistas.append("");}
                    if (!construcao2[25*(pagina-1)+i].isEmpty()){
                        painter.drawText(340,210+i*22,construcao2[25*(pagina-1)+i]);
                    } else {construcao2.append("");}
                    if (dizimistas[25*(pagina-1)+i].isEmpty() && construcao2[25*(pagina-1)+i].isEmpty()){i=imax;}
                    i=i+1;
                }
            }

            painter.end();
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));
        }

        if (exportar.Diario()==1){
            nomearquivo = (windowTitle().split("[").last()).split(" D").first() + (" Relatório Diário.pdf");
            QString dirarquivo = diretorio + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF, Responsavel;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();
            Responsavel = prefs.Responsavel();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            //Início
            QStringList dizimistas, despesas, dizimovalores, despesavalores;
            QString dizimovalor, despesavalor;

            double valortemp = 0, totaldespesa = 0;

            int i;
            int imax = 20;
            int tem=0;
            double somalinha=0;
            int linha = 0, coluna = 0;

            for (int k = 0; k<ui->Tabela->rowCount();++k){
                dizimovalor = (ui->Tabela->model()->index(k,1).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                if ((dizimovalor.toFloat())>0 && !ui->Tabela->item(k,1)->text().contains("-")){
                    dizimistas.append(ui->Tabela->item(k,0)->text());
                    dizimovalores.append(QLocale().toCurrencyString(dizimovalor.toDouble()));
                }
            }
            for (linha=0; linha<ui->Tabela->rowCount(); ++linha){
                for (coluna=1; coluna<=5; ++coluna){
                    valortemp = (ui->Tabela->item(linha,coluna)->text().replace(QString(","),QString(".")).split(" ").last()).toDouble();
                    if (ui->Tabela->item(linha,coluna)->text().contains("-")){
                        somalinha+=-1*valortemp;
                        tem=1;
                    }
                    if (coluna==5 && tem==1){
                        despesas.append(ui->Tabela->item(linha,0)->text());
                        despesavalor.append(QString::number(somalinha));
                        despesavalores.append(QLocale().toCurrencyString(somalinha));
                        totaldespesa+=somalinha;
                        somalinha=0;
                        tem=0;
                    }
                }
            }

            int paginasa = (dizimistas.size()/20);
            int paginasb = (despesas.size()/20);
            int paginas;
            if (paginasa>=paginasb){
                paginas=paginasa;
                if (dizimistas.size()%20!=0){paginas+=1;}
            } else{
                paginas=paginasb;
                if (despesas.size()%20!=0){paginas+=1;}
            }

            dizimistas.append("");
            dizimovalor.append("");
            despesas.append("");
            despesavalor.append("");

            double totaldizimo = 0, totalmissao = 0, totaloferta = 0, totalvoto = 0, totalconstrucao = 0, total = 0;
            for (linha=0; linha<ui->Tabela->rowCount(); ++linha){
                for (int coluna=1; coluna<=5; ++coluna){
                    valortemp = (ui->Tabela->item(linha,coluna)->text().replace(QString(","),QString(".")).split(" ").last()).toDouble();
                    if (ui->Tabela->item(linha,coluna)->text().contains("-")){valortemp=0;}
                    if (coluna==1){totaldizimo+=valortemp;}
                    if (coluna==2){totalmissao+=valortemp;}
                    if (coluna==3){totaloferta+=valortemp;}
                    if (coluna==4){totalvoto+=valortemp;}
                    if (coluna==5){totalconstrucao+=valortemp;}
                }
            }

            total += totaldizimo+totalvoto+totalmissao+totalconstrucao+totaloferta+totaldespesa;

            QPainter painter(&printer);

            QFont bold("Arial", 16); bold.setBold(true);
            QFont bold2("Arial", 14); bold2.setBold(true);

            for (int pagina=1; pagina<=paginas; ++pagina){
                if (pagina!=1){printer.newPage();}
                //Logo
                QRect rectlogo = QRect(60,20,90,90);
                painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

                //Cabeçalho
                painter.setFont(QFont("Arial",11));
                painter.setPen(Qt::gray);
                painter.drawText(180,70,Igreja);
                painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

                //Rodapé
                painter.drawLine(60,760,510,760);
                painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

                //Titulo
                painter.setPen(Qt::black);
                painter.setFont(bold);
                painter.drawLine(60,133,510,133);
                painter.drawLine(60,155,510,155);
                painter.drawText(250,150,"CADERNO");
                painter.setFont(QFont("Arial",13));
                QString dataoriginal = dirarquivo.split("Bot/").last().split(" ").first(); dataoriginal.remove(dataoriginal.size()-5,3);
                QDateTime dataoriginal1 = QDateTime::fromString(dataoriginal,"yyyy/MMMM/dd");
                painter.drawText(200,170,dataoriginal1.toString("dddd, dd 'de' MMMM 'de' yyyy"));

                if (pagina==1){
                    painter.setFont(bold2);
                    if (!dizimistas[0].isEmpty()){
                        painter.drawText(60,210,"DÍZIMOS:");
                        painter.drawText(175,210,QLocale().toCurrencyString(totaldizimo));
                    }
                    if (!despesas[0].isEmpty()){
                        painter.drawText(320,210,"DESPESAS:");
                        painter.drawText(420,210,QLocale().toCurrencyString(totaldespesa));
                    }
                }

                i=0;
                painter.setFont(QFont("Arial",11));
                while (i<imax){
                    if (!dizimistas[20*(pagina-1)+i].isEmpty()){
                        painter.drawText(60,230+i*22,dizimistas[20*(pagina-1)+i]);
                        painter.drawText(210,230+i*22,dizimovalores[20*(pagina-1)+i]);
                    } else {dizimistas.append("");}
                    if (!despesas[20*(pagina-1)+i].isEmpty()){
                        painter.drawText(320,230+i*22,despesas[20*(pagina-1)+i]);
                        painter.drawText(440,230+i*22,despesavalores[20*(pagina-1)+i]);
                    } else {despesas.append("");}
                    if (dizimistas[20*(pagina-1)+i].isEmpty() && despesas[20*(pagina-1)+i].isEmpty()){i=imax;}
                    i=i+1;
                }

                if (pagina==paginas){
                    painter.setFont(bold2);
                    painter.drawText(280,670,"MISSÃO:");
                    painter.drawText(280,690,"OFERTA:");
                    painter.drawText(280,710,"VOTO:");
                    painter.drawText(280,730,"CONSTRUÇÃO:");

                    painter.drawText(420,670,QLocale().toCurrencyString(totalmissao));
                    painter.drawText(420,690,QLocale().toCurrencyString(totaloferta));
                    painter.drawText(420,710,QLocale().toCurrencyString(totalvoto));
                    painter.drawText(420,730,QLocale().toCurrencyString(totalconstrucao));

                    painter.drawText(280,750,"TOTAL:");
                    if (total>0){painter.setPen(Qt::darkGreen);}
                    if (total<0){painter.setPen(Qt::red);}
                    painter.drawText(420,750,QLocale().toCurrencyString(total));
                }
            }

            painter.end();
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));
        }

        if (exportar.CapaMensal()==1){

            QString datacapa = exportar.TRelatorioMensal();
            nomearquivo = (datacapa.replace("/",".")).toUpper() + (" Capa.pdf");
            QString dirarquivo = diretorio + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            QPainter painter(&printer);
            painter.setFont(QFont("Arial",11));

            QString TituloCab = Igreja;
            QString SegTituloCab = Rua + " - " + Bairro + " - " + Cidade + ", " + UF;

            //Logo
            QRect rectlogo = QRect(60,20,90,90);
            painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

            //Cabeçalho
            painter.setPen(Qt::gray);
            painter.drawText(180,70,TituloCab);
            painter.drawText(180,85,SegTituloCab);

            //Rodapé
            painter.drawLine(60,760,510,760);

            //Titulo
            QFont bold("Arial", 32);
            bold.setBold(true);
            painter.setPen(Qt::black);
            painter.setFont(bold);
            painter.drawLine(60,155,510,155);
            QStringList DataCapa = datacapa.split(".");
            painter.drawText(230,400,DataCapa[0].toUpper());
            painter.drawText(280,450,DataCapa[1].toUpper());

            painter.end();

            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));

        }

        if (exportar.RelatorioMensal()==1){
            MainWindow::on_Novo_clicked();
            QString TRelatorioMensal = exportar.TRelatorioMensal();
            QTableWidget tabela;
            QString dir = QDir::homePath() + ("/Documents/TonBot/2019/") + TRelatorioMensal.split("/").first() + "/";
            dir.replace("/","\\");

            QString nometabela = (("TonBot   -   [") + TRelatorioMensal + "]");
            setWindowTitle(nometabela);

            QList<QStringList> lista;
            QString linha;

            QDirIterator it(dir, QStringList() << "*Dados.txt", QDir::Files);
            while (it.hasNext()){
                QFile arquivo(it.next());
                QTextStream texto(&arquivo);
                if (arquivo.open(QIODevice::ReadOnly)){
                    while (!texto.atEnd()) {
                        linha = texto.readLine();
                        lista << linha.split(".");
                    }
                }
            }
            for ( int linha=0; linha<lista.size();++linha ) {
                ui->Tabela->insertRow(linha);
                for (int coluna=0; coluna<6; ++coluna) {
                    ui->Tabela->setItem(linha, coluna, new QTableWidgetItem(lista[linha][coluna]));
                }
            }
            MainWindow::Atualizar();
            MainWindow::NomeSobrenome();
            //Imprimir
            nomearquivo = TRelatorioMensal.split("/").first().toUpper() + " de " + TRelatorioMensal.split("/").last() + (" Relatório Mensal.pdf");
            QString dirarquivo = dir + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF, Responsavel;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();
            Responsavel = prefs.Responsavel();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            //Início
            QStringList dizimistas;
            QString dizimovalor;

            int i, j;
            int imax = 25;

            for (int k = 0; k<ui->Tabela->rowCount();++k){
                dizimovalor = (ui->Tabela->model()->index(k,1).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                if ((dizimovalor.toFloat()>0) && !(ui->Tabela->item(k,1)->text().contains("-"))){
                    dizimistas.append(ui->Tabela->item(k,0)->text());
                }
            }

            QPainter painter(&printer);

            int paginas = (dizimistas.size()/50);
            if (dizimistas.size()%50!=0){
                paginas+=1;
            }
            for (int pagina=1; pagina<=paginas; ++pagina){
                if (pagina!=1){printer.newPage();}
                //Logo
                QRect rectlogo = QRect(60,20,90,90);
                painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

                //Cabeçalho
                painter.setFont(QFont("Arial",11));
                painter.setPen(Qt::gray);
                painter.drawText(180,70,Igreja);
                painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

                //Rodapé
                painter.drawLine(60,760,510,760);
                painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

                //Titulo
                QFont bold("Arial", 16);
                bold.setBold(true);
                painter.setPen(Qt::black);
                painter.setFont(bold);
                painter.drawLine(60,133,510,133);
                painter.drawLine(60,155,510,155);
                painter.drawText(180,150,"LISTA DE DIZIMISTAS MENSAL");
                painter.setFont(QFont("Arial",13));
                QString titulo = TRelatorioMensal.split("/").first() + " de " + TRelatorioMensal.split("/").last();
                titulo.replace(0,1,titulo[0].toUpper());
                painter.drawText(380,170,titulo);

                //Nomes
                painter.setFont(QFont("Arial",14));
                dizimistas.append("");
                for (j=0; j<=1; ++j){
                    i=0;
                    while (i<imax){
                        if (!dizimistas[50*(pagina-1)+25*j+i].isEmpty()){
                            painter.drawText(100+(j*240),210+i*22,dizimistas[50*(pagina-1)+25*j+i]);
                        } else {
                            i=imax; j=2;
                        }
                        i=i+1;
                    }
                }
            }

            //Receitas
            double totaldizimo = 0, totalmissao = 0, totaloferta = 0, totalvoto = 0, totalconstrucao = 0;
            int linha2;
            QString valortemp;
            for (linha2=0; linha2<ui->Tabela->rowCount(); ++linha2){
                for (int coluna=1; coluna<=5; ++coluna){
                    valortemp = ui->Tabela->item(linha2,coluna)->text().replace(QString(","),QString(".")).split(" ").last();
                    if (ui->Tabela->item(linha2,coluna)->text().contains("-")){valortemp="0";}
                    if (coluna==1){totaldizimo+=valortemp.toDouble();}
                    if (coluna==2){totalmissao+=valortemp.toDouble();}
                    if (coluna==3){totaloferta+=valortemp.toDouble();}
                    if (coluna==4){totalvoto+=valortemp.toDouble();}
                    if (coluna==5){totalconstrucao+=valortemp.toDouble();}
                }
            }

            //Calcular total
            double total = 0, totaldespesas = 0;

            //Despesas
            QStringList Despesas;
            QStringList DespesasValores;
            int tem=0;
            double somalinha=0;
            for (linha2=0; linha2<ui->Tabela->rowCount(); ++linha2){
                for (int coluna=1; coluna<=5; ++coluna){
                    valortemp = ui->Tabela->item(linha2,coluna)->text().replace(QString(","),QString(".")).split(" ").last();
                    if (ui->Tabela->item(linha2,coluna)->text().contains("-")){
                        somalinha+=-1*valortemp.toDouble();
                        tem=1;
                    }
                    if (coluna==5 && tem==1){
                        Despesas.append(ui->Tabela->item(linha2,0)->text());
                        DespesasValores.append(QString::number(somalinha));
                        totaldespesas+=somalinha;
                        somalinha=0;
                        tem=0;
                    }
                }
            }

            total += totaldizimo+totalvoto+totalmissao+totalconstrucao+totaloferta+totaldespesas;

            //Imprimir receitas e despesas
            int tamanhodespesas = Despesas.size();
            int paginas2=1;
            if (tamanhodespesas>16){
                paginas2 += (Despesas.size()-16)/23;
                if (!((Despesas.size()-16)%23==0)){
                    paginas2 += 1;
                }
            }

            Despesas.append("");
            DespesasValores.append("");

            for (int pagina2=1; pagina2<=paginas2; ++pagina2){
                printer.newPage();
                QRect rectlogo = QRect(60,20,90,90);
                painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));
                //Logo

                //Cabeçalho
                painter.setFont(QFont("Arial",11));
                painter.setPen(Qt::gray);
                painter.drawText(180,70,Igreja);
                painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

                //Rodapé
                painter.drawLine(60,760,510,760);
                painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

                //Titulo
                QFont bold("Arial", 16);
                bold.setBold(true);
                painter.setPen(Qt::black);
                painter.setFont(bold);
                painter.drawLine(60,133,510,133);
                painter.drawLine(60,155,510,155);
                painter.drawText(250,150,"FINANÇAS");
                painter.setFont(QFont("Arial",13));
                QString titulo = TRelatorioMensal.split("/").first() + " de " + TRelatorioMensal.split("/").last();
                titulo.replace(0,1,titulo[0].toUpper());
                painter.drawText(380,170,titulo);

                painter.setFont(bold);
                if (pagina2==paginas2){
                    painter.drawText(100,750,"TOTAL:");
                    if (total>0){painter.setPen(Qt::darkGreen);}
                    if (total<0){painter.setPen(Qt::red);}
                    painter.drawText(400,750,QLocale().toCurrencyString(total));
                }

                painter.setPen(Qt::black);
                if (pagina2==1){
                    //Imprimir subtitulos
                    painter.drawText(100,210,"RECEITAS:");
                    painter.drawText(100,360,"DESPESAS:");

                    //Imprimir receitas
                    painter.setFont(QFont("Arial",14));
                    painter.drawText(100,230,"DÍZIMOS:");
                    painter.drawText(100,250,"MISSÃO:");
                    painter.drawText(100,270,"OFERTA:");
                    painter.drawText(100,290,"VOTO:");
                    painter.drawText(100,310,"CONSTRUÇÃO:");

                    painter.drawText(400,230,QLocale().toCurrencyString(totaldizimo));
                    painter.drawText(400,250,QLocale().toCurrencyString(totalmissao));
                    painter.drawText(400,270,QLocale().toCurrencyString(totaloferta));
                    painter.drawText(400,290,QLocale().toCurrencyString(totalvoto));
                    painter.drawText(400,310,QLocale().toCurrencyString(totalconstrucao));

                    //Imprimir despesas
                    imax=Despesas.size();
                    i=0;
                    while (i<imax && i<16){
                        if (!Despesas[i].isEmpty()){
                            painter.setPen(Qt::black);
                            painter.drawText(100,380+i*22,Despesas[i]);
                            painter.setPen(Qt::red);
                            painter.drawText(400,380+i*22,QLocale().toCurrencyString(DespesasValores[i].toDouble()));
                        } else {
                            i=imax;
                        }
                        i=i+1;
                    }
                } else {
                    painter.setFont(QFont("Arial",14));
                    //Continuar despesas
                    imax=Despesas.size();
                    i=0;
                    if (pagina2==2){
                        while ((16+i)<imax && i<23){
                            if (!Despesas[16+i].isEmpty()){
                                painter.setPen(Qt::black);
                                painter.drawText(100,210+i*22,Despesas[16+i]);
                                painter.setPen(Qt::red);
                                painter.drawText(400,210+i*22,QLocale().toCurrencyString(DespesasValores[16+i].toDouble()));
                            } else {
                                i=imax;
                            }
                            i=i+1;
                        }
                    } else {
                        while ((16+23*(pagina2-2)+i)<imax && i<23){
                            if (!Despesas[16+23*(pagina2-2)+i].isEmpty()){
                                painter.setPen(Qt::black);
                                painter.drawText(100,210+i*22,Despesas[16+23*(pagina2-2)+i]);
                                painter.setPen(Qt::red);
                                painter.drawText(400,210+i*22,QLocale().toCurrencyString(DespesasValores[16+23*(pagina2-2)+i].toDouble()));
                            } else {
                                i=imax;
                            }
                            i=i+1;
                        }
                    }
                }
            }
            painter.end();
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));

            QFile arquivo(QDir::homePath() + "/Documents/TonBot/2019/" + TRelatorioMensal.split("/").first() + " Dados.txt");
            if (arquivo.open(QIODevice::WriteOnly)) {
                QTextStream stream(&arquivo);
                stream << "RECEITAS." << QLocale().toCurrencyString(totaldizimo).replace(".","") << "." << QLocale().toCurrencyString(totalmissao).replace(".","")
                       << "." << QLocale().toCurrencyString(totaloferta).replace(".","") << "." << QLocale().toCurrencyString(totalvoto).replace(".","")
                       << "." << QLocale().toCurrencyString(totalconstrucao).replace(".","") << "." << '\n';
                stream << "DESPESAS." << QLocale().toCurrencyString(totaldespesas).replace(".","") << "." << 0 << "." << 0 << "." << 0 << "." << 0 << "." << '\n';
            }

            ui->Salvar->setEnabled(false);
            ui->Salvar->setStyleSheet("border-image: url(:/imgs/imgs/salvarpb.png);" "margin: 10px;");
            ui->Adicionar->setEnabled(false);
            ui->Adicionar->setStyleSheet("border-image: url(:/imgs/imgs/adicionarpb.png);" "margin: 10px;");
            ui->Remover->setEnabled(false);
            ui->Remover->setStyleSheet("border-image: url(:/imgs/imgs/removerpb.png);" "margin: 10px;");
            ui->Remover->setToolTip("");
            ui->Salvar->setToolTip("");
            ui->Adicionar->setToolTip("");

        }

        if (exportar.RelatorioAnual()==1){
            MainWindow::on_Novo_clicked();
            QString TRelatorioAnual = exportar.TRelatorioAnual();
            QTableWidget tabela;
            QString dir = QDir::homePath() + "/Documents/TonBot/" + TRelatorioAnual + "/";
            dir.replace("/","\\");

            QString nometabela = (("TonBot   -   [") + TRelatorioAnual + "]");
            setWindowTitle(nometabela);

            QList<QStringList> lista;
            QString linha;

            QDirIterator it(dir, QStringList() << "*Dados.txt", QDir::Files);
            while (it.hasNext()){
                QFile arquivo(it.next());
                QTextStream texto(&arquivo);
                if (arquivo.open(QIODevice::ReadOnly)){
                    while (!texto.atEnd()) {
                        linha = texto.readLine();
                        lista << linha.split(".");
                    }
                    for ( int linha=0; linha<lista.size();++linha ) {
                        ui->Tabela->insertRow(linha);
                        for (int coluna=0; coluna<6; ++coluna) {
                            ui->Tabela->setItem(linha, coluna, new QTableWidgetItem(lista[linha][coluna]));
                        }
                    }
                }
            }
            MainWindow::Atualizar();
            //Imprimir
            nomearquivo = TRelatorioAnual + (" Relatório Anual.pdf");
            QString dirarquivo = dir + nomearquivo;
            dirarquivo = QFileDialog::getSaveFileName(this, ("Salvar arquivo"),dirarquivo,("Documentos (*.pdf)"));

            QString Igreja, Rua, Bairro, Cidade, UF, Responsavel;
            Preferencias prefs;
            prefs.VerificarConfiguracoes();

            Igreja = prefs.Igreja();
            Rua = prefs.Rua();
            Bairro = prefs.Bairro();
            Cidade = prefs.Cidade();
            UF = prefs.UF();
            Responsavel = prefs.Responsavel();

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFileName(dirarquivo);
            printer.setPageSize(QPrinter::A4);
            printer.setOrientation(QPrinter::Portrait);
            printer.setFullPage(false);

            QPainter painter(&printer);

            //Logo
            QRect rectlogo = QRect(60,20,90,90);
            painter.drawImage(rectlogo,QImage(":/imgs/imgs/adlogopb.jpg"));

            //Cabeçalho
            painter.setFont(QFont("Arial",11));
            painter.setPen(Qt::gray);
            painter.drawText(180,70,Igreja);
            painter.drawText(180,85,Rua + (" - ") + (Bairro) + (" - ") + (Cidade) + (", ") + (UF));

            //Rodapé
            painter.drawLine(60,760,510,760);
            painter.drawText(310,770,(("RESPONSÁVEL: ")+Responsavel));

            //Titulo
            QFont bold("Arial", 16);
            bold.setBold(true);
            painter.setPen(Qt::black);
            painter.setFont(bold);
            painter.drawLine(60,133,510,133);
            painter.drawLine(60,155,510,155);
            painter.drawText(200,150,"RELATÓRIO ANUAL");
            painter.drawText(420,170,TRelatorioAnual);

            MainWindow::NomeSobrenome();

            //Nomes
            painter.setFont(bold);
            painter.drawText(80,250,"DÍZIMOS:");
            painter.drawText(80,300,"MISSÃO:");
            painter.drawText(80,350,"OFERTA:");
            painter.drawText(80,400,"VOTO:");
            painter.drawText(80,450,"CONSTRUÇÃO:");
            painter.drawText(80,500,"DESPESAS:");
            painter.drawText(80,600,"TOTAL:");

            painter.drawText(380,250,QLocale().toCurrencyString(ui->Tabela->item(1,1)->text().split(" ").last().replace(",",".").toDouble()));
            painter.drawText(380,300,QLocale().toCurrencyString(ui->Tabela->item(1,2)->text().split(" ").last().replace(",",".").toDouble()));
            painter.drawText(380,350,QLocale().toCurrencyString(ui->Tabela->item(1,3)->text().split(" ").last().replace(",",".").toDouble()));
            painter.drawText(380,400,QLocale().toCurrencyString(ui->Tabela->item(1,4)->text().split(" ").last().replace(",",".").toDouble()));
            painter.drawText(380,450,QLocale().toCurrencyString(ui->Tabela->item(1,5)->text().split(" ").last().replace(",",".").toDouble()));
            painter.setPen(Qt::red);
            painter.drawText(380,500,"-" + QLocale().toCurrencyString(ui->Tabela->item(0,1)->text().split(" ").last().replace(",",".").toDouble()));
            double total=0;
            for (int i=0; i<=1; i++){for (int j=1; j<=5; j++){total+=ui->Tabela->item(i,j)->text().split(" ").last().replace(",",".").toDouble();}}
            if (total>0){painter.setPen(Qt::darkGreen);}
            if (total<0){painter.setPen(Qt::red);}
            painter.drawText(380,600,QLocale().toCurrencyString(total));

            painter.end();
            QDesktopServices::openUrl(QUrl::fromLocalFile(dirarquivo));

            ui->Salvar->setEnabled(false);
            ui->Salvar->setStyleSheet("border-image: url(:/imgs/imgs/salvarpb.png);" "margin: 10px;");
            ui->Adicionar->setEnabled(false);
            ui->Adicionar->setStyleSheet("border-image: url(:/imgs/imgs/adicionarpb.png);" "margin: 10px;");
            ui->Remover->setEnabled(false);
            ui->Remover->setStyleSheet("border-image: url(:/imgs/imgs/removerpb.png);" "margin: 10px;");
        }
    }
}

void MainWindow::on_Novo_clicked() {
    ui->Tabela->setRowCount(0);
    setWindowTitle(("TonBot   -   [") + (QDateTime::currentDateTime().toString("MM-dd HH-mm ")) + ("Dados.txt]"));

    ui->Salvar->setEnabled(true);
    ui->Adicionar->setEnabled(true);
    ui->Salvar->setStyleSheet("border-image: url(:/imgs/imgs/salvar.png);" "margin: 10px;");
    ui->Adicionar->setStyleSheet("border-image: url(:/imgs/imgs/adicionarenv.png);" "margin: 10px;");
    ui->Remover->setEnabled(true);
    ui->Remover->setStyleSheet("border-image: url(:/imgs/imgs/removerenv.png);" "margin: 10px;");
}

void MainWindow::NomeSobrenome(){
    QString tirarprefixotemp, tirarprefixotemp2, prefixo, prefixo2;
    double valor1, valor2, somavalor;
    QString texto1, texto2, somatexto;
    for (int linha=0; linha<(ui->Tabela->rowCount()-1); ++linha){
        prefixo = ui->Tabela->item(linha,0)->text().split(" ").first();
        tirarprefixotemp = ui->Tabela->item(linha,0)->text();
        if ((prefixo=="DC") || (prefixo=="PB") || (prefixo=="EV") || (prefixo=="PR")){tirarprefixotemp.remove(0,3);}
        for (int linha2=linha+1; linha2<ui->Tabela->rowCount(); ++linha2){
            prefixo2 = ui->Tabela->item(linha2,0)->text().split(" ").first();
            tirarprefixotemp2 = ui->Tabela->item(linha2,0)->text();
            if ((prefixo2=="DC") || (prefixo2=="PB") || (prefixo2=="EV") || (prefixo2=="PR")){tirarprefixotemp2.remove(0,3);}
            if (tirarprefixotemp==tirarprefixotemp2){
                for (int coluna=1; coluna<=5; ++coluna){
                    texto1 = (ui->Tabela->model()->index(linha,coluna).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                    valor1 = texto1.toDouble();
                    if (ui->Tabela->item(linha,coluna)->text().contains("-")){valor1=valor1*-1;}

                    texto2 = (ui->Tabela->model()->index(linha2,coluna).data().toString()).replace(QString(","),QString(".")).split(" ").last();
                    valor2 = texto2.toDouble();
                    if (ui->Tabela->item(linha2,coluna)->text().contains("-")){valor2=valor2*-1;}

                    somavalor = valor1+valor2;

                    somatexto = QLocale().toCurrencyString(somavalor);
                    if (somatexto.contains(".",Qt::CaseSensitive)) {somatexto.replace(".", "", Qt::CaseSensitive);}
                    ui->Tabela->item(linha,coluna)->setText(somatexto);
                }
                ui->Tabela->removeRow(linha2);
                linha2-=1;
            }
        }
    }
}

void MainWindow::on_Calendario_clicked() {
    Calendario calendario;
    calendario.exec();

    QString datacalendario = calendario.AbrirData();

    if (!datacalendario.isEmpty()){
        MainWindow::on_Novo_clicked();
        QTableWidget tabela;
        QString linha;
        QList<QStringList> lista;
        QString dir = QDir::homePath() + ("/Documents/TonBot/") + datacalendario.split(" ").first();

        QDirIterator it(dir, QStringList() << datacalendario.split(" ").last()+"*Dados.txt", QDir::Files);
        while (it.hasNext()){
            QFile arquivo(it.next());
            QTextStream texto(&arquivo);
            if (arquivo.open(QIODevice::ReadOnly)){
                while (!texto.atEnd()) {
                    linha = texto.readLine();
                    lista << linha.split(".");
                }
            }
        }
        for ( int linha=0; linha<lista.size();++linha ) {
            ui->Tabela->insertRow(linha);
            for (int coluna=0; coluna<6; ++coluna) {
                ui->Tabela->setItem(linha, coluna, new QTableWidgetItem(lista[linha][coluna]));
            }
        }
        MainWindow::Atualizar();
        MainWindow::NomeSobrenome();

        setWindowTitle(("TonBot   -   [") + datacalendario.split(" ").last() + (" Dados.txt]"));

        ui->Salvar->setEnabled(false);
        ui->Salvar->setStyleSheet("border-image: url(:/imgs/imgs/salvarpb.png);" "margin: 10px;");
        ui->Adicionar->setEnabled(false);
        ui->Adicionar->setStyleSheet("border-image: url(:/imgs/imgs/adicionarpb.png);" "margin: 10px;");
        ui->Remover->setEnabled(false);
        ui->Remover->setStyleSheet("border-image: url(:/imgs/imgs/removerpb.png);" "margin: 10px;");
        ui->Remover->setToolTip("");
        ui->Salvar->setToolTip("");
        ui->Adicionar->setToolTip("");

    }
}
