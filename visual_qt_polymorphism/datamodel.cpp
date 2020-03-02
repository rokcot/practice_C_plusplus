#include "datamodel.h"

#include <QDebug>
#include <QTime>
#include <QtMath>

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
    Circle(int r) : Shape("circle"), m_radius(r)
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
        double p = pow(s*(s - m_A)*(s - m_B)*(s - m_C), 0.5);
        return p;
    }
    QString getNumber() const override
    {
        return "A="+QString::number(m_A)+" B="+QString::number(m_B)+" C="+QString::number(m_C);
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
        return "height="+QString::number(m_height)+" m_width="+QString::number(m_width);
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
    switch (role)
    {
    case Qt::DisplayRole:
    {
        if (index.row() < 0 || index.row() >= rowCount())
        {
            return QVariant();
        }
        const auto& shape = m_figureList.at(index.row());
        if (shape)
        {
            return shape->getName() + ": " + shape->getNumber()+
                    " - "+"Площадь = "+QString::number(shape->area());
        }
        break;
    }
    default:
        break;
    }
    return QVariant();
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
//        emit dataChanged()
        endInsertRows();
    }
}

void DataModel::addTriangle(qreal A, qreal B, qreal C)
{
    if ((A > 0.0) && (B > 0.0) && (C > 0.0) && (A < B + C))
    {
        beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
        auto shape = Shape::create<Triangle>(A,B,C);
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
        auto shape = Shape::create<Rectangle>(width,height);
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
    for(int i=0;i<count;i++)
    {
        if (iter != m_figureList.end())
        {
            auto item = *iter;
            m_figureList.erase(iter);
        }
    }
    endRemoveRows();
}

void DataModel::generateShape(int count)
{
    for(int i=0;i<count;i++)
    {
        int rnd = qrand() % 3 +1;
        switch (rnd)
        {
        case 1:
        {
            int radius = qrand() % 10 +1;
            if (radius > 0.0)
            {
                beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Circle>(radius);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            break;
        }
        case 2:
        {
            int A = qrand() % 10 + 1;
            int B = qrand() % 10 + 1;
            int C = qrand() % 10 + 1;
            if ((A > 0.0) && (B > 0.0) && (C > 0.0) && (A < B + C))
            {
                beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Triangle>(A,B,C);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            break;
        }
        case 3:
        {
            int height = qrand() % 10 +1;
            int width = qrand() % 10 +1;
            if (width > 0.0 && height > 0.0)
            {
                beginInsertRows(QModelIndex(), m_figureList.count(), m_figureList.count());
                auto shape = Shape::create<Rectangle>(width,height);
                m_figureList.push_back(shape);
                endInsertRows();
            }
            break;
        }
        default:
            break;
        }
    }
}

