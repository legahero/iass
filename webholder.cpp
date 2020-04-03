#include "webholder.h"
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineProfile>

QWebHolder::QWebHolder(QWidget* parent)
    :QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    addToolbar();    
    addShortcut();

    this->resize(1024,650);

    //m_webView = new QWebEngineView();

    auto profile = QWebEngineProfile::defaultProfile();
    m_webView = new QiassWebView();
    QWebEnginePage *webPage = new QWebEnginePage(profile, m_webView);
    m_webView->setPage(webPage);


    m_layout->setContentsMargins(0,0,0,0);
    m_layout->addWidget(m_toolbar);
    m_layout->addWidget(m_webView);
    this->setLayout(m_layout);
    //this->setCentralWidget(this->parent());


    connect(m_webView,SIGNAL(urlChanged(QUrl)),this,SLOT(changeUrl(QUrl)));
    connect(m_webView,SIGNAL(titleChanged(QString)),this,SLOT(changeTitle(QString)));
    connect(m_webView,SIGNAL(loadStarted()),this,SLOT(initLoading()));
    connect(m_webView,SIGNAL(loadProgress(int)),this,SLOT(loading(int)));
    connect(m_webView,SIGNAL(loadFinished(bool)),this,SLOT(endOfLoad(bool)));
    connect(m_webView,SIGNAL(iconChanged(const QIcon&)),this,SLOT(changeIcon(const QIcon&)));

    m_webView->show();
}

QWebHolder::QWebHolder(QString url,QWidget* parent)
    :QWebHolder(parent)
{
    //QWebHolder(parent);

    QString tmpurl=url.simplified();//trimmed();
    if(tmpurl.isEmpty())
    {
        tmpurl = tr("about:blank");
    }
    else
    {
        if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
        {
            url = "http://"+url;
        }
    }

    m_webView->load(QUrl(url));// m_webPage->load(tr("about:blank"));
}

QWebHolder::~QWebHolder()
{
    delete m_webView;
    delete m_homeAction;
    delete m_submit;
    if(NULL!=m_urlField) delete m_urlField;
    if(NULL!=m_previousPageAction) delete m_previousPageAction;
    if(NULL!=m_nextPageAction) delete m_nextPageAction;
    if(NULL!=m_refreshAction) delete m_refreshAction;
    if(NULL!=m_stopAction) delete m_stopAction;

    delete m_toolbar;

}


void QWebHolder::changeUrl(QUrl url)
{
    m_urlField->setText(url.toString());
}
void QWebHolder::changeTitle(QString title)
{
    this->m_title = title;
    //qDebug()<<this->metaObject()->className();
    //qDebug()<<this->parent()->metaObject()->className();
    qDebug()<<this->parent()->parent()->metaObject()->className();
    //QTabWidget * tabContainer1=((QTabWidget*) this->parent());
    QTabWidget * tabContainer=qobject_cast<QTabWidget *>(this->parent()->parent());//((QTabWidget*) this->parent());
    int index=tabContainer->indexOf(this);
    tabContainer->setTabText(index,title);
    //this->setWindowTitle(title);
}
void QWebHolder::initLoading()
{
    qDebug()<<"initLoading";
}
void QWebHolder::loading(int value)
{
    qDebug()<<"loading";
    m_refreshAction->setVisible(false);
    m_stopAction->setVisible(true);
}
void QWebHolder::endOfLoad(bool visible)
{
    qDebug()<<"endOfLoad";
    if(visible)
    {        
        m_refreshAction->setVisible(true);
        m_stopAction->setVisible(false);
    }
}

void QWebHolder::changeIcon(const QIcon &icon)
{
    qDebug()<<"changeIcon";
    this->m_icon = icon;
    //this->setWindowIcon(m_icon);
    qDebug()<<this->parent()->parent()->metaObject()->className();
    QTabWidget * tabContainer=qobject_cast<QTabWidget *>(this->parent()->parent());//((QTabWidget*) this->parent());
    int index=tabContainer->indexOf(this);
    if (index != -1)
        tabContainer->setTabIcon(index, icon);

}

