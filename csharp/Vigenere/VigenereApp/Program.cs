using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereApp {

    using VigenereCode.Core.Text;
    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Crypto;
    using VigenereCode.Core.Crypto.KasiskiAnalyzer;
    using VigenereCode.Core.Utils;

    class Program {

        #region Task 2 Solving

        private static Key ReadKey(string path, Alphabet alphabet) {
            
            if (!File.Exists(path)) {
                throw new FileNotFoundException();
            }

            char[] text = null;

            using (BinaryReader reader = new BinaryReader(File.Open(path, FileMode.Open), Encoding.GetEncoding(1251))) {

                text = new char[reader.BaseStream.Length];
                for (long i = 0, l = reader.BaseStream.Length; i < l; ++i) {
                    text[i] = reader.ReadChar();
                    if (!alphabet.Contains(text[i])) {
                        throw new ArgumentException("Symbol " + text[i] + " is not in the given alphabet!");
                    }
                }
            }

            return new Key(text, alphabet);
        }

        static private void Task2Solver(string logRootPath) {
            SourceText st = new SourceText(logRootPath + "\\source.txt", Alphabet.Russian);
            Key key = ReadKey(logRootPath + "\\key.txt", Alphabet.Russian);

            IEncoder encoder = new VigenereCode.Core.Crypto.Encoder();
            EncodedText outText = encoder.Encode(st, key);

            outText.WriteFile(logRootPath + "\\result.txt");

            CoincidenceKeyLengthAnalyzer ca = new CoincidenceKeyLengthAnalyzer(outText);
            ILogger coincidenceKeyLengthAnalyzerLogger = new FileLogger(logRootPath + "\\KasiskiTest.log");
            ca.Analyze(coincidenceKeyLengthAnalyzerLogger);            
            
            //IDecoder decoder = new Decoder();
            //(decoder.Decode(outText, key)).WriteFile(logRootPath + "\\source-back.txt");
        }
        
        #endregion

        #region Task 4 Solving

        static void Task4Solver(string logRootPath) {
            EncodedText et = new EncodedText(logRootPath + "\\encoded.txt", Alphabet.Russian);

            //CoincidenceKeyText(logRootPath, et);

            //CoincidenceKeyLength(logRootPath, et);

            //Substring(logRootPath, et);

            Decode(logRootPath, et);
        }

        private static void CoincidenceKeyLength(string logRootPath, EncodedText et) {
            CoincidenceKeyLengthAnalyzer ca = new CoincidenceKeyLengthAnalyzer(et);
            ILogger coincidenceKeyLengthAnalyzerLogger = new FileLogger(logRootPath + "\\coincidence-key.log");
            ca.Analyze(coincidenceKeyLengthAnalyzerLogger);
        }

        private static void Decode(string logRootPath, EncodedText et) {
            Key key = new Key("БРУНО".ToCharArray(), Alphabet.Russian);

            IDecoder dec = new Decoder();
            dec.Decode(et, key).WriteFile(logRootPath + "\\source-text.txt");
        }

        private static void Substring(string logRootPath, EncodedText et) {
            SubstringKeyAnalyzer sa = new SubstringKeyAnalyzer(et, 5, 3);
            ILogger substringKeyAnalyzerLogger = new FileLogger(logRootPath + "\\substring.log");
            sa.Analyze(substringKeyAnalyzerLogger);
        }

        private static void CoincidenceKeyText(string logRootPath, EncodedText et) {
            CoincidenceKeyTextAnalyzer ca = new CoincidenceKeyTextAnalyzer(et, 1);
            ILogger coincidenceKeyTextAnalyzerLogger = new FileLogger(logRootPath + "\\coincidence-text.log");
            ca.Analyze(coincidenceKeyTextAnalyzerLogger);
        }

        #endregion

        static void Main(string[] args) {
            //Task2Solver(Directory.GetCurrentDirectory() + "\\..\\..\\task2");
            Task4Solver(Directory.GetCurrentDirectory() + "\\..\\..\\task4");
        }
    }
}
