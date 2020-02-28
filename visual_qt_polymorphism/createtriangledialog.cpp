#include "createtriangledialog.h"
#include "ui_createtriangledialog.h"

CreateTriangleDialog::CreateTriangleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateTriangleDialog)
{
    ui->setupUi(this);
}

CreateTriangleDialog::~CreateTriangleDialog()
{
    delete ui;
}

qreal CreateTriangleDialog::A() const
{
    return ui->doubleTriangleBoxA->value();
}
qreal CreateTriangleDialog::B() const
{
    return ui->doubleTriangleBoxB->value();
}
qreal CreateTriangleDialog::C() const
{
    return ui->doubleTriangleBoxC->value();
}
