import bb.cascades 1.2

Tab {
    id: tab
    property bool isDynamic: true
    property int group_id
    
    function init(_app, tab_data) {
        this.group_id = tab_data["id"];
        this.title = tab_data["name"];
        
        pgGroup.init(_app, this.group_id);
        
        pgGroup.deleteTriggered.connect(function() {
            console.log("deleteTriggered", group_id);
            _app.removeGroup(group_id);
        });
        
        return this;
    }

    content: GroupPage {
        id: pgGroup
        titleBar: TitleBar {
            title: tab.title
        }
    }
}
