using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit.Framework;

namespace VigenereCodeTests.Core.Crypto {

    using VigenereCode.Core.Ring;
    using VigenereCode.Core.Crypto;
    
    [TestFixture]
    public class KeyTest {

        private int order = 32;
        private FiniteRing ring;

        private int keyLength = 40;
        private FiniteRingElement[] initialSequence;

        [SetUp]
        public void setUp() {
            
            ring = new FiniteRing(order);
            initialSequence = new FiniteRingElement[keyLength];

            for (int i = 0; i < keyLength; ++i) { 
                initialSequence[i] = ring.GetElement((new Random()).Next());
            }
        }

        [TearDown]
        public void tearDown() {
            ring.Dispose();
            initialSequence = null;
        }

        [Test]
        public void generateKeyByLengthTest() {
            int expectedKeyLength = 15;
            FiniteRingElement[] expectedSequence = new FiniteRingElement[expectedKeyLength];

            for (int i = 0; i < expectedKeyLength; ++i) {
                expectedSequence[i] = initialSequence[i];
            }

            Assert.That((new Key(ring, initialSequence)).generateKeyByLength(expectedKeyLength), 
                Is.EqualTo(new Key(ring, expectedSequence)));
        }

        [Test]
        [ExpectedException(typeof(ArgumentException))]
        public void generateKeyByBadLengthTest() {
            Key k = (new Key(ring, initialSequence)).generateKeyByLength(0);
        }
        
    }
}
