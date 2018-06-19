using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Utils {
    
    public interface ILogger {
        void Log(IEnumerable<string> message);
        void Clear();
    }
}
