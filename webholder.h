#ifndef WEBHOLDER_H
#define WEBHOLDER_H

#define APPDIR QCoreApplication::applicationDirPath()
#include <QtWidgets>
#include <QTranslator>
#include <QMainWindow>
#include <QWebEngineView>
#include "iasswebview.h"

class QWebHolder: public QWidget
{
  Q_OBJECT
  public slots:
    void changeUrl(QUrl);
    void changeTitle(QString);
    void initLoading();
    void loadUrl();
    void loading(int);
    void endOfLoad(bool);
    void changeIcon(const QIcon&);
    void previous();
    void next();
    void refresh();
    void goHome();
    void stop();

  public:

    QWebHolder(QWidget *parent);

    QWebHolder(QString url,QWidget *parent);
    ~QWebHolder();


    static QWebHolder* newView(QString url);
    const QIcon &icon() {return m_icon ;}
    const QString &title()   {return m_title;}

    QiassWebView * getWebView()   {return m_webView;}

        //  QVector<QAction*> allAction(){return liste;}

  private:
    QString const defaultHomePage = "http://www.inzsc.com/";
    QString         m_title;
    QIcon           m_icon;

    QVBoxLayout    *m_layout;
    QiassWebView *m_webView;
    QToolBar       *m_toolbar;
    QAction        *m_homeAction;
    QAction        *m_submit;
    QLineEdit      *m_urlField;
    QAction        *m_previousPageAction;
    QAction        *m_nextPageAction;
    QAction        *m_refreshAction;
    QAction        *m_stopAction;

   // QVector<QAction*> liste;

    void addToolbar();
    void addShortcut();
};

#endif // WEBHOLDER_H
