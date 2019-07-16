#ifndef ITEMDELEGATETABELA_H
#define ITEMDELEGATETABELA_H

#include <QStyledItemDelegate>
#include <QDialog>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>

namespace Ui {
class ItemDelegateTabela;
}

class ItemDelegateTabela : public QDialog
{
    Q_OBJECT

public:
    explicit ItemDelegateTabela(QWidget *parent = nullptr);
    ~ItemDelegateTabela();

private:
    Ui::ItemDelegateTabela *Ui;

    QStandardItemModel *model;
};

#endif
