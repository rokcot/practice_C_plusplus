#ifndef CREATERECTANGLEDIALOG_H
#define CREATERECTANGLEDIALOG_H

#include <QWidget>

namespace Ui {
class CreateRectangleDialog;
}

class CreateRectangleDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateRectangleDialog(QWidget *parent = nullptr);
    ~CreateRectangleDialog();

private:
    Ui::CreateRectangleDialog *ui;
};

#endif // CREATERECTANGLEDIALOG_H
