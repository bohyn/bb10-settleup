import bb.cascades 1.2

Page {
    function init(_app) {
        btnCreateGroup.clicked.connect(function() {
            var group_data = {};
            group_data["name"] = txtGroupName.text.trim();
            group_data["members"] = contMembers.collectData();
            console.log("adding group data", group_data);
            _app.addGroup(group_data);
            contMembers.resetInputs();
            txtGroupName.text = "";
            txtGroupName.validator.state = ValidationState.Unknown;
        });
    }
    
    titleBar: TitleBar {
        title: qsTr("Create group")
    }
    content: Container {
		Wrap {
	        Label {
	            text: qsTr("To create group, enter its name and names of members.")
	        }
	    }
        Header {
            id: hdrGroupName
            title: qsTr("Group name")
        }
        Wrap {
	        TextField {
	            id: txtGroupName
	            accessibility.labelledBy: hdrGroupName
	            hintText: qsTr("Enter group name")
	            validator: Validator {
	                mode: ValidationMode.Immediate
	                errorMessage: qsTr("Group name is required")
	                onValidate: {
	                    valid = parent.text.trim().length > 0;
	                }
	            }
	        }
	    }
        Header {
            title: qsTr("Members")
        }
        Wrap {
            layout: StackLayout {
                orientation: LayoutOrientation.LeftToRight
            }
	        Container {
	            id: contMembers
	            property int totalValidCount: 0
                function collectData() {
                    var members = [];
                    for (var i = 0; i < contMembers.count(); ++i) {
                        var member = contMembers.at(i).text.trim();
                        if (member.length > 0) {
                            members.push(member);
                        }
                    }
                    return members;
                }
                
                function resetInputs() {
                    contMembers.at(0).text = "";
                    for (var i = contMembers.count() - 1; i > 0; --i) {
                    	contMembers.remove(contMembers.at(i));
                    }
                }
	            layoutProperties: StackLayoutProperties {
                	spaceQuota: 4.0 
                }
	        }
	        Container {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1.0 
                }
                verticalAlignment: VerticalAlignment.Bottom
                leftMargin: 20
                Button {
                    text: qsTr("Add")
                    onClicked: {
                        var txt_member = defMemberName.createObject();
                        contMembers.add(txt_member);
                    }
                }
            }
        }
        Wrap {
	        Button {
	            id: btnCreateGroup
	            text: qsTr("Create new group")
	            enabled: txtGroupName.validator.valid // && contMembers.totalValidCount > 0
	            horizontalAlignment: HorizontalAlignment.Fill
	        }
            horizontalAlignment: HorizontalAlignment.Fill
        }
        
        attachedObjects: [
            ComponentDefinition {
                id: defMemberName
                TextField {
                    property bool lastValid: false
                    hintText: "Enter member name"
                    
                    onTextChanging: {
                        if (text.trim().length > 0) {
                            if (!lastValid) {
                                lastValid = true;
                                contMembers.totalValidCount++;
                            }
                        } else {
                            if (lastValid) {
                                lastValid = false
                                contMembers.totalValidCount--;
                            }
                        }
                    }
                }
            }
        ]
        onCreationCompleted: {
            contMembers.add(defMemberName.createObject());
        }
    }
}
