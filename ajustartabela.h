#ifndef ITEMDELEGATEPAINT_H
#define ITEMDELEGATEPAINT_H

#include <QStyledItemDelegate>

class ItemDelegatePaint : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ItemDelegatePaint(QObject *parent = 0);
    ItemDelegatePaint(const QString &txt, QObject *parent = 0);


protected:
    void paint( QPainter *painter,
                const QStyleOptionViewItem &option,
                const QModelIndex &index ) const;
    QSize sizeHint( const QStyleOptionViewItem &option,
                    const QModelIndex &index ) const;
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget * editor, const QModelIndex & index) const;
    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;
    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;

signals:

public slots:

};

#endif // ITEMDELEGATEPAINT_H
