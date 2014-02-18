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

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include <QSettings>
#include <QObject>

class GroupsModel;

namespace bb
{
    namespace cascades
    {
        class Application;
        class LocaleHandler;
    }
}

class QTranslator;

/*!
 * @brief Application object
 *
 *
 */

class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI(bb::cascades::Application *app);
    virtual ~ApplicationUI() { }
    Q_INVOKABLE int getLastActiveTab();
    Q_INVOKABLE void setLastActiveTab(int idx);

public slots:
    //QVariantList getGroupsData();
    //QObject* getGroupsModel();
    int addGroup(const QVariantMap &group_data);
    void removeGroup(int id);
    int addMember(int group_id, const QVariantMap &member_data);
    void removeMember(int id);

signals:
    void groupAdded(int id);
    void groupRemoved(int id);
    void memberAdded(int id);
    void memberRemoved(int id);

private slots:
    void onSystemLanguageChanged();

private:
    void registerQmlTypes();
    bool initDatabase();

    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;
    GroupsModel *m_groups_model;

    QSettings m_settings;
};

#endif /* ApplicationUI_HPP_ */
