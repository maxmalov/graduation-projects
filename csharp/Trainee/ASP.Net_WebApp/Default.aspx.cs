using System;
using System.Collections.Generic;

using ItemsObjects;

namespace ScrollProxy {
    public partial class _Default : System.Web.UI.Page {
        static private int last;

        protected void Page_Load(object sender, EventArgs e) {
        }

        [System.Web.Services.WebMethod]
        public static object[] LoadData() {
            /**
             * Page method requiest to server for database data.
             * Request about item fields & count of fields, 'nd datablock.
             * TODO: this is test version.
             */
            last = 0;
            object[] result = new object[5];
            for (int i = 0; i < 5; ++i) result[i] = "Caption " + i.ToString();

            return result;
        }

        [System.Web.Services.WebMethod]
        public static BufferItemList GetItems(string mode, int limit) {
            /**
             * Page method request to server for datablock
             * @param mode the type of downloading (up or down)
             * @param limit - count of item records
             * @returns link to list with downloaded data
             */
            BufferItemList bil = new BufferItemList();

            //if (last > 999) return null;
            //TODO: compare limit and 0 and load before or next block
            if (mode == "down") {
                for (int i = last; i < last + limit; ++i)
                    bil.BufferItems.Add(new BufferItem(5, i));
            }

            if (mode == "up") {
                for (int i = last - limit; i < last + 2 * limit; ++i)
                    bil.BufferItems.Add(new BufferItem(5, i));
            }
            last += limit;

            return bil;
        }
    }
}
