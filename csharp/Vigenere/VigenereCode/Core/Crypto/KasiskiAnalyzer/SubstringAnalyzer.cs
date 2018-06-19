using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Crypto.KasiskiAnalyzer {
    
    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Text;
    using VigenereCode.Core.Utils;

    public class DistanceAnalyzer : IAnalyzer { 
        private string subString;
        private List<int> occurrences;
        private int commonGreatestDenomintor = 1;
        private List<int> distances;

        public DistanceAnalyzer(string substr, List<int> occurrences) {
            subString = substr;
            this.occurrences = occurrences;
        }

        private void CountDistances() {
            distances = new List<int>();
            int lastOccurence = 0;
            foreach (int o in occurrences) {
                if (occurrences.IndexOf(o) != 0) {
                    distances.Add(o - lastOccurence);
                }
                lastOccurence = o;
            }
        }
        
        #region IAnalyzer Methods

        public void Analyze(ILogger logger) {
            CountDistances();
            commonGreatestDenomintor = CommonGreatestDenominator.Count(this.distances);

            List<string> log = new List<string>();

            log.Add(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
            log.Add("Substring " + subString + " occurrs " + occurrences.Count + " times:");
            log.Add("\t First occurrence is on " + occurrences[0] + " position");
            foreach (int distance in distances) {
                log.Add("\t Than after " + distance + " symbols");
            }
            log.Add("\t* Suggested key length: " + commonGreatestDenomintor);
            log.Add("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

            logger.Log(log);
        }
        
        #endregion
    }


    public class SubstringKeyAnalyzer : IAnalyzer {
    
        private EncodedText encodedText;

        private int substrLength;
        private int occurrencesFilter;

        public SubstringKeyAnalyzer(EncodedText et, int subStringLength = 3, int occurrencesFilter = 4) {
            encodedText = et;
            substrLength = subStringLength;
            this.occurrencesFilter = occurrencesFilter;
        }

        public void ChangeSettings(int subStringLength = 3, int occurrencesFilter = 4) {
            substrLength = subStringLength;
            this.occurrencesFilter = occurrencesFilter;
        }

        private static int FindNextOccurrence(string text, string substr, int index) {
            return text.IndexOf(substr, index);     
        }

        private Dictionary<string, List<int>> CountSubstrOccurrences() {
            Dictionary<string, List<int>> substrOccurrences = new Dictionary<string, List<int>>();
            string text = encodedText.ToString();
            string substr;
            for (int i = 0, l = text.Length - substrLength + 1; i < l; ++i) {
                substr = text.Substring(i, substrLength);

                if(!substrOccurrences.ContainsKey(substr)) {

                    int occurrence = text.IndexOf(substr, i + 1);
                    if (occurrence != -1) {
                        substrOccurrences.Add(substr, new List<int>());
                        substrOccurrences[substr].Add(i);

                        for (; occurrence < text.Length - substrLength + 1 && occurrence != -1; occurrence = SubstringKeyAnalyzer.FindNextOccurrence(text, substr, occurrence + substrLength)) {
                            substrOccurrences[substr].Add(occurrence);
                        }

                        if (substrOccurrences[substr].Count < occurrencesFilter) {
                            substrOccurrences.Remove(substr);
                        }
                    }
                }
            }
            return substrOccurrences;
        }

        #region IAnalyzer Members

        public void Analyze(ILogger logger) {

            logger.Clear();

            Dictionary<string, List<int>> occurencesMap = CountSubstrOccurrences();
            
            foreach (KeyValuePair<string, List<int>> occurenceMap in occurencesMap) {
                (new DistanceAnalyzer(occurenceMap.Key, occurenceMap.Value)).Analyze(logger);
            }    
        }

        #endregion
    }
}
