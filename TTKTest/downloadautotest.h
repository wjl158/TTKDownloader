#ifndef DOWNLOADAUTOTEST_H
#define DOWNLOADAUTOTEST_H

/* =================================================
 * This file is part of the TTK Downloader project
 * Copyright (c) 2016 - 2017 Greedysky Studio
 * All rights reserved!
 * Redistribution and use of the source code or any derivative
 * works are strictly forbiden.
   =================================================*/

#include <QDebug>
#include <QtTest/QTest>
#include <QSharedPointer>
#include "downloadobject.h"

namespace DownloadAutoTest
{
    typedef QList<QObject*> TestList;

    inline TestList& testList()
    {
        static TestList list;
        return list;
    }

    inline bool findObject(QObject* object)
    {
        TestList& list = testList();
        if(list.contains(object))
        {
            return true;
        }
        foreach(QObject* test, list)
        {
            if(test->objectName() == object->objectName())
            {
                return true;
            }
        }
        return false;
    }

    inline void addTest(QObject* object)
    {
        TestList& list = testList();
        if(!findObject(object))
        {
            list.append(object);
        }
    }

    inline int run(int argc, char *argv[])
    {
        int ret = 0;
        foreach(QObject* test, testList())
        {
            ret += QTest::qExec(test, argc, argv);
        }
        return ret;
    }
}

template <class T>
class DownloadTest
{
public:
    QSharedPointer<T> m_child;

    DownloadTest(const QString& name) : m_child(new T)
    {
        m_child->setObjectName(name);
        DownloadAutoTest::addTest(m_child.data());
    }
    static QString getClassName()
    {
        return "DownloadTest";
    }
};

#define DECLARE_TEST(className) static DownloadTest<className> t(#className);

#define TEST_MAIN \
    int main(int argc, char *argv[]) \
    { \
        QApplication app(argc, argv); \
        QCoreApplication::setOrganizationName(APPNAME); \
        QCoreApplication::setOrganizationDomain(APPCOME); \
        QCoreApplication::setApplicationName(APPNAME); \
        return DownloadAutoTest::run(argc, argv); \
    }

#endif // DOWNLOADAUTOTEST_H
