using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using NUnit;
using NUnit.Framework;
using NUnit.Framework.Constraints;

namespace VigenereCodeTests.Core.Ring {

    using VigenereCode.Core.Ring;
        
    [TestFixture]
    public class FiniteRingTest {

        private FiniteRing obj;
        private int order = 32;

        [SetUp]
        public void setUp() {
            obj = new FiniteRing(order);
        }

        [TearDown]
        public void tearDown() {
            (obj as FiniteRing).Dispose();
        }

        [Test]
        [ExpectedException(typeof(ArgumentException))]
        public void incorrectOrderCreateTest() {
            FiniteRing fail = new FiniteRing(1);
        }


        [Test]
        public void OrderTest() { 
            Assert.That(obj.Order, Is.EqualTo(order));
        }

        [Test]
        public void getElementTest() {
            int number = 34;
            Assert.That(obj.GetElement(number), Is.EqualTo(new FiniteRingElement(number, obj)));
        }

        [Test]
        public void GetHashCodeTest() {
            Assert.That(obj.GetHashCode(), Is.EqualTo(order));
        }

        [Test]
        public void EqualsTest() {
            Assert.That(obj, Is.EqualTo(new FiniteRing(order)));            
        }

        [Test]
        public void NonEqualsTest() {
            Assert.That(obj, Is.Not.EqualTo(new FiniteRing(order + 1)));
        }

    }

    [TestFixture]
    public class FiniteRingElementTest {

        private int order = 32;
        private FiniteRing ring;

        private int number = -39;
        private FiniteRingElement elem;

        [SetUp]
        public void setUp() {
            ring = new FiniteRing(order);
            elem = ring.GetElement(number);
        }

        [TearDown]
        public void tearDown() {
            (ring as FiniteRing).Dispose();
            (elem as FiniteRingElement).Dispose();
        }

        [Test]
        public void ValueTest() {
            
            int value = number % order;
            if(value < 0) {
                value = order + value;
            }

            Assert.That(elem.Value, Is.EqualTo(value));
        }

        [Test]
        public void OriginValueTest() {
            Assert.That(elem.OriginValue, Is.EqualTo(number));
        }

        [Test]
        public void OwnerRingTest() {
            Assert.That(elem.OwnerRing, Is.EqualTo(ring));
        }

        [Test]
        public void SuccessAdditionTest() {
            int additionNumber = 123;
            FiniteRingElement addition = ring.GetElement(additionNumber);

            Assert.That((elem + addition).Value, Is.EqualTo(20));
        }

        [Test]
        [ExpectedException(typeof(ArgumentException))]
        public void NonEqualRingsAdditionTest() {
            FiniteRing otherRing = new FiniteRing(order + 1);
            FiniteRingElement addition = otherRing.GetElement(15);

            FiniteRingElement result = elem + addition;
        }

        [Test]
        public void GetHashCodeTest() {
            Assert.That(elem.GetHashCode(), Is.EqualTo(elem.Value));
        }

        [Test]
        public void EqualsTest() {
            int compareNumber = 153;
            Assert.That(elem, Is.EqualTo(ring.GetElement(compareNumber)));
        }

        [Test]
        public void NonEqualsTest() {
            int compareNumber = -153;
            Assert.That(elem, Is.Not.EqualTo(ring.GetElement(compareNumber)));
        }
    }
}
