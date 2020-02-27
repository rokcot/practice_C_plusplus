#include "createrectangledialog.h"
#include "ui_createrectangledialog.h"

CreateRectangleDialog::CreateRectangleDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateRectangleDialog)
{
    ui->setupUi(this);
}

CreateRectangleDialog::~CreateRectangleDialog()
{
    delete ui;
}
