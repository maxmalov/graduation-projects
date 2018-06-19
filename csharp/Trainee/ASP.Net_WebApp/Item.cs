using System;
using System.Collections.Generic;

namespace ItemsObjects {
    
    public class BufferItem {
        int id;
        object[] fields;

        public BufferItem(int size, int exs) {
            id = exs;
            fields = new object[size];
            for(int i = 0; i < size; ++i) 
				fields[i] = "Item " + exs.ToString() + " Field " + i.ToString(); 
        }
        
        
        public int ID {
            get { return id; }
        }

        public object[] Fields {
            get { return fields; }
        }
    }
    
    public class BufferItemList {
        private List<BufferItem> _bufferItems = new List<BufferItem>();

        public List<BufferItem> BufferItems {
            get {
                return _bufferItems;
            }
        }
    }
}