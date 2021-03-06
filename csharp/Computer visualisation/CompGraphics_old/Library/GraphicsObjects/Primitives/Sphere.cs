using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Library
{
    public class Sphere : IGraphicsObject3D
    {
        private double radius;
        private Point3D center;
        private Material material;
        private Bitmap texture;

        public Sphere(Point3D origin, double R, Material material)
        {
            radius = R;
            this.center = origin;
            this.material = material;
        }

        public Sphere(Point3D origin, double R, Material material, Bitmap bmp)
        {
            radius = R;
            this.center = origin;
            this.material = material;
            texture = bmp;
        }
        //public Material Material
        //{
        //    set
        //    {
        //        material = value;
        //    }
        //}
        public IntersectionInfo Intersection(Ray r)
        {
            double epsilon = 0.01;
            Vector3D v = new Vector3D(r.Origin.X - center.X, r.Origin.Y - center.Y, r.Origin.Z - center.Z);
            double A = r.Direction.LengthSquare;
            double B = VectorOperations.ScalarProduct(r.Direction, v);
            double C = v.LengthSquare - radius * radius;
            double D = B * B - A * C;

            if (D <= 0.0)
                return null;

            double t1 = (-B - Math.Sqrt(D)) / A;
            double t2 = (-B + Math.Sqrt(D)) / A;
            double t = t1;

            if (t2 <= epsilon)
                return null;

            if (t1 <= epsilon)    //луч идет из шара
                t = t2;

            Point3D P = new Point3D(r.Origin.X + r.Direction.X * t,
                                    r.Origin.Y + r.Direction.Y * t,
                                    r.Origin.Z + r.Direction.Z * t);    //первая точка пересечения

            Vector3D N = new Vector3D(center,  P);   //вектор нормали единичной длины
            N *= (1 / N.Length);
            if (t1 <= epsilon)    //луч идет из шара
                N *= (-1.0);


            if (texture != null)
            {
                Point3D E = new Point3D(P.X - center.X, P.Y - center.Y, P.Z - center.Z);
                double psi, fi;
                psi = Math.Asin(E.Z / radius);

                if (Math.Abs(psi) == Math.PI / 2)
                    fi = 0;
                else
                {
                    double cosfi = E.X / (radius * Math.Cos(psi));
                    if (cosfi > 1)
                        cosfi = 1;
                    if (cosfi < -1)
                        cosfi = -1;
                    fi = Math.Acos(cosfi);
                    if (E.Y < 0)
                        fi = 2 * Math.PI - fi;
                }
                Material m;
                lock (texture)
                {
                    int x = (int)((fi / (Math.PI * 2)) * (texture.Width - 1));
                    int y = (int)((0.5 - psi / Math.PI) * (texture.Height - 1));
                    m = new Material(texture.GetPixel(x, y), material.Diffusion, material.Specularity,
                                            material.Reflection, material.Transparency, material.FongCoeff);
                }
                material = m;
            }
            return new IntersectionInfo(P, N, material);
        }
    }
}
