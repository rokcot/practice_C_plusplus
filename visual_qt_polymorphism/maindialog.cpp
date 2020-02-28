#include "maindialog.h"
#include "ui_maindialog.h"

#include <QMenu>

#include "createcircledialog.h"
#include "createtriangledialog.h"
#include "createrectangledialog.h"
#include "deletedialog.h"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
    , m_createMenu(nullptr)
{
    ui->setupUi(this);

    m_createMenu = new QMenu(ui->addButton);
    m_createMenu->addAction("Создать окружность", this, &MainDialog::createCircle);
    m_createMenu->addAction("Создать треугольник", this, &MainDialog::createTriangle);
    m_createMenu->addAction("Создать прямоугольник", this, &MainDialog::createRectangle);
    ui->addButton->setMenu(m_createMenu);

    connect(ui->listButton, &QPushButton::clicked, this, &MainDialog::getShape);
    connect(ui->delButton, &QPushButton::clicked, this, &MainDialog::delShape);
    connect(ui->clearButton, &QPushButton::clicked, this, &MainDialog::clearLog);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainDialog::generateShape);

}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::clearLog()
{
    ui->logText->setPlainText("");
}

void MainDialog::generateShape()
{
    for(int i=0;i<100;i++)
    {
        int rnd =  qrand() % 3 +1;
        switch (rnd)
        {
        case 1:
        {
            int radius =  qrand() % 10 +1;
            if (radius > 0.0)
            {
                auto shape = Shape::create<Circle>(radius);
                figure_list.push_back(shape);
            }
            break;
        }
        case 2:
        {
            int A = qrand() % 10 +1;
            int B = qrand() % (A+3) + A;
            int C = qrand() % (B+3) + B;
            if ((A > 0.0) && (B > 0.0) && (C > 0.0) && (A < B + C))
            {
                auto shape = Shape::create<Triangle>(A,B,C);
                figure_list.push_back(shape);
            }
            break;
        }
        case 3:
        {
            int height = qrand() % 10 +1;
            int width = qrand() % 10 +1;
            if (width > 0.0 && height > 0.0)
            {
                auto shape = Shape::create<Rectangle>(width,height);
                figure_list.push_back(shape);
            }
            break;
        }
        default:
            break;
        }
    }
}

void MainDialog::delShape()
{
    DeleteDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        int start = dialog.first();
        int count = dialog.count();

        auto iter = figure_list.begin();
        std::advance(iter, start);
        for(int i=0;i<count;i++)
        {
            if (iter != figure_list.end())
            {
                auto item = *iter;
                figure_list.erase(iter);
                qDebug()<<"delete"<<endl;
            }
        }
    }
    else
    {
        qDebug("REJECTED");
    }
}

void MainDialog::getShape()
{
    int step=0;
    QString temp="";
    for (auto iter = figure_list.begin(); iter != figure_list.end(); iter++)
    {
        step++;
        temp+="Фигура "+QString::number(step)+" "+(*iter)->getName()+" ("+(*iter)->getNumber()+": "
                                  +") - "+"Площадь = "+QString::number((*iter)->area())+"\r\n";
    }
    ui->logText->setPlainText(temp);
}

void MainDialog::createCircle()
{
    CreateCircleDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        qreal radius = dialog.radius();
        if (radius > 0.0)
        {
            auto shape = Shape::create<Circle>(radius);
            figure_list.push_back(shape);
            qDebug()<< "Создана новая фигура! площадь которого:"
                    << shape->area();
        }
    }
    else
    {
        qDebug("REJECTED");
    }
}

void MainDialog::createTriangle()
{
    CreateTriangleDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        qreal A = dialog.A();
        qreal B = dialog.B();
        qreal C = dialog.C();
        if ((A > 0.0) && (B > 0.0) && (C > 0.0) && (A < B + C))
        {
            auto shape = Shape::create<Triangle>(A,B,C);
            figure_list.push_back(shape);
            qDebug()<< "Создана новая фигура! площадь которого:"
                    << shape->area();
        }
    }
    else
    {
        qDebug("REJECTED");
    }
}

void MainDialog::createRectangle()
{
    CreateRectangleDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        qreal width = dialog.widthShape();
        qreal height = dialog.heigthShape();
        if (width > 0.0 && height > 0.0)
        {
            auto shape = Shape::create<Rectangle>(width,height);
            figure_list.push_back(shape);
            qDebug()<< "Создана новая фигура! площадь которого:"
                    << shape->area();
        }
    }
    else
    {
        qDebug("REJECTED");
    }
}
