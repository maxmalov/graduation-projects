using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Utils {
    public class CommonGreatestDenominator {

        public static int Count(int first, int second) {
            return (first > second) ? Calculate(first, second) : Calculate(second, first);
        }

        private static int Calculate(int greater, int lower) {
            if (greater == lower || lower == 0) {
                return greater;
            }

            int buff;
            while (lower > 0) {
                greater %= lower;
                
                buff = lower;
                lower = greater;
                greater = buff;
            }

            return greater;

        }

        public static int Count(List<int> source) {
            int cgd = source[0];
            for (int i = 1, l = source.Count; i < l; ++i) {
                cgd = CommonGreatestDenominator.Count(cgd, source[i]);
                if (cgd == 1) {
                    return 1;
                }
            }
            return cgd;
        }
    }
}
