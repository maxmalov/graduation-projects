using System;

namespace Library {
    public class Interpolation {
        public static Point3D call(Point3D p1, Point3D p2, Point3D p3, Point3D p4, Point2D p) {
            
            double x = ((p1.X + p2.X + p3.X + p4.X) + p.X * (p1.X - p2.X - p3.X + p4.X) + p.Y * (p1.X + p2.X - p3.X - p4.X) + p.X * p.Y * (p1.X - p2.X + p3.X - p4.X)) / 4,
                y = ((p1.Y + p2.Y + p3.Y + p4.Y) + p.X * (p1.Y - p2.Y - p3.Y + p4.Y) + p.Y * (p1.Y + p2.Y - p3.Y - p4.Y) + p.X * p.Y * (p1.Y - p2.Y + p3.Y - p4.Y)) / 4,
                z = ((p1.Z + p2.Z + p3.Z + p4.Z) + p.X * (p1.Z - p2.Z - p3.Z + p4.Z) + p.Y * (p1.Z + p2.Z - p3.Z - p4.Z) + p.X * p.Y * (p1.Z - p2.Z + p3.Z - p4.Z)) / 4;
            return new Point3D(x, y, z);
        }
    }
}
