using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Crypto.KasiskiAnalyzer {

    using VigenereCode.Core.Utils;

    interface IAnalyzer {
        void Analyze(ILogger logger);
    }
}
