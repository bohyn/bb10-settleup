/*
 * GroupRelatedModelBase.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: bohacekm
 */

#include "GroupRelatedModelBase.h"

#include <bb/cascades/datamanager/SqlDataQuery>

GroupRelatedModelBase::GroupRelatedModelBase(QObject *parent)
    : SimpleQueryDataModel(parent), m_group_id(-1)
{
    connect(this, SIGNAL(groupIdChanged(int)), this, SLOT(onGroupIdChanged(int)));
}

GroupRelatedModelBase::~GroupRelatedModelBase()
{
    // TODO Auto-generated destructor stub
}

void GroupRelatedModelBase::setGroupId(int group_id)
{
    bool changed = (m_group_id != group_id);
    m_group_id = group_id;
    if (changed) {
        emit groupIdChanged(group_id);
    }
}

void GroupRelatedModelBase::onGroupIdChanged(int group_id)
{
    Q_UNUSED(group_id)
    bb::cascades::datamanager::SqlDataQuery *query = constructQuery();
    setQuery(query);
    emit queryChanged();
}
