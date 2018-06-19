/// <reference path="ext-base.js" />
/// <reference path="ext-all-debug.js" />

Ext.ns('Ext.ux');
Ext.ux.ThreePanelApp = function(conf) {
    //Master panel
    MasterPanel = function(conf) {
        config = {
            title: 'Master',
            region: 'center'
        };
        Ext.apply(config, conf || {});
        MasterPanel.superclass.constructor.call(this, config);
    }
    Ext.extend(MasterPanel, Ext.Panel);

    var masterPanelConf = {};
    if (conf && conf.masterpanelConf) {
        masterPanelConf = conf.masterPanelConf;
    }
    var masterPanel = new MasterPanel(masterPanelConf);

    //Details panel
    DetailsPanel = function(conf) {
        config = {
            id: 'details-panel',
            layout: 'fit',
            title: 'Details'
        };
        Ext.apply(config, conf || {});
        DetailsPanel.superclass.constructor.call(this, config);
    }
    Ext.extend(DetailsPanel, Ext.Panel);

    var detailsPanelConf = {};
    if (conf && conf.detailsPanelConf) {
        detailsPanelConf = conf.detailsPanelConf;
    }
    var detailsPanel = new DetailsPanel(detailsPanelConf);

    //Navi panel
    NaviPanel = function(conf) {
        config = {
            title: 'Navigation',
            region: 'west',
            margins: '5 0 5 5',
            cmargins: '5 5 5 5',
            width: 200,
            minSize: 100,
            maxSize: 300
        };
        Ext.apply(config, conf || {});
        NaviPanel.superclass.constructor.call(this, config);
    }
    Ext.extend(NaviPanel, Ext.Panel);
    var naviPanelConf = {};
    if (conf && conf.naviPanelConf) {
        naviPanelConf = conf.naviPanelConf;
    }
    var naviPanel = new NaviPanel(naviPanelConf);

    //Master details container
    MasterDetailsCnt = function(conf) {
        config = {
            layout: 'border',
            region: 'center',
            collapsible: false,
            border: false,
            margins: '5 5 5 0',
            id: 'main-view',
            hideMode: 'offsets',
            items: [masterPanel
                , {
                    id: 'bottom-details',
                    layout: 'fit',
                    height: 300,
                    split: true,
                    border: false,
                    region: 'south',
                    items: detailsPanel
                }
            ]
        };
        Ext.apply(config, conf || {});
        MasterDetailsCnt.superclass.constructor.call(this, config);
    }
    Ext.extend(MasterDetailsCnt, Ext.Panel);
    var masterDetailsCntConf = {};
    if (conf && conf.masterDetailsCntConf) {
        masterDetailsCntConf = conf.masterDetailsCntConf;
    }
    var masterDetailsCnt = new MasterDetailsCnt(masterDetailsCntConf);

    //other config
    config = {
        layout: 'border',
        details: {
            collapsible: true,
            split: true
        },
        items: [{
            xtype: 'box',
            height: 20,
            region: 'north'
        }, naviPanel, masterDetailsCnt]
    };
    if (conf) {
        Ext.apply(config, conf);
    }
    Ext.ux.ThreePanelApp.superclass.constructor.call(this, config);
}
Ext.extend(Ext.ux.ThreePanelApp, Ext.Viewport);

