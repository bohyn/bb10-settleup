import bb.cascades 1.3

Page {
    signal titleBarActionTriggered()
    property variant membersModel
    function resetInput() {
        txtAmount.text = "";
        txtName.text = "";
        dtDate.value = new Date();
    } 
    
    titleBar: TitleBar {
        acceptAction: ActionItem {
        	title: qsTr("Add")
        	onTriggered: {
        		titleBarActionTriggered();
            }
        }
        dismissAction: ActionItem {
            title: qsTr("Back")
            onTriggered: {
                titleBarActionTriggered();
                resetInput();
            }
        }
        title: qsTr("New transaction")
    }
    Container {
        topPadding: 20
        rightPadding: 20
        bottomPadding: 20
        leftPadding: 20

    	layout: StackLayout {
        	orientation: LayoutOrientation.TopToBottom
        }
        Container {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0
            }
            Container {
                Label {
                    text: qsTr("Who paid?")
                }
                ListView {
                    dataModel: membersModel
                    listItemComponents: [
                        ListItemComponent {
                            CustomListItem {
                                onTouch: {
                                    if (event.touchType == TouchType.Up) {
                                        chkItemFrom.checked = !chkItemFrom.checked;
                                    }
                                }
                                content: Container {
                                    verticalAlignment: VerticalAlignment.Center
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    rightPadding: 20
                                    Label {
                                        id: lblItemFrom
                                        text: ListItemData.name
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 5.0
                                        }
                                    }
                                    CheckBox {
                                        id: chkItemFrom
                                        accessibility.labelledBy: lblItemFrom
                                    }
                                }
                            }
                        }
                    ]
                }
            }
            
            Container {
                Label {
                    text: qsTr("For whom?")
                }
                ListView {
                    dataModel: membersModel
                    listItemComponents: [
                        ListItemComponent {
                            CustomListItem {
                                onTouch: {
                                    if (event.touchType == TouchType.Up) {
                                        chkItemTo.checked = !chkItemTo.checked;
                                    }
                                }
                                content: Container {
                                    verticalAlignment: VerticalAlignment.Center
                                    layout: StackLayout {
                                        orientation: LayoutOrientation.LeftToRight
                                    }
                                    rightPadding: 20
                                    Label {
                                        id: lblItemTo
                                        text: ListItemData.name
                                        layoutProperties: StackLayoutProperties {
                                            spaceQuota: 5.0
                                        }
                                    }
                                    CheckBox {
                                        id: chkItemTo
                                        accessibility.labelledBy: lblItemTo
                                        horizontalAlignment: HorizontalAlignment.Right
                                    }
                                }
                            }
                        }
                    ]
                }
            }
        
        }
        
        Container {
            layoutProperties: StackLayoutProperties {
                spaceQuota: 1.0
            }
            Label {
                id: lblAmount
                text: qsTr("Amount")
            }
            TextField {
                id: txtAmount
                accessibility.labelledBy: lblAmount
                inputMode: TextFieldInputMode.NumbersAndPunctuation
            }
            Label {
                id: lblName
                text: qsTr("Title")
            }
            TextField {
                id: txtName
                accessibility.labelledBy: lblName
            }
            Label {
                id: lblDate
                text: qsTr("Date")
            }
            DateTimePicker {
                id: dtDate
                accessibility.labelledBy: lblDate
                mode: DateTimePickerMode.DateTime
            }
        }

    }
}
