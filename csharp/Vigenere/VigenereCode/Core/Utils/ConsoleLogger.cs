using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Utils {
    public class ConsoleLogger : ILogger {
        
        #region ILogger Members

        public void Log(IEnumerable<string> message) {
            foreach (string s in message) {
                Console.WriteLine(s);
            }
        }

        public void Clear() {
            Console.Clear();
        }

        #endregion
    }
}
