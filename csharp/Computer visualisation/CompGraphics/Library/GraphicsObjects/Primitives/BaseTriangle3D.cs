using System;

namespace Library {
    public class BaseTriangle3D : IGraphicsObject3D {
        
        private Point3D A, B, C;
        private double epsilon = 1e-2;
        private PolygonalSurface ownerSurface;
        
        public BaseTriangle3D(Point3D v1, Point3D v2, Point3D v3, PolygonalSurface ownerSurface) {
            A = v1;
            B = v2;
            C = v3;
            this.ownerSurface = ownerSurface;
        }

        public Point3D VertexA {
            get {
                return A;
            }
        }
        public Point3D VertexB {
            get {
                return B;
            }
        }
        public Point3D VertexC {
            get {
                return C;
            }
        }

        public IntersectionInfo Intersection(Ray r) {
            Vector3D normal = VectorOperations.VectorProduct(new Vector3D(A, B), new Vector3D(A, C));
            normal *= (1 / normal.Length);

            Vector3D V = new Vector3D(r.Origin.X - A.X, r.Origin.Y - A.Y, r.Origin.Z - A.Z);
            
            //определяем пересекает ли луч треугольник
            double t = -VectorOperations.ScalarProduct(V, normal) / VectorOperations.ScalarProduct(r.Direction, normal);
            if (t <= epsilon || Double.IsNaN(t) || Double.IsInfinity(t))
                return null;

            Point3D crossPoint = new Point3D(r.Origin.X + r.Direction.X * t,
                                             r.Origin.Y + r.Direction.Y * t,
                                             r.Origin.Z + r.Direction.Z * t);

            Vector3D OX = new Vector3D(A, B);
            Vector3D AC = new Vector3D(A, C);
            Vector3D AD = new Vector3D(A, crossPoint);
            Vector3D OY = VectorOperations.VectorProduct(normal, OX);

            Line3D axis = new Line3D(A, OX);
            Line3D ordinate = new Line3D(A, OY);

            double Bx = VectorOperations.Distance(ordinate, B);
            double By = 0;

            double Cx = VectorOperations.Distance(ordinate, C) * ((VectorOperations.Cos(OX, AC) < 0)? -1 : 1);
            double Cy = VectorOperations.Distance(axis, C) * ((VectorOperations.Cos(OY, AC) < 0)? -1 : 1);
            
            double Dx = VectorOperations.Distance(ordinate, crossPoint) * ((VectorOperations.Cos(OX, AD) < 0)? -1 : 1);
            double Dy = VectorOperations.Distance(axis, crossPoint) * ((VectorOperations.Cos(OY, AD) < 0) ? -1 : 1);
            
            int s1 = Math.Sign(Bx * Dy - By * Dx);
            int s2 = Math.Sign((Cx - Bx) * (Dy - By) - (Cy - By) * (Dx - Bx));
            int s3 = Math.Sign(-Cx * (Dy - Cy) + Cy * (Dx - Cx));

            if (s1 == s2 && s1 == s3 && s2 == s3) {
                Material m = ownerSurface.MaterialFront;
                if (VectorOperations.Cos(normal, r.Direction) >= -epsilon && (ownerSurface.MaterialBack != null)) {
                    normal *= (-1);
                    m = ownerSurface.MaterialBack;
                }

                return new IntersectionInfo(crossPoint, normal, m);
            }

            return null;
        }
    }
}
