#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QSharedPointer>
#include <QThread>

QT_BEGIN_NAMESPACE
class Shape;
QT_END_NAMESPACE
typedef QSharedPointer<Shape> ShapePtr;

class DataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DataModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addCircle(qreal radius);
    void addTriangle(qreal a, qreal b, qreal c);
    void addRectangle(qreal width, qreal height);
    void delShape(int start, int count);
    void generateShape();
    void generateShapeWithStep();
    void getRandToGenerate();


private:
    QVector<ShapePtr> m_figureList;
};

#endif // DATAMODEL_H
