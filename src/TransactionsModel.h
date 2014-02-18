/*
 * TransactionsModel.h
 *
 *  Created on: Feb 18, 2014
 *      Author: bohacekm
 */

#ifndef TRANSACTIONSMODEL_H_
#define TRANSACTIONSMODEL_H_

#include "GroupRelatedModelBase.h"

class TransactionsModel : public GroupRelatedModelBase
{
public:
    TransactionsModel(QObject *parent=0);
    virtual ~TransactionsModel();

protected:
    virtual bb::cascades::datamanager::SqlDataQuery *constructQuery();
};

#endif /* TRANSACTIONSMODEL_H_ */
