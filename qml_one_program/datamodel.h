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
    enum ItemDataRole
    {
        NameRole = Qt::UserRole + 1,
        Data
    };



    explicit DataModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addCircle(qreal radius);
    Q_INVOKABLE void addTriangle(qreal a, qreal b, qreal c);
    Q_INVOKABLE void addRectangle(qreal width, qreal height);
    Q_INVOKABLE void delShape(int start, int count);
    Q_INVOKABLE void editShape(int index, const QString shap, qreal a=0.0, qreal b=0.0, qreal c=0.0);
    Q_INVOKABLE void setShapeIndex(int index);
    Q_INVOKABLE void generateShape();
//    Q_INVOKABLE void generateShapeWithStep();
//    Q_INVOKABLE void getRandToGenerate();


private:
    QVector<ShapePtr> m_figureList;
};

#endif // DATAMODEL_H
