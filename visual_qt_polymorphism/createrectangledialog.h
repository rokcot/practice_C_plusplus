#ifndef CREATERECTANGLEDIALOG_H
#define CREATERECTANGLEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateRectangleDialog;
}

class CreateRectangleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateRectangleDialog(QWidget *parent = nullptr);
    ~CreateRectangleDialog() override;
    qreal shapeWidth() const;
    qreal shapeHeight() const;

private:
    Ui::CreateRectangleDialog *ui;
};

#endif // CREATERECTANGLEDIALOG_H
