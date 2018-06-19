using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Crypto {

    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Text;

    public interface IEncoder {
        EncodedText Encode(SourceText text, Key key);        
    }

    public class Encoder : IEncoder {

        private FiniteRingElement[] EncodeDigitalRecord(FiniteRingElement[] code, Key key) {
            FiniteRingElement[] result = new FiniteRingElement[code.LongLength];
            Key neededKey = key.generateKeyByLength(code.LongLength);

            for (long i = 0, l = code.LongLength; i < l; ++i) {
                result[i] = code[i] + neededKey[i];
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

        #region IEncoder Members

        EncodedText IEncoder.Encode(SourceText text, Key key) {
            return new EncodedText(DecodeToText(EncodeDigitalRecord(text.GetDigitCode(), key), text.Alphabet), text.Alphabet);
        }

        #endregion
    }
}
