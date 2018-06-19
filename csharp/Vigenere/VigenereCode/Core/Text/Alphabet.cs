using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using VigenereCode.Core.Ring;

namespace VigenereCode.Core.Text {
    
    public abstract class Alphabet : DisposableClass {

        protected Dictionary<char, FiniteRingElement> alphabet; 
        protected int alphabetCard;
        protected FiniteRing ring;

        public Alphabet() {
            
            initAlphabet();
        }

        protected virtual void initAlphabet() { }

        public FiniteRingElement GetLetterOrder(char letter) {
            if (!Contains(letter)) {
                throw new ArgumentException("Letter must be in the alphabet");
            }

            return alphabet[letter];
        }

        public char GetLetterByOrder(FiniteRingElement order) {
            
            if (!ring.Contains(order)) {
                throw new ArgumentOutOfRangeException();
            }

            foreach (KeyValuePair<char, FiniteRingElement> letter in alphabet) {
                if (letter.Value.Equals(order)) {
                    return letter.Key;
                }                
            }

            throw new ArgumentOutOfRangeException();
        }

        public bool Contains(char letter) {
            return alphabet.Keys.Contains<char>(letter);
        }

        public int Card {
            get {
                return alphabetCard;
            }
        }

        protected override void DisposeResources() {
            alphabetCard = 0;
            alphabet.Clear();
            ring.Dispose();
        }

        public static Alphabet Russian {
            get {
                return new RussianAlphabet();
            }
        }

        public char[] GetLetters() {
            char[] letters = new char[alphabet.Count];
            long i = 0;
            foreach (KeyValuePair<char, FiniteRingElement> letterElement in alphabet) {
                letters[i] = letterElement.Key;
                i++;
            }
            return letters;
        }

        public virtual KeyValuePair<char, FiniteRingElement> GetOftenLetter() {
            throw new NotSupportedException();
        }
    }

    public class RussianAlphabet : Alphabet {

        public RussianAlphabet() : base() { }

        protected sealed override void initAlphabet() {
            alphabetCard = 32; // ё == е

            alphabet = new Dictionary<char, FiniteRingElement>();
            ring = new FiniteRing(alphabetCard);

            alphabet.Add('А', ring.GetElement(0));
            alphabet.Add('Б', ring.GetElement(1));
            alphabet.Add('В', ring.GetElement(2));
            alphabet.Add('Г', ring.GetElement(3));
            alphabet.Add('Д', ring.GetElement(4));
            alphabet.Add('Е', ring.GetElement(5));
            alphabet.Add('Ж', ring.GetElement(6));
            alphabet.Add('З', ring.GetElement(7));
            alphabet.Add('И', ring.GetElement(8));
            alphabet.Add('Й', ring.GetElement(9));
            alphabet.Add('К', ring.GetElement(10));
            alphabet.Add('Л', ring.GetElement(11));
            alphabet.Add('М', ring.GetElement(12));
            alphabet.Add('Н', ring.GetElement(13));
            alphabet.Add('О', ring.GetElement(14));
            alphabet.Add('П', ring.GetElement(15));
            alphabet.Add('Р', ring.GetElement(16));
            alphabet.Add('С', ring.GetElement(17));
            alphabet.Add('Т', ring.GetElement(18));
            alphabet.Add('У', ring.GetElement(19));
            alphabet.Add('Ф', ring.GetElement(20));
            alphabet.Add('Х', ring.GetElement(21));
            alphabet.Add('Ц', ring.GetElement(22));
            alphabet.Add('Ч', ring.GetElement(23));
            alphabet.Add('Ш', ring.GetElement(24));
            alphabet.Add('Щ', ring.GetElement(25));
            alphabet.Add('Ъ', ring.GetElement(26));
            alphabet.Add('Ы', ring.GetElement(27));
            alphabet.Add('Ь', ring.GetElement(28));
            alphabet.Add('Э', ring.GetElement(29));
            alphabet.Add('Ю', ring.GetElement(30));
            alphabet.Add('Я', ring.GetElement(31));
        }

        public override KeyValuePair<char,FiniteRingElement>  GetOftenLetter() {
            char oftenLetter = 'О';
            return new KeyValuePair<char, FiniteRingElement>(oftenLetter, alphabet[oftenLetter]);
        }

    }
}
