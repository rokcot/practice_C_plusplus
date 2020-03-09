#include "datamodel.h"

#include <QDebug>
#include <QTime>
#include <QtMath>

template <typename T>
T getRandom(T lower, T upper)
{
    return  lower + static_cast <T> (qrand()) /
            (static_cast <T> (RAND_MAX/(upper-lower)));
}

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


class Circle : public Shape
{
public:
    Circle(double r) : Shape("circle"), m_radius(r)
    {
    }
    double area() const override
    {
        return M_PI * m_radius * m_radius;
    }
    QString getNumber() const override
    {
        return "R="+QString::number(m_radius);
    }
private:
    double m_radius;
};
class Triangle : public Shape
{
public:
    Triangle(double a, double b, double c) : Shape("triangle"), m_A(a), m_B(b), m_C(c)
    {
    }
    double area() const override
    {
        double s = (m_A + m_B + m_C) / 2;
        double p = qPow(s * (s - m_A) * (s - m_B) * (s - m_C), 0.5);
        return p;
    }
    QString getNumber() const override
    {
        return "A=" + QString::number(m_A) + " B=" + QString::number(m_B) +
                " C="+QString::number(m_C);
    }
private:
    double m_A = 0;
    double m_B = 0;
    double m_C = 0;
};
class Rectangle : public Shape
{
public:
    Rectangle(double w, double h) : Shape("rectangle"), m_height(h), m_width(w)
    {}

    double area() const override
    {
        return m_height * m_width;
    }
    QString getNumber() const override
    {
        return "height=" + QString::number(m_height) +
                " m_width=" + QString::number(m_width);
    }

private:
    double m_height;
    double m_width;

};

DataModel::DataModel(QObject *parent) : QAbstractListModel(parent)
{
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_figureList.count();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= rowCount())
    {
        return QVariant();
    }
    const auto& shape = m_figureList.at(index.row());
    switch (role)
    {
    case Qt::DisplayRole:
    {
        if (shape)
        {
            return shape->getName() + ": " + shape->getNumber() +
                    " - " + "Площадь = " + QString::number(shape->area());
        }
        break;
    }
    case ItemDataRole::NameRole:
        if (shape)
        {
            return shape->getName();
        }
        break;
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> result = {
        { Qt::DisplayRole, "text" },
        { ItemDataRole::NameRole, "name" }
    };
    return result;
}

void DataModel::addCircle(qreal radius)
{
    if (radius > 0.0)
    {
        beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
        auto shape = Shape::create<Circle>(radius);
        m_figureList.push_back(shape);
        qDebug()<< "Создана новая фигура! площадь которого:"
                << shape->area();
        endInsertRows();
    }
}

void DataModel::addTriangle(qreal a, qreal b, qreal c)
{
    if ((a > 0.0) && (b > 0.0) && (c > 0.0) && (a < b + c))
    {
        beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
        auto shape = Shape::create<Triangle>(a, b, c);
        m_figureList.push_back(shape);
        qDebug()<< "Создана новая фигура! площадь которого:"
                << shape->area();
        endInsertRows();
    }
}

void DataModel::addRectangle(qreal width, qreal height)
{
    if (width > 0.0 && height > 0.0)
    {
        beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
        auto shape = Shape::create<Rectangle>(width, height);
        m_figureList.push_back(shape);
        endInsertRows();
        qDebug()<< "Создана новая фигура! площадь которого:"
                << shape->area();

    }
}

void DataModel::delShape(int start, int count)
{
    auto iter = m_figureList.begin();
    std::advance(iter, start);
    beginRemoveRows(QModelIndex(), start, start + count - 1);
    for(int i = 0; i < count; i++)
    {
        if (iter != m_figureList.end())
        {
            auto item = *iter;
            m_figureList.erase(iter);
        }
    }
    endRemoveRows();
}

void DataModel::generateShape()
{
    qsrand (static_cast <uint> (QTime::currentTime().msec()));
    int i = 100;
    while(i>0)
    {
        switch (1 + qrand() % 3)
        {
        case 1:
        {
            double radius = getRandom<double>(0.0,10.0);
            if (radius > 0.0)
            {
                beginInsertRows(QModelIndex(),
                                m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Circle>(radius);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            else
            {
                continue;
            }

            break;
        }
        case 2:
        {
            double a = getRandom<double>(0.0,10.0);
            double b = getRandom<double>(0.0,10.0);
            double c = getRandom<double>(0.0,10.0);
            if ((a > 0.0) && (b > 0.0) && (c > 0.0) && (a < b + c))
            {
                beginInsertRows(QModelIndex(),
                                m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Triangle>(a, b, c);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            else
            {
                continue;
            }

            break;
        }
        case 3:
        {
            double height = getRandom<double>(0.0,10.0);
            double width = getRandom<double>(0.0,10.0);
            if (width > 0.0 && height > 0.0)
            {
                beginInsertRows(QModelIndex(),
                                m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Rectangle>(width, height);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            else
            {
                continue;
            }

            break;
        }
        default:
            break;
        }
        --i;
    }

}

