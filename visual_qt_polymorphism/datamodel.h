#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE
class Shape;
QT_END_NAMESPACE
typedef QSharedPointer<Shape> ShapePtr;

class Shape
{
public:
    virtual ~Shape()
    {}
    virtual double area() const = 0;
    virtual QString getNumber() const = 0;
    QString getName() const
    {
        return m_name;
    }

    template <typename T, typename ...Params>
    static ShapePtr create(Params... params)
    {
        return QSharedPointer<T>::create(params...);
    }

protected:
    explicit Shape(const QString& name) : m_name(name)
    {
    }

private:
    QString m_name = "figure";
};


class DataModel : public QObject
{
    Q_OBJECT
public:
    explicit DataModel(QObject* parent = nullptr);

    void addCircle(qreal radius);
    void addTriangle(qreal A, qreal B, qreal C);
    void addRectangle(qreal width, qreal height);
    void delShape(int start, int count);
    void generateShape(int count = 100);
    QString getShape();

private:
    QVector<ShapePtr> m_figureList;
};

#endif // DATAMODEL_H
