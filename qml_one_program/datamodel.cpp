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
static int idert = 0;
class Shape
{
public:
    virtual ~Shape()
    {}
    virtual double area() const = 0;
    virtual QString getNumber() const = 0;
    virtual double getData(int index) const = 0;
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
    void setRadius(double r)
    {
        m_radius = r;
    }
    double getData(int index) const override
    {
        return m_radius;
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
    void setA(double a)
    {
        m_A = a;
    }
    void setB(double b)
    {
        m_B = b;
    }
    void setC(double c)
    {
        m_C = c;
    }
    double getData(int index) const override
    {
        switch(index)
        {
        case 1:
            return m_A;
        case 2:
            return m_B;
        case 3:
            return m_C;
        default:
            return 0;
        }
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
    void setHeight(double height)
    {
        m_height = height;
    }
    void setWidth(double width)
    {
        m_width = width;
    }
    double getData(int index) const override
    {
        switch(index)
        {
        case 1:
            return m_height;
        case 2:
            return m_width;
        default:
            return 0;
        }
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
    case ItemDataRole::Data:
        if (shape)
        {
            return shape->getData(idert);
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
        { ItemDataRole::NameRole, "name" },
        { ItemDataRole::Data, "data" }
    };
    return result;
}

void DataModel::setShapeIndex(int index)
{
    idert = index;
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

void DataModel::editShape(int index, const QString shap, qreal a, qreal b, qreal c)
{

    auto shape = m_figureList.at(index);
    if(shap == "circle")
    {
        auto circle = shape.staticCast<Circle>();
        circle->setRadius(a);
        const auto modelIndex = this->index(index, 0);
        emit dataChanged(modelIndex, modelIndex, {
                             Qt::DisplayRole, ItemDataRole::NameRole
                         });
    }
    else if(shap == "rectangle")
    {
        auto rectangle = shape.staticCast<Rectangle>();
        rectangle->setWidth(a);
        rectangle->setHeight(b);
        const auto modelIndex = this->index(index, 0);
        emit dataChanged(modelIndex, modelIndex, {
                             Qt::DisplayRole, ItemDataRole::NameRole
                         });
    }
    else if(shap == "triangle")
    {
        auto triangle = shape.staticCast<Triangle>();
        triangle->setA(a);
        triangle->setB(b);
        triangle->setC(c);
        const auto modelIndex = this->index(index, 0);
        emit dataChanged(modelIndex, modelIndex, {
                             Qt::DisplayRole, ItemDataRole::NameRole
                         });
    }

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

