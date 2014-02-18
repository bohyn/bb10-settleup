/*
 * GroupsModel.cpp
 *
 *  Created on: Feb 12, 2014
 *      Author: bohacekm
 */

#include "dbinfo.h"
#include "GroupsModel.h"

#include <bb/cascades/datamanager/SqlDataQuery>
#include <QDebug>

#define SETTINGS_GROUPS_KEY "_groups_"

GroupsModel::GroupsModel(QObject *parent)
    : bb::cascades::datamanager::SimpleQueryDataModel(parent)
{
    bb::cascades::datamanager::SqlDataQuery *query = new bb::cascades::datamanager::SqlDataQuery();
    query->setSource(QUrl::fromLocalFile(DB_FILE));
    query->setQuery("SELECT id, name FROM groups");
    query->setKeyColumn("id");
    query->setCountQuery("SELECT COUNT(*) FROM groups");
    setQuery(query);

//    connect(this, SIGNAL(itemAdded(QVariantList)), this, SLOT(onItemAdded(QVariantList)));
//    connect(this, SIGNAL(itemUpdated(QVariantList)), this, SLOT(onItemUpdated(QVariantList)));
//    connect(this, SIGNAL(itemRemoved(QVariantList)), this, SLOT(onItemRemoved(QVariantList)));
}

GroupsModel::~GroupsModel()
{
}

int GroupsModel::createGroup(const QVariantMap &group_data)
{
    return 0;
}

void GroupsModel::deleteGroup(int id)
{

}

QVariantList GroupsModel::groupsData()
{
    int child_count = childCount(QVariantList());
    QVariantList result;
    for (int i = 0; i < child_count; ++i) {
        QVariantList idx = QVariantList() << i;
        result << data(idx);
    }
    return result;
}

//void GroupsModel::onItemAdded(QVariantList indexPath)
//{
//    QVariantList d = m_settings.value(SETTINGS_GROUPS_KEY).toList();
//    int idx = indexPath.value(0).toInt();
//    d.insert(idx, data(indexPath));
//    m_settings.setValue(SETTINGS_GROUPS_KEY, d);
//}
//
//void GroupsModel::onItemUpdated(QVariantList indexPath)
//{
//    QVariantList d = m_settings.value(SETTINGS_GROUPS_KEY).toList();
//    int idx = indexPath.value(0).toInt();
//    d[idx] = data(indexPath);
//    m_settings.setValue(SETTINGS_GROUPS_KEY, d);
//}
//
//void GroupsModel::onItemRemoved(QVariantList indexPath)
//{
//    QVariantList d = m_settings.value(SETTINGS_GROUPS_KEY).toList();
//    int idx = indexPath.value(0).toInt();
//    d.removeAt(idx);
//    m_settings.setValue(SETTINGS_GROUPS_KEY, d);
//}
