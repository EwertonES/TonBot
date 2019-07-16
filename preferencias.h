#ifndef PREFERENCIAS_H
#define PREFERENCIAS_H

#include <QDialog>

namespace Ui {
class Preferencias;
}

class Preferencias : public QDialog
{
    Q_OBJECT

public:
    explicit Preferencias(QWidget *parent = nullptr);
    ~Preferencias();

    QString Igreja() const;
    QString Rua() const;
    QString Bairro() const;
    QString Cidade() const;
    QString UF() const;
    QString Pastor() const;
    QString Responsavel() const;
    void VerificarConfiguracoes();
    void Carregar();

private slots:
    void on_pushButton_clicked();



private:
    Ui::Preferencias *ui;
};

#endif // PREFERENCIAS_H
