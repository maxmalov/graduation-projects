using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Crypto {

    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Text;

    public interface IDecoder {
        SourceText Decode(EncodedText text, Key key);
    }
    
    public class Decoder : IDecoder {

        private FiniteRingElement[] EncodeDigitalRecord(FiniteRingElement[] code, Key key) {
            FiniteRingElement[] result = new FiniteRingElement[code.LongLength];
            Key neededKey = key.generateKeyByLength(code.LongLength);

            for (long i = 0, l = code.LongLength; i < l; ++i) {
                result[i] = code[i] - neededKey[i];
            }
            return result;
        }

        private char[] DecodeToText(FiniteRingElement[] code, Alphabet alphabet) {
            char[] result = new char[code.LongLength];
            for (long i = 0, l = code.LongLength; i < l; ++i) {
                result[i] = alphabet.GetLetterByOrder(code[i]);
            }
            return result;
        }
        
        #region IDecoder Members

        SourceText IDecoder.Decode(EncodedText text, Key key) {
            return new SourceText(DecodeToText(EncodeDigitalRecord(text.GetDigitCode(), key), text.Alphabet), text.Alphabet);
        }

        #endregion
    }
}
