/// <reference path="ext-base.js" />
/// <reference path="ext-all-debug.js" />

Ext.onReady(function() {

    var scrollTop = 0;
    var grid = new Ext.grid.EditorGridPanel({
        el: 'grid_sample',
        width: 800,
        height: 300,
        layout: 'border',
        region: 'center',
        title: 'Sample Items',
        stripeRows: true,
        loadMask: true,
        enableHdMenu: false,
        view: new Ext.grid.GridView({
            scrollToTop: Ext.emptyFn
        }),
        listeners: {
            bodyscroll: function() {
                var d = grid.getView().scroller.dom;
                if (d.scrollTop > d.scrollHeight - 550 &&
                 d.scrollTop < d.scrollHeight - 351 &&
                 d.scrollTop > scrollTop) {
                    grid.getStore().loadDataBlock(100, 'down');
                    scrollTop = d.scrollTop;
                }
            }
        }
    }); //end grid constructor
  
    PageMethods.LoadData(function(response) {
        if (response) {
            var gridcolumns = new Array(), storefields = new Array();

            for (i = 0; i < response.length; ++i) {
                storefields[i] = 'Fields[' + i + ']';
                gridcolumns[i] = { header: response[i], dataIndex: storefields[i], width: 150, sortable: false };
            }

            var store = new Ext.data.JsonStore({
                root: 'BufferItems',
                idProperty: 'ID',
                fields: storefields
            });

            store.loadDataBlock = function(limit, mode) {
                PageMethods.GetItems(mode, limit, function(response) {
                    store.loadData(response, true);
                });
            }
            store.loadDataBlock(100, 'down');

            var gridColumnModel = new Ext.grid.ColumnModel(gridcolumns);
            grid.reconfigure(store, gridColumnModel);
            grid.autoExpandColumn = 2;
            grid.render();

        } else {
            Ext.Msg.alert('unable to load database!');
        }
    });  //end LoadData
});