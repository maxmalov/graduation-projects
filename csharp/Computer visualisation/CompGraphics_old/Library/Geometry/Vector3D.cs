using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class Vector3D
    {
        double x, y, z;
        public Vector3D(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public Vector3D(Point3D p)
        {
            x = p.X;
            y = p.Y;
            z = p.Z;
        }
        public override bool Equals(object obj)
        {
            Vector3D v = (Vector3D)obj;
            Vector3D a = new Vector3D(x - v.x, y - v.y, z - v.z);
            return a.Length < 0.01;
        }
        public Vector3D(Point3D p1, Point3D p2)
        {
            x = p2.X - p1.X;
            y = p2.Y - p1.Y;
            z = p2.Z - p1.Z;
        }
        public double Length
        {
            get
            {
                return Math.Sqrt(x * x + y * y + z * z);
            }
        }
        public double LengthSquare
        {
            get
            {
                return (x * x + y * y + z * z);
            }
        }
        public double X
        {
            get
            {
                return x;
            }
        }
        public double Y
        {
            get
            {
                return y;
            }
        }
        public double Z
        {
            get
            {
                return z;
            }
        }


        public static double operator *(Vector3D v1, Vector3D v2)
        {
            return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
        }
        public static Vector3D operator +(Vector3D v1, Vector3D v2)
        {
            return new Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
        }

        public static Vector3D operator *(double d, Vector3D v)
        {
            return new Vector3D(d * v.x, d * v.y, d * v.z);
        }

        public static Vector3D operator *(Vector3D v, double d)
        {
            return d * v;
        }

    }
}
