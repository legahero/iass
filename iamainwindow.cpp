#include "iamainwindow.h"
#include "ui_iamainwindow.h"


IaMainWindow::IaMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IaMainWindow)
{
    ui->setupUi(this);    

    QTabWidget * tabContainer = ui->tabWidget;
    tabContainer->clear();
    //tabContainer->setTabShape(QTabWidget::Triangular);
    tabContainer->setTabsClosable(true);
    tabContainer->setMovable(true);

    connect(tabContainer,SIGNAL(tabCloseRequested(int)),this,SLOT(removeTab(int)));
    connect(tabContainer,SIGNAL(currentChanged(int)),this,SLOT(changeTab(int)));

    //setCentralWidget(tabContainer);

    setWindowIcon(QIcon(":/png/png/web.png"));
    this->resize(1024,650);

    QWebHolder * tabWebpage=new QWebHolder("www.inzsc.com",tabContainer);
    tabContainer->addTab(tabWebpage,"盈智善创");

}

IaMainWindow::~IaMainWindow()
{
    delete ui;
}

QWebHolder * IaMainWindow::createBackgroundTab()
{
    QTabWidget * tabContainer = ui->tabWidget;
    QWebHolder * tabWebpage=new QWebHolder(tabContainer);
    int index =tabContainer->addTab(tabWebpage,"");
    //tabContainer->setTabIcon(index, webView->favIcon());

    return tabWebpage;
}

QWidget * IaMainWindow::currentTabWindow()
{
    QTabWidget * tabContainer = ui->tabWidget;
    return (QWidget*)(tabContainer->currentWidget());
}

void IaMainWindow::removeTab()
{
    QTabWidget * tabContainer = ui->tabWidget;

    if(tabContainer->count()<=1)
        this->close();
    else
        tabContainer->removeTab(tabContainer->currentIndex());
}
void IaMainWindow::removeTab(int index)
{
    QTabWidget * tabContainer = ui->tabWidget;
    if(tabContainer->count()<=1)//as the current window is a child of the main
        this->close();          //window, it will be free by polmorphism
    else
    {
        tabContainer->removeTab(index);
        delete currentTabWindow();
    }
}

void IaMainWindow::changeTab(int)
{
    QTabWidget * tabContainer = ui->tabWidget;
    QString title = tabContainer->currentWidget()->windowTitle();
    if(title.isEmpty())
        this->setWindowTitle(tr("inzsc"));
    else
        this->setWindowTitle(title + tr(" - inzsc"));
}

void IaMainWindow::changeTitle(QString title)
{
    QTabWidget * tabContainer = ui->tabWidget;
    //truncate the title if it too long
    QString newTitle = title;
    if(title.size() > 25)
    {
        newTitle = title.left(25) + "...";
    }
    int index = tabContainer->currentIndex();

    tabContainer->setTabText(index,newTitle);
    this->setWindowTitle(newTitle);
}

