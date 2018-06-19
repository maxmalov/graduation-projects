using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace VigenereCode.Core.Ring {

    public class FiniteRing : DisposableClass {
        
        private int order;

        public FiniteRing(int order) {
            if (order < 2) {
                throw new ArgumentException("Ring order must be greater than 1");
            }
            
            this.order = order;
        }

        public int Order {
            get {
                return order;
            }
        }

        public FiniteRingElement GetElement(int value) {
            return new FiniteRingElement(value, this);
        }

        public override int GetHashCode() {
            return order;
        }

        public override bool Equals(object ring) {
            return this.GetHashCode() == (ring as FiniteRing).GetHashCode();           
        }

        public bool Contains(FiniteRingElement elem) {
            return order == elem.OwnerRing.Order;
        }

        protected override void DisposeResources() {
            order = 0;
        }

    }

    public class FiniteRingElement : DisposableClass {

        private int ringValue;
        private int originValue;
        private FiniteRing ownerRing;

        public FiniteRingElement(int number, FiniteRing owner) {
            originValue = number;
            ownerRing = owner;
            ringValue = originValue % ownerRing.Order;

            if (ringValue < 0) {
                ringValue = OwnerRing.Order + ringValue;
            }
        }

        public int Value {
            get {
                return ringValue;
            }
        }

        public int OriginValue {
            get {
                return originValue;
            }
        }

        public FiniteRing OwnerRing {
            get {
                return ownerRing;
            }
        }

        public static FiniteRingElement operator +(FiniteRingElement elem1, FiniteRingElement elem2) {
            
            if (!elem1.OwnerRing.Equals(elem2.OwnerRing)) {
                throw new ArgumentException("Rings must be similar!");
            }

            return new FiniteRingElement(elem1.Value + elem2.Value, elem1.OwnerRing);
        }

        public static FiniteRingElement operator -(FiniteRingElement elem1, FiniteRingElement elem2) {

            if (!elem1.OwnerRing.Equals(elem2.OwnerRing)) {
                throw new ArgumentException("Rings must be similar!");
            }

            return new FiniteRingElement(elem1.Value - elem2.Value, elem1.OwnerRing);
        }

        public static FiniteRingElement Distance(FiniteRingElement elem1, FiniteRingElement elem2) {

            if (!elem1.OwnerRing.Equals(elem2.OwnerRing)) {
                throw new ArgumentException("Rings must be similar!");
            }

            return new FiniteRingElement(Math.Abs(elem1.Value - elem2.Value), elem1.OwnerRing);
        }

        public override int GetHashCode() {
            return ringValue;
        }

        public override bool Equals(object obj) {
            
            if (OwnerRing.Order != (obj as FiniteRingElement).OwnerRing.Order) {
                return false;
            }

            return ringValue == (obj as FiniteRingElement).Value;
        }

        protected override void DisposeResources() {
            ringValue = originValue = 0;
            ownerRing.Dispose();
        }
    }
}
