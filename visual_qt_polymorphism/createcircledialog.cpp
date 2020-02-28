#include "createcircledialog.h"
#include "ui_createcircledialog.h"

CreateCircleDialog::CreateCircleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCircleDialog)
{
    ui->setupUi(this);
}

CreateCircleDialog::~CreateCircleDialog()
{
    delete ui;
}

qreal CreateCircleDialog::radius() const
{
    return ui->doubleCircleBox->value();
}
