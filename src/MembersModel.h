/*
 * UsersModel.h
 *
 *  Created on: Feb 13, 2014
 *      Author: bohacekm
 */

#ifndef USERSMODEL_H_
#define USERSMODEL_H_

#include "GroupRelatedModelBase.h"

class MembersModel : public GroupRelatedModelBase
{
    Q_OBJECT

public:
    MembersModel(QObject* parent=0);
    virtual ~MembersModel();

protected:
    virtual bb::cascades::datamanager::SqlDataQuery *constructQuery();
};

#endif /* USERSMODEL_H_ */