void QWebHolder::addToolbar()
{
    m_toolbar = new QToolBar;
    m_previousPageAction = new QAction(tr("Previous page"));
    m_nextPageAction     = new QAction(tr("Next Page"));
    m_refreshAction      = new QAction(tr("Refresh"));
    m_stopAction         = new QAction(tr("Stop"));
    m_homeAction         = new QAction(tr("Home"));

    //m_toolbar = this->addToolBar(tr("Navigation"));
    m_toolbar->addAction(m_previousPageAction);
    m_toolbar->addAction(m_nextPageAction);
    m_toolbar->addAction(m_refreshAction);
    m_toolbar->addAction(m_stopAction);
    m_toolbar->addSeparator();
    m_toolbar->addAction(m_homeAction);

    m_urlField = new QLineEdit(defaultHomePage);
    m_urlField->setFocus(Qt::OtherFocusReason);
    m_urlField->selectAll();
    m_toolbar->addWidget(m_urlField);
    m_submit = new QAction(tr("Go"));
    m_toolbar->addAction(m_submit);

    m_previousPageAction->setIcon(QIcon(":/png/png/prev.png"));
    m_nextPageAction->setIcon(QIcon(":/png/png/next.png"));
    m_refreshAction->setIcon(QIcon(":/png/png/refresh.png"));
    m_homeAction->setIcon(QIcon(":/png/png/home.png"));
    m_stopAction->setIcon(QIcon(":/png/png/stop.png"));
    m_submit->setIcon(QIcon(":/png/png/enter.png"));
}
void QWebHolder::loadUrl()
{
    QString url = this->m_urlField->text();
    bool space = false, dot = false;
    /*Verify if a url was typed or a keyword to search in the adress bar*/
    for(int i=0;i<url.size();i++)
    {
         if(url[i]==' ')
         {
             url[i]='+';
             space = true;
         }
         else if(url[i]=='.')
             dot = true;
     }

    if(url.isEmpty())
    {
        url = "https:// ";
    }
    else
    {
        if( (url.left(7) != "http://") && (url.left(8) != "https://" ) )
        {
            if(space || (!dot)) //Submitting the research
               url = "http://duckduckgo.com/?q="+url+"&t=h_&ia=web";
            else
               url = "http://"+url;
        }
    }
    this->m_webView->load(QUrl(url));
    this->m_icon = QIcon();
}


void QWebHolder::addShortcut()
{
    this->m_previousPageAction->setShortcut(QKeySequence(QKeySequence::Back));
    this->m_nextPageAction->setShortcut(QKeySequence(QKeySequence::Forward));
    this->m_refreshAction->setShortcut(QKeySequence(QKeySequence::Refresh));
    this->m_stopAction->setShortcut(QKeySequence(QKeySequence::Cancel));

    connect(new QShortcut(QKeySequence("CTRL+R"),this),SIGNAL(activated()),this,SLOT(refresh()));
    connect(m_previousPageAction,SIGNAL(triggered())    ,this,SLOT(previous()));
    connect(m_nextPageAction    ,SIGNAL(triggered())    ,this,SLOT(next()));
    connect(m_refreshAction     ,SIGNAL(triggered())    ,this,SLOT(refresh()));
    connect(m_stopAction        ,SIGNAL(triggered())    ,this,SLOT(stop()));
    connect(m_homeAction        ,SIGNAL(triggered())    ,this,SLOT(goHome()));
    connect(m_submit            ,SIGNAL(triggered())    ,this,SLOT(loadUrl()));
    connect(m_urlField          ,SIGNAL(returnPressed()),this,SLOT(loadUrl()));
}

//Toolbar & Menu Action's Slot
void QWebHolder::previous()
{
    m_webView->back();
}
void QWebHolder::next()
{
    m_webView->forward();
}
void QWebHolder::refresh()
{
    m_webView->reload();
}
void QWebHolder::goHome()
{
   m_webView->load(QUrl(defaultHomePage));
}
void QWebHolder::stop()
{
   m_webView->stop();
}

