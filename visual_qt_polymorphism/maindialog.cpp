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
    , m_dataModel(new DataModel())
{
    ui->setupUi(this);

    ui->listView->setModel(m_dataModel.get());

    m_createMenu = new QMenu(ui->addButton);
    m_createMenu->addAction("Создать окружность", this, &MainDialog::createCircle);
    m_createMenu->addAction("Создать треугольник", this, &MainDialog::createTriangle);
    m_createMenu->addAction("Создать прямоугольник", this, &MainDialog::createRectangle);
    ui->addButton->setMenu(m_createMenu);

    connect(ui->delButton, &QPushButton::clicked, this, &MainDialog::delShape);
    connect(ui->generateButton, &QPushButton::clicked, this, &MainDialog::generateShape);

}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::generateShape()
{
    m_dataModel->generateShape();
}

void MainDialog::delShape()
{
    DeleteDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        m_dataModel->delShape(dialog.first(),dialog.count());
    }
    else
    {
        qDebug("REJECTED");
    }
}


void MainDialog::createCircle()
{
    CreateCircleDialog dialog;
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug("ACCEPTED");
        m_dataModel->addCircle(dialog.radius());
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
        m_dataModel->addTriangle(dialog.A(),dialog.B(),dialog.C());
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
        m_dataModel->addRectangle(dialog.shapeWidth(),dialog.shapeHeight());
    }
    else
    {
        qDebug("REJECTED");
    }
}
