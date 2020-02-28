#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QSharedPointer>
#include <QTime>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
class QMenu;
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

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
    void createCircle();
    void createTriangle();
    void createRectangle();

    void getShape();
    void delShape();
    void clearLog();
    void generateShape();

    QVector<ShapePtr> figure_list;

private:
    Ui::MainDialog *ui;
    QMenu* m_createMenu;
};
#endif // MAINDIALOG_H
