#include "createtriangledialog.h"
#include "ui_createtriangledialog.h"

CreateTriangleDialog::CreateTriangleDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateTriangleDialog)
{
    ui->setupUi(this);
}

CreateTriangleDialog::~CreateTriangleDialog()
{
    delete ui;
}
