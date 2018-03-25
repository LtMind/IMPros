#include "logiclayer.h"

#include <QDebug>
#include "login.h"

LogicLayer::LogicLayer(QObject *parent) :
    QObject(parent)
{
    m_login = new Login;
    m_connectServer = new ConnectServer;
    m_friendList = new FriendList;
    m_userInfoForm = new UserInfoForm;

    connect(m_login, SIGNAL(signalCloseProject()),
            this, SLOT(slotCloseProject()));
    connect(m_friendList, SIGNAL(signalCloseProject()),
            this, SLOT(slotCloseProject()));
    connect(m_login, SIGNAL(signalCloseProject()),
            this, SLOT(slotCloseProject()));
    connect(m_connectServer, SIGNAL(signalUserLoginFail()),
            m_login, SLOT(slotUserLoginFail()));

    connect(m_login, SIGNAL(signalConnectServer(QString,QString)),
            m_connectServer, SLOT(slotConnectServer(QString,QString)));
    connect(m_connectServer, SIGNAL(signalUserLoginSuccess(UserInfo)),
            this, SLOT(slotUserLoginSuccess(UserInfo)));

    m_connectServer->start();
}

LogicLayer::~LogicLayer()
{
    if(m_login != NULL)
    {
        delete m_login;
        m_login = NULL;
    }

    if(m_friendList != NULL)
    {
        delete m_friendList;
        m_friendList = NULL;
    }

    if(m_connectServer != NULL)
    {
        delete m_connectServer;
        m_connectServer = NULL;
    }
}

void LogicLayer::slotCloseProject(void)
{
    m_connectServer->closeThreads();
}

void LogicLayer::showLoginW(void)
{
    m_login->show();
}

void LogicLayer::slotUserLoginSuccess(UserInfo info)
{
    m_login->hide();
    m_friendList->initUserInfo(info);
    m_friendList->show();

    connect(m_friendList, SIGNAL(signalClickUserInfo(UserInfo)),
            this, SLOT(slotClickUserInfo(UserInfo)));
}

void LogicLayer::slotClickUserInfo(UserInfo info)
{
    m_userInfoForm->show();
    m_userInfoForm->updateUserInfoToForm(info);
}
