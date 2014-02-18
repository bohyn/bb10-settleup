import bb.cascades 1.2
import bb.system 1.0
import fairbill 1.0

Page {
    signal deleteTriggered()
    
    function init(_app, group_id) {
        modelMembers.groupId = group_id;
        modelTransactions.groupId = group_id;
    }

    actions: [
        ActionItem {
            id: actNewTransaction
            ActionBar.placement: ActionBarPlacement.Signature
            title: qsTr("New transaction")
            imageSource: "asset:///images/ac_add.png"
            onTriggered: {
                pgNewTransaction.membersModel = modelMembers;
                shtNewTransaction.open();
            }
        },
        DeleteActionItem {
            onTriggered: {
                dlgConfirmDelete.exec();
                if (dlgConfirmDelete.result == SystemUiResult.ConfirmButtonSelection) {
                    deleteTriggered();
                }
            }
        }
    ]
    attachedObjects: [
        SystemDialog {
            id: dlgConfirmDelete
            title: qsTr("Delete group")
            body: qsTr("Are you sure you want to delete this group including all persons?")
        },
        MembersModel {
            id: modelMembers
            onQueryChanged: {
                load();
            }
        },
        TransactionsModel {
            id: modelTransactions
            onQueryChanged: {
                load();
            }
        },
        Sheet {
            id: shtNewTransaction
            content: NewTransactionPage {
                id: pgNewTransaction
                onTitleBarActionTriggered: {
                    shtNewTransaction.close();
                }
            }
        }
    ]
    Container {
        horizontalAlignment: HorizontalAlignment.Fill
        Container {
            topPadding: 20
            bottomPadding: 20
            horizontalAlignment: HorizontalAlignment.Fill
	        SegmentedControl {
	            options: [
	                Option {
	                    text: qsTr("Transactions")
	                    value: "transactions"
	                },
	                Option {
	                    text: qsTr("Debts")
	                    value: "debts"
	                },
	                Option {
	                    text: qsTr("Summary")
	                    value: "summary"
	                }
	            ]
	            
	            onSelectedOptionChanged: {
                 	contTransactions.visible = false;
                 	contDebts.visible = false;
                 	contSummary.visible = false;
                 	switch (selectedOption.value) {
                 	    case "transactions":
                            contTransactions.visible = true;
                 	        break;
                 	    case "debts":
                 	        contDebts.visible = true;
                 	        break;
                 	    case "summary":
                 	        contSummary.visible = true;
                 	        break;
                 	}
                }
	        }
        }

        Container {
            id: contTransactions
	        ListView {
	            //id: lstMembers
	            id: lstTransactions
	            //dataModel: modelMembers
	            dataModel: modelTransactions
	            listItemComponents: [
	                ListItemComponent {
	                    StandardListItem {
	                        title: ListItemData.from_members + " " + qsTr("paid") + " " + ListItemData.amount + " " + ListItemData.currency
	                        description: ListItemData.transaction_name + " " + qsTr("for:") + " " + ListItemData.to_members + " (" + ListItemData.to_members_ratio + ")"
	                        status: ListItemData.transaction_date
	                        textFormat: TextFormat.Html
	                        imageSource: "asset:///images/transaction.png"
	                    }
	                }
	            ]
	        }
        }
        
        Container {
            id: contDebts
        }
        
        Container {
            id: contSummary
        }

    }
}
