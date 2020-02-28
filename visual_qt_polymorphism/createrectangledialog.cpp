#include "createrectangledialog.h"
#include "ui_createrectangledialog.h"

CreateRectangleDialog::CreateRectangleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRectangleDialog)
{
    ui->setupUi(this);
}

CreateRectangleDialog::~CreateRectangleDialog()
{
    delete ui;
}
qreal CreateRectangleDialog::widthShape() const
{
    return ui->doubleRectangleBoxWidth->value();
}
qreal CreateRectangleDialog::heigthShape() const
{
    return ui->doubleRectangleBoxHeigth->value();
}
