#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QString>
#include <QSharedPointer>
#include <QTime>
#include <QtMath>

static void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif // _WIN32
}

class Shape;
typedef QSharedPointer<Shape> ShapePtr;

class Shape
{
public:
    virtual ~Shape()
    {
        qDebug()<<"Delete"<<endl;
    }
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

static ShapePtr createCircle(double radius)
{
    if (radius > 0.0)
    {
        return Shape::create<Circle>(radius);
    }
    return nullptr;
}

static ShapePtr createTriangle(double a, double b, double c)
{
    if ((a > 0.0) && (b > 0.0) && (c > 0.0) && (a < b + c))
    {
        return Shape::create<Triangle>(a, b, c);
    }
    return nullptr;
}

static ShapePtr createRectangle(double width, double height)
{
    if (width > 0.0 && height > 0.0)
    {
        return Shape::create<Rectangle>(width, height);
    }
    return nullptr;
}

static ShapePtr createShape(int type,bool process)
{
    QTextStream in(stdin);
    double input = 0;
    double t[3];
    switch (type)
    {
    case 1:
    {
        if(!process){
            clearScreen();
            qDebug() << "Введите радиус:" ;
            in >> input;
            return createCircle(input);
        }
        else
        {
            int rnd =  qrand() % 10 +1;
            return createCircle(rnd);
        }
    }
    case 2:
    {
        if(!process)
        {
            for (int i = 1; i <= 3; ++i)
            {
                clearScreen();
                qDebug() << "Введите длину стороны " << i << ":" ;
                in >> input;
                t[i - 1] = input;
            }
            return createTriangle(t[0], t[1], t[2]);
        }
        else
        {
            int A = qrand() % 10 +1;
            int B = qrand() % (A+3) + A;
            int C = qrand() % (B+3) + B;
            return createTriangle(A, B, C);
        }
    }
    case 3:
    {
        if(!process)
        {
            clearScreen();
            qDebug() << "Введите ширину:";
            in >> input;
            t[0] = input;
            qDebug() << "Введите длину:";
            in >> input;
            t[1] = input;
            return createRectangle(t[0], t[1]);
        }
        else
        {
            int height = qrand() % 10 +1;
            int width = qrand() % 10 +1;
            return createRectangle(height, width);
        }
    }

    default:
        break;
    }
    return nullptr;
}


static bool selectList(int type, QVector<ShapePtr>& figure_list)
{
    QTextStream in(stdin);
    switch (type)
    {
    case 4:
    {
        clearScreen();
        int step=0;
        for (auto iter = figure_list.begin(); iter != figure_list.end(); iter++)
        {
            step++;
            qDebug()<<"Фигура "<<step << " "<<(*iter)->getName()<<" ("<<(*iter)->getNumber()<<": "
                    << ") - " <<"Площадь = "<< (*iter)->area();
        }
        return true;
    }
    case 5:
    {
        int index=0;
        qDebug() << "Введите элемент для удаления(Элементов "<<figure_list.size()<<"):"<< endl ;
        in>>index;
        auto iter = figure_list.begin();
        std::advance(iter, index);
        if (iter != figure_list.end())
        {
            auto item = *iter;
            figure_list.erase(iter);
            qDebug()<<"delete"<<endl;
            return true;
        }
        return false;
    }
    case 6:
    {

        for(int i=0;i<100;i++)
        {
            int rnd =  rand() % 3 +1;
            auto shape = createShape(rnd, true);
            figure_list.push_back(shape);
        }
        return false;
    }
    case 7:
    {
        if(50<figure_list.size())
        {
            int i = 50;
            auto iter = figure_list.end();
            while (i-- > 0)
            {
                --iter;
                figure_list.erase(iter);
            }
            return true;
        }
        return false;
    }
    default:
        break;
    }
    return false;
}

template <typename T>
double getArea(const T& shape)
{
    return shape.area();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"debug";
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    setlocale(0, "");
    int select = 0;

    QVector<ShapePtr> figure_list;
    QTextStream in(stdin);

    while (true)
    {
        clearScreen();
        qDebug()
            << "Что выполнить?:" << endl
            << "Создать Круг: 1"<< endl
            << "Создать Треугольник: 2"<< endl
            << "Создать Прямоугольник: 3"<< endl
            << "Вывести все фигуры: 4"<< endl
            << "Удалить фигуру: 5"<< endl
            << "Создать 100 уникальных фигур: 6"<< endl
            << "Удалить 50 случайных фигур: 7"<< endl
            << "Выход: 8"<< endl;
        in >> select;
        if (select < 1 || select > 8)
        {
            break;
        }
        if (select < 1 || select > 3)
        {
           if (!selectList(select,figure_list))
           {
              qDebug()<<"Error";
           }
        }
        else
        {
            auto shape = createShape(select,false);

            if (shape)
            {
                figure_list.push_back(shape);
                qDebug() << "Создана новая фигура! площадь которого:"
                         << shape->area();
            }
            else
            {
                qDebug() << "Не удалось создать фигуру";
            }

        }
        system("pause");
    }
//    return 0;

    return a.exec();
}
