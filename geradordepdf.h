#ifndef GERADORDEPDF_H
#define GERADORDEPDF_H

#include <QDialog>

namespace Ui {
class GeradordePDF;
}

class GeradordePDF : public QDialog
{
    Q_OBJECT

public:
    explicit GeradordePDF(QWidget *parent = nullptr);
    ~GeradordePDF();

private:
    Ui::GeradordePDF *ui;
};

#endif // GERADORDEPDF_H
