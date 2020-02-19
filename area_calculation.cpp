#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Shape
{
public:
	virtual double area() const = 0;
	string getName() const
	{
		return m_name;
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
private:
	int m_radius;
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

private:
	double m_height;
	double m_width;
};

Shape* createCircle(double radius)
{
	if (radius > 0.0)
	{
		Circle* circle = new Circle(radius);
		return circle;
	}
	return nullptr;
}

Shape* createTriangle(double a, double b, double c)
{
	if ((a > 0.0) && (b > 0.0) && (c > 0.0) && (a > b + c))
	{
		Triangle* triangle = new Triangle(a, b, c);
		return triangle;
	}
	return nullptr;
}

Shape* createRectangle(double width, double height)
{
	if (width > 0.0 && height > 0.0)
	{
		Rectangle* rectangle = new Rectangle(width, height);
		return rectangle;
	}
	return nullptr;
}

Shape* createShape(int type)
{
	double input = 0;
	double t[2];
	switch (type)
	{
	case 1:
	{
		system("cls");
		cout << "Введите радиус:" << endl;
		cin >> input;
		return createCircle(input);
	}
	case 2:
	{
		for (int i = 1; i <= 3; ++i)
		{
			system("cls");
			cout << "Введите длину стороны " << i << ":" << endl;
			cin >> input;
			t[i - 1] = input;
		}
		return createTriangle(t[0], t[1], t[2]);
	}
	case 3:
	{
		system("cls");
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


int main()
{
	setlocale(0, "");
	int select = 0;
	
	while (true) {
		system("cls");
		std::cout
			<< "Какой объект создать?:" << endl
			<< "Круг: 1" << endl
			<< "Треугольник: 2" << endl
			<< "Прямоугольник: 3" << endl
			<< "Выход: 4" << endl;
		cin >> select;
		if (select < 1 || select > 3)
		{
			break;
		}
		Shape* shape = createShape(select);
		if (shape)
		{
			std::cout << "Площадь:" << shape->area() << std::endl;
		}
		else
		{
			std::cout << "Не удалось создать фигуру" << std::endl;
		}
		system("pause");
	}
	return 0;
}