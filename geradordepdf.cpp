#include "geradordepdf.h"
#include "ui_geradordepdf.h"
#include <QPdfWriter>
#include <QPainter>
#include <QUrl>

GeradordePDF::GeradordePDF(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeradordePDF)
{
    ui->setupUi(this);
}

GeradordePDF::~GeradordePDF()
{
    delete ui;
}
