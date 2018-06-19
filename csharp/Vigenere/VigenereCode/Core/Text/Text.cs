using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

using VigenereCode.Core.Ring;
using VigenereCode.Core.Crypto;

namespace VigenereCode.Core.Text {

    public abstract class AText : DisposableClass {
        
        protected char[] text = null;
        protected FiniteRingElement[] code = null;
        protected Alphabet alphabet = null;

        public AText(string path, Alphabet alphabet) {
            this.alphabet = alphabet;
            ReadFile(path);
        }

        public AText(char[] text, Alphabet alphabet) {
            this.text = text;
            this.alphabet = alphabet;
        }

        protected virtual void ReadFile(string path) {
            if (!File.Exists(path)) {
                throw new FileNotFoundException();
            }

            using (BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open), Encoding.GetEncoding(1251))) {
                
                text = new char[reader.BaseStream.Length];
                for (long i = 0, l = reader.BaseStream.Length; i < l; ++i) {
                    text[i] = reader.ReadChar();
                    if (!alphabet.Contains(text[i])) {
                        throw new ArgumentException("Symbol " + text[i] + " is not in the given alphabet!");
                    }
                }
            }
        }

        protected virtual void Digitize() {
            code = new FiniteRingElement[text.LongLength];
            for (long i = 0, l = text.LongLength; i < l; ++i) {
                code[i] = alphabet.GetLetterOrder(text[i]);
            }
        }

        public FiniteRingElement[] GetDigitCode() {
            if (code == null) {
                Digitize();
            }

            return code;
        }

        public Alphabet Alphabet {
            get {
                return alphabet;
            }
        }

        public void WriteFile(string path) {
            using (BinaryWriter writer = new BinaryWriter(File.Open(path, FileMode.Create), Encoding.GetEncoding(1251))) {
                writer.Write(text);
            }
        }

        public long Length {
            get {
                return text.LongLength;
            }
        }

        public override string ToString() {
            return new string(text);
        }
    }

    public class SourceText : AText {
        
        public SourceText(char[] text, Alphabet alphabet) : base(text, alphabet) {
        }

        public SourceText(string path, Alphabet alphabet) : base(path, alphabet) {
        }
    }

    public class EncodedText : AText {

        public EncodedText(char[] text, Alphabet alphabet) : base(text, alphabet) {
        }

        public EncodedText(string path, Alphabet alphabet) : base(path, alphabet) {
        }

        public char this[long indexer] {
            get {
                return text[indexer];
            }
        }
    }

}
