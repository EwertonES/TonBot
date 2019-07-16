#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void UpdateDateTime();
    virtual void resizeEvent(QResizeEvent *event);

private slots:

    void on_Adicionar_clicked();
    void on_Editar_toggled(bool checked);
    void on_Remover_clicked();
    void on_Preferencias_clicked();
    void on_Sair_clicked();
    void Atualizar();
    void on_Exportar_clicked();
    void on_Salvar_clicked();
    void on_Carregar_clicked();
    void on_Novo_clicked();
    void NomeSobrenome();

    void on_Calendario_clicked();

private:

    Ui::MainWindow *ui;
    QTimer *timer_1s;

    enum Coluna {
        NOME, DIZIMO, MISSAO, OFERTA, VOTO, CONSTRUCAO
    };

};

#endif // MAINWINDOW_H
