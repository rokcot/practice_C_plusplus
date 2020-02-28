#ifndef CREATECIRCLEDIALOG_H
#define CREATECIRCLEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateCircleDialog;
}

class CreateCircleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCircleDialog(QWidget *parent = nullptr);
    ~CreateCircleDialog() override;

    qreal radius() const;

private:
    Ui::CreateCircleDialog *ui;
};

#endif // CREATECIRCLEDIALOG_H
