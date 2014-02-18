/*
 * TransactionsModel.cpp
 *
 *  Created on: Feb 18, 2014
 *      Author: bohacekm
 */

#include "dbinfo.h"
#include "TransactionsModel.h"

#include <bb/cascades/datamanager/SqlDataQuery>

TransactionsModel::TransactionsModel(QObject *parent)
    : GroupRelatedModelBase(parent)
{
}

TransactionsModel::~TransactionsModel()
{
}

bb::cascades::datamanager::SqlDataQuery *TransactionsModel::constructQuery()
{
    bb::cascades::datamanager::SqlDataQuery *query = new bb::cascades::datamanager::SqlDataQuery();
    query->setSource(QUrl::fromLocalFile(DB_FILE));
    query->setQuery("SELECT t.id as id, "
                    "       t.name AS transaction_name, "
                    "       STRFTIME('%d.%m.%Y %H:%M', t.transaction_date) AS transaction_date, "
                    "       ROUND(SUM(tf.amount), 1) AS amount, "
                    "       t.currency AS currency, "
                    "       GROUP_CONCAT(mf.name, ', ') AS from_members, "
                    "       (SELECT GROUP_CONCAT(mt.name, ', ') FROM transactions_to tt LEFT JOIN members mt ON mt.id = tt.member_id WHERE tt.transaction_id = t.id ORDER BY tt.id) AS to_members, "
                    "       (SELECT GROUP_CONCAT(ROUND(tt.ratio, 1), ':') FROM transactions_to tt LEFT JOIN members mt ON mt.id = tt.member_id WHERE tt.transaction_id = t.id ORDER BY tt.id) AS to_members_ratio "
                    "FROM transactions t "
                    "LEFT JOIN transactions_from tf ON t.id = tf.transaction_id "
                    "LEFT JOIN members mf ON mf.id = tf.member_id "
                    "WHERE t.group_id = :filterGroupId "
                    "GROUP BY t.id");

    query->setKeyColumn("id");
    query->setCountQuery("SELECT COUNT(*) FROM transactions WHERE group_id = :filterGroupId");

    QVariantMap bind_values;
    bind_values["filterGroupId"] = groupId();
    query->setValuesToBind(bind_values);
    return query;
}
