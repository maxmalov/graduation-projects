using System;

namespace Library {
    public class Point2D {
        private double x, y;

        public Point2D(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public double X {
            get {
                return x;
            }
            set {
                x = value;
            }
        }

        public double Y {
            get {
                return y;
            }
            set {
                y = value;
            }
        }

        public Point3D ConvertTo3D {
            get {
                return new Point3D(x, y, 0);
            }
        }
    }
}
