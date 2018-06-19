using System;

namespace Library {
    public class Triangle2D {
        private Point2D v1, v2, v3;

        public Triangle2D(Point2D v1, Point2D v2, Point2D v3) {
            this.v1 = new Point2D(v1.X, v1.Y);
            this.v2 = new Point2D(v2.X, v2.Y);
            this.v3 = new Point2D(v3.X, v3.Y);
        }

        public Point2D V1 {
            get {
                return v1;
            }
        }

        public Point2D V2 {
            get {
                return v2;
            }
        }

        public Point2D V3 {
            get {
                return v3;
            }
        }
    }
}
