#include "deletedialog.h"
#include "ui_deletedialog.h"

DeleteDialog::DeleteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog)
{
    ui->setupUi(this);
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}
int DeleteDialog::first() const
{
    return ui->deleteStartBox->value();
}
int DeleteDialog::count() const
{
    return ui->deleteCountBox->value();
}

void DeleteDialog::setFirst(const int &index)
{
    ui->deleteStartBox->setValue(index);
}

void DeleteDialog::setCount(const int &count)
{
    ui->deleteCountBox->setValue(count);
}
