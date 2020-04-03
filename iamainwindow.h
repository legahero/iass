#ifndef IAMAINWINDOW_H
#define IAMAINWINDOW_H

#include <QMainWindow>
#include "webholder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class IaMainWindow; }
QT_END_NAMESPACE

class IaMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    IaMainWindow(QWidget *parent = nullptr);
    ~IaMainWindow();

    QWebHolder * createBackgroundTab();
    QWidget * currentTabWindow();
    void removeTab();
    void removeTab(int);
    void changeTab(int);
    void changeTitle(QString);

private:
    Ui::IaMainWindow *ui;
};
#endif // IAMAINWINDOW_H
