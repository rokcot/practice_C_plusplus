#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteDialog(QWidget *parent = nullptr);
    ~DeleteDialog() override;
    int first() const;
    int count() const;

private:
    Ui::DeleteDialog *ui;
};

#endif // DELETEDIALOG_H
