#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>

#include "datamodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
class QMenu;
class DataModel;
QT_END_NAMESPACE


class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();
    void createCircle();
    void createTriangle();
    void createRectangle();

    void delShape();
    void generateShape();


private:
    Ui::MainDialog *ui;
    QMenu* m_createMenu;
    QScopedPointer<DataModel, QScopedPointerDeleteLater> m_dataModel;
};
#endif // MAINDIALOG_H
