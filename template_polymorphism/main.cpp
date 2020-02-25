#include <iostream>
#include <string>
#include <cmath>
#include <list>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif // _WIN32
}


class Shape
{
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual string getNumber() const = 0;
    string getName() const
    {
        return m_name;
    }

    template <typename T, typename ...Params>
    static Shape* create(Params... params)
    {
        return new T(params...);
    }

protected:
    explicit Shape(const std::string& name) : m_name(name)
    {
    }

private:
    string m_name = "figure";
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
    string getNumber() const override
    {
        return "R="+to_string(m_radius);
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
    string getNumber() const override
    {
        return "A="+to_string(m_A)+" B="+to_string(m_B)+" C="+to_string(m_C);
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
    string getNumber() const override
    {
        return "height="+to_string(m_height)+" m_width="+to_string(m_width);
    }

private:
    double m_height;
    double m_width;
};

Shape* createCircle(double radius)
{
    if (radius > 0.0)
    {
        return Shape::create<Circle>(radius);
    }
    return nullptr;
}

Shape* createTriangle(double a, double b, double c)
{
    if ((a > 0.0) && (b > 0.0) && (c > 0.0) && (a < b + c))
    {
        return Shape::create<Triangle>(a, b, c);
    }
    return nullptr;
}

Shape* createRectangle(double width, double height)
{
    if (width > 0.0 && height > 0.0)
    {
        return Shape::create<Rectangle>(width, height);
    }
    return nullptr;
}

Shape* createShape(int type)
{
    double input = 0;
    double t[3];
    switch (type)
    {
    case 1:
    {
        clearScreen();
        cout << "Введите радиус:" << endl;
        cin >> input;
        return createCircle(input);
    }
    case 2:
    {
        for (int i = 1; i <= 3; ++i)
        {
            clearScreen();
            cout << "Введите длину стороны " << i << ":" << endl;
            cin >> input;
            t[i - 1] = input;
        }
        return createTriangle(t[0], t[1], t[2]);
    }
    case 3:
    {
        clearScreen();
        cout << "Введите ширину:" << endl;
        cin >> input;
        t[0] = input;
        cout << "Введите длину:" << endl;
        cin >> input;
        t[1] = input;
        return createRectangle(t[0], t[1]);
    }

    default:
        break;
    }
    return nullptr;
}

bool selectList(int type, list<Shape*>& figure_list)
{
    switch (type)
    {
    case 4:
    {
        clearScreen();
        int step=0;
        for (auto iter = figure_list.begin(); iter != figure_list.end(); iter++)
        {
            step++;
            std::cout<<"Фигура "<<step << " "<<(*iter)->getName()<<" ("<<(*iter)->getNumber()<<": "
                    << ") - " <<"Площадь = "<< (*iter)->area() << "\n";
        }
        return true;
    }
    case 5:
    {
        int index=0;
        cout << "Введите элемент для удаления(Элементов "<<figure_list.size()<<"):" << endl;
        cin>>index;
        auto iter = figure_list.begin();
        std::advance(iter, index);
        if (iter != figure_list.end())
        {
            auto item = *iter;
            figure_list.erase(iter);
            cout<<"delete"<<endl;
            delete item;
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

int main()
{
    setlocale(0, "");
    int select = 0;
    list<Shape*> figure_list;

    while (true) {
        clearScreen();
        std::cout
            << "Что выполнить?:" << endl
            << "Создать Круг: 1" << endl
            << "Создать Треугольник: 2" << endl
            << "Создать Прямоугольник: 3" << endl
            << "Вывести все фигуры: 4" << endl
            << "Удалить фигуру: 5" << endl
            << "Выход: 6" << endl;
        cin >> select;
        if (select < 1 || select > 6)
        {
            break;
        }
        if (select < 1 || select > 3)
        {
           if (!selectList(select,figure_list))
           {
               cout<<"Error"<<endl;
           }
        }
        else
        {
            Shape* shape = createShape(select);

            if (shape)
            {
                figure_list.push_back(shape);
                std::cout << "Создана новая фигура! площадь которого:" << shape->area() << std::endl;
            }
            else
            {
                std::cout << "Не удалось создать фигуру" << std::endl;
            }
        }
        system("pause");
    }
    return 0;
}
