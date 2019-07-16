#ifndef IMPRESSOES_H
#define IMPRESSOES_H

#include <QDialog>

namespace Ui {
class Impressoes;
}

class Impressoes : public QDialog
{
    Q_OBJECT

public:
    explicit Impressoes(QWidget *parent = nullptr);
    ~Impressoes();

private slots:
    void on_Fechar_clicked();

private:
    Ui::Impressoes *ui;
};

#endif // IMPRESSOES_H
