using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core {
    
    public abstract class DisposableClass : IDisposable {

        private bool disposed;

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void DisposeResources() { }

        private void Dispose(bool disposing) {
            if (!disposed) {
                if (disposing) {
                    DisposeResources();
                }
                disposed = true;
            }
        }


    }
}
