#ifndef CALENDARIO_H
#define CALENDARIO_H

#include <QDialog>

namespace Ui {
class Calendario;
}

class Calendario : public QDialog
{
    Q_OBJECT

public:
    explicit Calendario(QWidget *parent = nullptr);
    ~Calendario();
    QString AbrirData() const;

private:
    Ui::Calendario *ui;
    QList<QDate> datas;
    QString abrirdata;

private slots:
    void on_calendarWidget_clicked(const QDate &date);
};
#endif // CALENDARIO_H
