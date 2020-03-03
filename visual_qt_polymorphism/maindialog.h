#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QTime>
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
    void generateShapeWithStep();

    int in = 0;

private:
    void delContext();
    void listContextMenu(const QPoint &pos);

private:
    Ui::MainDialog *ui;
    QMenu* m_createMenu;
    QScopedPointer<DataModel, QScopedPointerDeleteLater> m_dataModel;
    QMenu* menu;
    QMenu* generateShapeMenu;
    QTimer* timer;
};
#endif // MAINDIALOG_H
