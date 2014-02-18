/*
 * MembersModel.cpp
 *
 *  Created on: Feb 13, 2014
 *      Author: bohacekm
 */

#include "dbinfo.h"
#include "MembersModel.h"

#include <bb/cascades/datamanager/SqlDataQuery>

MembersModel::MembersModel(QObject* parent)
    : GroupRelatedModelBase(parent)
{
}

MembersModel::~MembersModel()
{
}

bb::cascades::datamanager::SqlDataQuery *MembersModel::constructQuery()
{
    bb::cascades::datamanager::SqlDataQuery *query = new bb::cascades::datamanager::SqlDataQuery();
    query->setSource(QUrl::fromLocalFile(DB_FILE));
    query->setQuery("SELECT id, name FROM members WHERE group_id = :filterGroupId");
    query->setKeyColumn("id");
    query->setCountQuery("SELECT COUNT(*) FROM members WHERE group_id = :filterGroupId");

    QVariantMap bind_values;
    bind_values["filterGroupId"] = groupId();
    query->setValuesToBind(bind_values);
    return query;
}
