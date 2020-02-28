#ifndef CREATETRIANGLEDIALOG_H
#define CREATETRIANGLEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateTriangleDialog;
}

class CreateTriangleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateTriangleDialog(QWidget *parent = nullptr);
    ~CreateTriangleDialog() override;
    qreal A() const;
    qreal B() const;
    qreal C() const;

private:
    Ui::CreateTriangleDialog *ui;
};

#endif // CREATETRIANGLEDIALOG_H
