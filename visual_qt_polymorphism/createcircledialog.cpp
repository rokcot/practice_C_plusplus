#include "createcircledialog.h"
#include "ui_createcircledialog.h"

CreateCircleDialog::CreateCircleDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateCircleDialog)
{
    ui->setupUi(this);
}

CreateCircleDialog::~CreateCircleDialog()
{
    delete ui;
}
