using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using VigenereCode.Core.Ring;
using VigenereCode.Core.Text;

namespace VigenereCode.Core.Crypto {
    
    public class Key : DisposableClass {

        private FiniteRing ring;
        private FiniteRingElement[] sequence;

        public Key(char[] sequence, Alphabet alphabet) {
            ring = new FiniteRing(alphabet.Card);
            
            this.sequence = new FiniteRingElement[sequence.LongLength];

            for (long i = 0, l = sequence.LongLength; i < l; ++i) {
                this.sequence[i] = alphabet.GetLetterOrder(sequence[i]);
            } 

        }

        public Key(FiniteRing ring, FiniteRingElement[] sequence) {
            this.ring = ring;
            this.sequence = sequence;
        }

        public Key generateKeyByLength(long length) {

            if (length < 1) {
                throw new ArgumentException("Key length must be greater than 0");
            }

            FiniteRingElement[] result = new FiniteRingElement[length];

            long i = 0, l;
            
            //Fill with repeats
            for (i = 0, l = (long) (length / sequence.LongLength); i < l; ++i) {
                for (long j = 0; j < sequence.LongLength; ++j) {
                    result[i * sequence.LongLength + j] = sequence[j];
                }
            }
            
            //Fill remainder
            for (long j = i * sequence.LongLength, k = 0; j < length; ++j, ++k) {
                result[j] = sequence[k];
            }

            return new Key(ring, result);
        }

        public FiniteRingElement this[long index] {
            get {
                return sequence[index];
            }
        }

        protected override void DisposeResources() {
            ring.Dispose();
        }

        public override bool Equals(object obj) {
            if(!ring.Equals((obj as Key).ring)) {
                return false;
            }

            if (sequence.LongLength != (obj as Key).sequence.LongLength) {
                return false;
            }

            for (long i = 0; i < sequence.LongLength; ++i) { 
                if(!sequence[i].Equals((obj as Key).sequence[i])) {
                    return false;
                }
             }

            return true;
        }

    }
}
