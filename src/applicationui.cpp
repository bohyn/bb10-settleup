/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "blink/qmlblink.h"
#include "dbinfo.h"
#include "GroupsModel.h"
#include "MembersModel.h"
#include "TransactionsModel.h"
#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/cascades/Tab>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

#define SETTINGS_LAST_TAB_KEY "_last_tab_idx_"

using namespace bb::cascades;

ApplicationUI::ApplicationUI(bb::cascades::Application *app) :
        QObject(app)
{
    registerQmlTypes();

    // prepare the localization
    m_pTranslator = new QTranslator(this);
    m_pLocaleHandler = new LocaleHandler(this);

    bool res = QObject::connect(m_pLocaleHandler, SIGNAL(systemLanguageChanged()), this, SLOT(onSystemLanguageChanged()));
    // This is only available in Debug builds
    Q_ASSERT(res);
    // Since the variable is not used in the app, this is added to avoid a
    // compiler warning
    Q_UNUSED(res);

    // initial load
    onSystemLanguageChanged();

    m_groups_model = new GroupsModel(this);

    // init db
    if (!initDatabase()) {
        qFatal("Error creating database");
    } else {
        qDebug() << "Database initialized successfully.";
    }

    // Create scene document from main.qml asset, the parent is set
    // to ensure the document gets destroyed properly at shut down.
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
    qml->setContextProperty("_app", this);

    // Create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();

    // Set created root object as the application scene
    app->setScene(root);

    new QmlBlink(this);
}

int ApplicationUI::getLastActiveTab()
{
    int id = m_settings.value(SETTINGS_LAST_TAB_KEY, 0).toInt();
    return id;
}

void ApplicationUI::setLastActiveTab(int idx)
{
    m_settings.setValue(SETTINGS_LAST_TAB_KEY, idx);
}

int ApplicationUI::addGroup(const QVariantMap &group_data)
{
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare("INSERT INTO groups (name, created, last_updated) VALUES (:name, datetime('now'), datetime('now'))");
    query.bindValue("name", group_data.value("name"));
    query.exec();
    int group_id = query.lastInsertId().toInt();
    database.close();
    qDebug() << "Added group ID" << group_id << "-" << group_data.value("name").toString();

    foreach (QVariant member_name, group_data.value("members").toList()) {
        QVariantMap member_data;
        member_data["name"] = member_name;
        addMember(group_id, member_data);
    }

    emit groupAdded(group_id);
    return group_id;
}

void ApplicationUI::removeGroup(int id)
{
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare("DELETE FROM groups WHERE id = :groupId");
    query.bindValue("groupId", id);
    query.exec();
    database.close();
    emit groupRemoved(id);
}

int ApplicationUI::addMember(int group_id, const QVariantMap &member_data)
{
    QSqlDatabase database = QSqlDatabase::database();
    QSqlQuery query(database);
    query.prepare("INSERT INTO members (group_id, name, created, last_updated) VALUES (:groupId, :name, datetime('now'), datetime('now'))");
    query.bindValue("groupId", group_id);
    query.bindValue("name", member_data.value("name"));
    query.exec();
    int member_id = query.lastInsertId().toInt();
    database.close();
    qDebug() << "Added member ID" << member_id << "-" << member_data.value("name").toString();
    emit memberAdded(member_id);
    return member_id;
}

void ApplicationUI::removeMember(int id)
{
    emit memberRemoved(id);
}

void ApplicationUI::onSystemLanguageChanged()
{
    QCoreApplication::instance()->removeTranslator(m_pTranslator);
    // Initiate, load and install the application translation files.
    QString locale_string = QLocale().name();
    QString file_name = QString("settleup_%1").arg(locale_string);
    if (m_pTranslator->load(file_name, "app/native/qm")) {
        QCoreApplication::instance()->installTranslator(m_pTranslator);
    }
}

bool ApplicationUI::initDatabase()
{
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(DB_FILE);
    if (!database.isValid()) {
        qWarning() << "Database connection invalid.";
        return false;
    }

    database.open();
    if (!database.isOpen()) {
        qWarning() << "Could not open database.";
        return false;
    }

    QStringList init_queries;

    init_queries << "CREATE TABLE IF NOT EXISTS groups ( "
                    "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "                name VARCHAR, "
                    "                created DATETIME, "
                    "                last_updated DATETIME"
                    ");";

    init_queries << "CREATE TABLE IF NOT EXISTS members ( "
                    "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "                group_id INTEGER REFERENCES groups(id) ON DELETE CASCADE, "
                    "                name VARCHAR, "
                    "                created DATETIME, "
                    "                last_updated DATETIME"
                    ");";

    init_queries << "CREATE TABLE IF NOT EXISTS transactions ( "
                    "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "                group_id INTEGER REFERENCES groups(id) ON DELETE CASCADE, "
                    "                name VARCHAR, "
                    "                transaction_date DATETIME, "
                    "                currency VARCHAR, "
                    "                created DATETIME, "
                    "                last_updated DATETIME"
                    ");";

    init_queries << "CREATE TABLE IF NOT EXISTS transactions_from ( "
                    "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "                transaction_id INTEGER REFERENCES transactions(id) ON DELETE CASCADE, "
                    "                member_id INTEGER REFERENCES members(id) ON DELETE CASCADE, "
                    "                amount DECIMAL(10,2), "
                    "                created DATETIME, "
                    "                last_updated DATETIME"
                    ");";

    init_queries << "CREATE TABLE IF NOT EXISTS transactions_to ( "
                    "                id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "                transaction_id INTEGER REFERENCES transactions(id) ON DELETE CASCADE, "
                    "                member_id INTEGER REFERENCES members(id) ON DELETE CASCADE, "
                    "                ratio DECIMAL(2,1), "
                    "                created DATETIME, "
                    "                last_updated DATETIME"
                    ");";

    foreach(QString q, init_queries) {
        QSqlQuery query(database);
        if (!query.exec(q)) {
            qWarning() << "Error executing SQL:\n" << q;
            return false;
        }
    }
    database.close();
    return true;
}

void ApplicationUI::registerQmlTypes()
{
    qmlRegisterType<GroupsModel>("settleup", 1, 0, "GroupsModel");
    qmlRegisterType<MembersModel>("settleup", 1, 0, "MembersModel");
    qmlRegisterType<TransactionsModel>("settleup", 1, 0, "TransactionsModel");
}
