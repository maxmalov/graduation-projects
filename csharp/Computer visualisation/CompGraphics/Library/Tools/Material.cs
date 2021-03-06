using System;
using System.Drawing;

namespace Library {
    public class Material {   //определяет свойства предмета, такие как цвет, зеркальность, прозрачность и т д
        private Color color;
        private double Kd, Ks, Kr, Kt, pFong;
        private double refractiveIndex = 1;
        public Material(Color color, double Kd, double Ks, double Kr, double Kt, double pFong) {
            this.color = color;
            this.Kd = Kd;   //diffuse from 0 to 1
            this.Ks = Ks;   //specular from 0 to 1
            this.Kr = Kr;   //reflection from 0 to 1
            this.Kt = Kt;   //tranceparence from 0 to 1
            this.pFong = pFong;
        }
        public Color Color {
            get {
                return color;
            }
        }
        public double FongCoeff {
            get {
                return pFong;
            }
        }
        public double Diffusion {
            get {
                return Kd;
            }
        }
        public double Specularity {
            get {
                return Ks;
            }
        }
        public double Transparency {
            get {
                return Kt;
            }
        }
        public double Reflection {
            get {
                return Kr;
            }
        }

        public double RefractiveIndex {
            get {
                return refractiveIndex;
            }
            set {
                refractiveIndex = value;
            }
        }
    }
}
