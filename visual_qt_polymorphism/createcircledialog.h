#ifndef CREATECIRCLEDIALOG_H
#define CREATECIRCLEDIALOG_H

#include <QWidget>

namespace Ui {
class CreateCircleDialog;
}

class CreateCircleDialog : public QWidget
{
    Q_OBJECT

public:
    explicit CreateCircleDialog(QWidget *parent = nullptr);
    ~CreateCircleDialog();

private:
    Ui::CreateCircleDialog *ui;
};

#endif // CREATECIRCLEDIALOG_H
