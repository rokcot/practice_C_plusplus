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

qreal CreateTriangleDialog::a() const
{
    return ui->doubleTriangleBoxA->value();
}
qreal CreateTriangleDialog::b() const
{
    return ui->doubleTriangleBoxB->value();
}
qreal CreateTriangleDialog::c() const
{
    return ui->doubleTriangleBoxC->value();
}
