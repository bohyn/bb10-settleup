/*
 * Copyright (c) 2011-2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import bb.cascades 1.2
import settleup 1.0

TabbedPane {
    tabs: [
        Tab {
            id: tabCreateGroup
            title: qsTr("Create group")
            property bool isDynamic: false
            CreateGroupPage {
            	onCreationCompleted: {
                	init(_app);
                }
            }
        }
    ]
    onCreationCompleted: {
        reloadTabs();
        activeTab = at(_app.getLastActiveTab());
        _app.groupAdded.connect(function(group_id) {
            reloadTabs();
            activateTabByGroupId(group_id);
        });
        _app.groupRemoved.connect(function() {
            activeTab = at(0);
            reloadTabs();
        });
    }
    
    onActiveTabChanged: {
        var idx = indexOf(activeTab);
        _app.setLastActiveTab(idx);
    }
    
    function activateTabByGroupId(group_id) {
        if (group_id > 0) {
            for (var i = 0; i < tabs.length; ++i) {
                var tab = at(i);
                if (tab.isDynamic && tab.group_id == group_id) {
                    activeTab = tab;
                    return;
                }
            }
        }
    }
    
    function reloadTabs() {
        modelGroups.load();
        for (var i = tabs.length - 1; i >= 0; --i) {
            var tab = at(i);
            if (tab.isDynamic) {
            	remove(at(i));
            }
        }
        var tabs_data = modelGroups.groupsData();
        for (var idx in tabs_data) {
            var tab_data = tabs_data[idx];
            var tab = defTabGroup.createObject().init(_app, tab_data);
            add(tab);
        }
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: defTabGroup
            source: "GroupTab.qml"
        },
        GroupsModel {
            id: modelGroups
        }
    ]
}

