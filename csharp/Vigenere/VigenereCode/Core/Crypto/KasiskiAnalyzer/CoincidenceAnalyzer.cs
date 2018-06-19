using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Crypto.KasiskiAnalyzer {

    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Text;
    using VigenereCode.Core.Utils;
    
    public class CoincidenceKeyLengthAnalyzer : IAnalyzer {
        
        private EncodedText encodedText;

        public CoincidenceKeyLengthAnalyzer(EncodedText et) {
            encodedText = et;
        }

        private static double COINCIDENCE_BORDER = 0.0553;

        private static Dictionary<char, long> GetLetterOccurrenceDictionary(Alphabet alphabet) {
            Dictionary<char, long> result = new Dictionary<char, long>();
            char[] letters = alphabet.GetLetters();
            for (long i = 0, l = letters.LongLength; i < l; ++i) {
                result.Add(letters[i], 0);
            }
            return result;
        }

        public static Dictionary<char, long> GetLettersOccurrences(EncodedText et) {
            Dictionary<char, long> result = CoincidenceKeyLengthAnalyzer.GetLetterOccurrenceDictionary(et.Alphabet);
            for (long i = 0, l = et.Length; i < l && et[i] != '\0'; ++i) {
                result[et[i]]++;
            }
            return result;
        }

        private static double GetCoincidenceIndex(EncodedText et) {
            Dictionary<char, long> lettersOccurences = CoincidenceKeyLengthAnalyzer.GetLettersOccurrences(et);
            long sum = 0;
            foreach (KeyValuePair<char, long> letterOccurrences in lettersOccurences) {
                sum += letterOccurrences.Value * letterOccurrences.Value;
            }
            return (double)sum / (et.Length * et.Length);
        }

        private EncodedText GetTextSlice(long layer) {
            long length = (encodedText.Length % layer == 0) ? (long)(encodedText.Length / layer) : (long)(encodedText.Length / layer + 1);
            char[] sequence = new char[length];
            for (long i = 0, j = 0; j < length; i += layer, j++) {
                sequence[j] = encodedText[i];
            }
            return new EncodedText(sequence, encodedText.Alphabet);
        }

        public void Analyze(ILogger logger) {
            
            double coincidenceIndex = GetCoincidenceIndex(encodedText);
            logger.Clear();
            List<string> log = new List<string>();           
            long i;
            for (i = 1; coincidenceIndex < COINCIDENCE_BORDER; ++i) {
                log.Add(i + ": Coincidence index: " + coincidenceIndex);
                coincidenceIndex = GetCoincidenceIndex(GetTextSlice(i));
            }

            log.Add("Coincidence index: " + coincidenceIndex + " is greater than " + COINCIDENCE_BORDER);
            log.Add("Key length supposed to be: " + i);

            logger.Log(log);
        }
    }

    public class OccurenceAnalyzer : IAnalyzer {

        private EncodedText encodedText;
        private int occurrenceFilter;

        public OccurenceAnalyzer(EncodedText et, int occurrenceFilter) {
            encodedText = et;
            this.occurrenceFilter = occurrenceFilter;
        }

        private List<KeyValuePair<char, long>> GetOftenLetters() {
            Dictionary<char, long> occurrences = CoincidenceKeyLengthAnalyzer.GetLettersOccurrences(encodedText);
            List<KeyValuePair<char, long>> result = new List<KeyValuePair<char, long>>();

            foreach (KeyValuePair<char, long> occurrence in occurrences) {
                result.Add(new KeyValuePair<char,long>(occurrence.Key, occurrence.Value));
            }

            result.Sort((firstPair, nextPair) => {
                return nextPair.Value.CompareTo(firstPair.Value);
            });

            /*
            for (int i = 10; result.Count > i; ) {
                result.RemoveAt(i);
            }
             */
            return result;
        }

        private static List<KeyValuePair<char, long>> GetOftenLettersTemplate() {
            List<KeyValuePair<char, long>> result = new List<KeyValuePair<char, long>>();
            
            result.Add(new KeyValuePair<char,long>('О',10));
            result.Add(new KeyValuePair<char,long>('А',9));
            result.Add(new KeyValuePair<char,long>('Е',8));
            result.Add(new KeyValuePair<char,long>('И',7));
            result.Add(new KeyValuePair<char,long>('Н',6));
            result.Add(new KeyValuePair<char,long>('Т',5));
            result.Add(new KeyValuePair<char,long>('Р',4));
            result.Add(new KeyValuePair<char,long>('С',3));
            result.Add(new KeyValuePair<char,long>('Л',2));
            result.Add(new KeyValuePair<char,long>('В',1));

            result.Sort((firstPair, nextPair) => {
                return nextPair.Value.CompareTo(firstPair.Value);
            });
            
            return result;
        }
        
        #region IAnalyzer Members

        public void Analyze(ILogger logger) {

            List<KeyValuePair<char, long>> occurrences = GetOftenLetters();
            //List<KeyValuePair<char, long>> template = GetOftenLettersTemplate();


            List<string> log = new List<string>();
            FiniteRingElement distance = null;
            log.Add(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            for(int i = 0, l = occurrences.Count; i < l; ++i) {
                //distance = FiniteRingElement.Distance(Alphabet.Russian.GetLetterOrder(occurrences[i].Key), Alphabet.Russian.GetLetterOrder(template[i].Key));
                log.Add("Letter " + occurrences[i].Key + " occurrs " + occurrences[i].Value + " times." /* + " Distance form " + template[i].Key + " is " + distance.Value + " means letter " + Alphabet.Russian.GetLetterByOrder(distance)*/);
            }

            log.Add("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");

            logger.Log(log);
        }

        #endregion
    }

    public class CoincidenceKeyTextAnalyzer : IAnalyzer {

        private EncodedText encodedText;
        private int keyLength;

        private KeyValuePair<char, FiniteRingElement> oftenLetter;

        public CoincidenceKeyTextAnalyzer(EncodedText et, int keyLength) {
            encodedText = et;
            this.keyLength = keyLength;
            oftenLetter = et.Alphabet.GetOftenLetter();
        }
        
        /**
         * Returns encoded text shifted by @offset symbols
         */
        private EncodedText GetTextSlice(int layer) {
            long length = (encodedText.Length % keyLength == 0) ? (long)(encodedText.Length / keyLength) : (long)(encodedText.Length / keyLength + 1);
            char[] sequence = new char[length];
            for (long i = layer, j = 0; j < length && i < encodedText.Length; i += keyLength, j++) {
                sequence[j] = encodedText[i];
            }
            return new EncodedText(sequence, encodedText.Alphabet);
        }
        
        #region IAnalyzer Members

        public void Analyze(ILogger logger) {
            logger.Clear();
            for (int i = 0; i < keyLength; ++i) {
                (new OccurenceAnalyzer(GetTextSlice(i), 5)).Analyze(logger);                 
            }
        }

        #endregion
    }
}
