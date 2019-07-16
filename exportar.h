#ifndef EXPORTAR_H
#define EXPORTAR_H

#include <QDialog>

namespace Ui {
class Exportar;
}

class Exportar : public QDialog
{
    Q_OBJECT

public:
    explicit Exportar(QWidget *parent = nullptr);
    ~Exportar();

    int Diario() const;
    int ListaDizimistas() const;
    int CapaMensal() const;
    int RelatorioMensal() const;
    int RelatorioAnual() const;
    int Construcao() const;
    QString TRelatorioAnual() const;
    QString TRelatorioMensal() const;

private slots:
    void on_pushButton_clicked();
    void Carregar();

    void on_ListaDizimistas_stateChanged();

private:
    Ui::Exportar *ui;
};

#endif // EXPORTAR_H
