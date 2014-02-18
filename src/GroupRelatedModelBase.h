/*
 * GroupRelatedModelBase.h
 *
 *  Created on: Feb 18, 2014
 *      Author: bohacekm
 */

#ifndef GROUPRELATEDMODELBASE_H_
#define GROUPRELATEDMODELBASE_H_

#include <bb/cascades/datamanager/SimpleQueryDataModel>

namespace bb {
    namespace cascades {
        namespace datamanager {
            class SqlDataQuery;
        }
    }
}

class GroupRelatedModelBase : public bb::cascades::datamanager::SimpleQueryDataModel
{
    Q_OBJECT
    Q_PROPERTY(int groupId READ groupId WRITE setGroupId NOTIFY groupIdChanged)

public:
    GroupRelatedModelBase(QObject *parent=0);
    virtual ~GroupRelatedModelBase();

    int groupId() { return m_group_id; }
    void setGroupId(int group_id);

protected:
    virtual bb::cascades::datamanager::SqlDataQuery *constructQuery() = 0;

protected slots:
    virtual void onGroupIdChanged(int group_id);

signals:
    void groupIdChanged(int group_id);

private:
    int m_group_id;
};

#endif /* GROUPRELATEDMODELBASE_H_ */
