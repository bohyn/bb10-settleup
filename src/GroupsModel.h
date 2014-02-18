/*
 * GroupsModel.h
 *
 *  Created on: Feb 12, 2014
 *      Author: bohacekm
 */

#ifndef GROUPSMODEL_H_
#define GROUPSMODEL_H_

#include <bb/cascades/datamanager/SimpleQueryDataModel>
#include <QSettings>

class GroupsModel : public bb::cascades::datamanager::SimpleQueryDataModel
{
    Q_OBJECT

public:
    GroupsModel(QObject *parent=0);
    virtual ~GroupsModel();

    int createGroup(const QVariantMap &group_data);
    void deleteGroup(int id);

public slots:
    QVariantList groupsData();

//private slots:
//    void onItemAdded(QVariantList indexPath);
//    void onItemUpdated(QVariantList indexPath);
//    void onItemRemoved(QVariantList indexPath);
};

#endif /* GROUPSMODEL_H_ */
