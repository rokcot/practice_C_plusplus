#ifndef CREATETRIANGLEDIALOG_H
#define CREATETRIANGLEDIALOG_H

#include <QWidget>

namespace Ui {
class CreateTriangleDialog;
}

class CreateTriangleDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateTriangleDialog(QWidget *parent = nullptr);
    ~CreateTriangleDialog();

private:
    Ui::CreateTriangleDialog *ui;
};

#endif // CREATETRIANGLEDIALOG_H
