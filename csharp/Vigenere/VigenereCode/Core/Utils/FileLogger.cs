using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Utils {
    public class FileLogger : ILogger {

        private string filePath;

        public FileLogger(string filePath) {
            this.filePath = filePath;
        }

        #region ILogger Members

        public void Log(IEnumerable<string> message) {
            File.AppendAllLines(filePath, message);
        }

        public void Clear() {
            File.Delete(filePath);
        }

        #endregion
    }
}
