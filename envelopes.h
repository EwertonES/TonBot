#ifndef ENVELOPES_H
#define ENVELOPES_H

#include <QDialog>

namespace Ui {
class Envelopes;
}

class Envelopes : public QDialog
{
    Q_OBJECT

public:
    explicit Envelopes(QWidget *parent = nullptr);
    ~Envelopes();

    QString Nome() const;
    double Dizimo() const;
    double Oferta() const;
    double Construcao() const;
    double Missao() const;
    double Voto() const;

private slots:
    void on_Botoes_accepted();
    void on_Botoes_rejected();

private:
    Ui::Envelopes *ui;
};

#endif // ENVELOPES_H
