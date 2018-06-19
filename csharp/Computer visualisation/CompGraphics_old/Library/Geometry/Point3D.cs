using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class Point3D
    {
        double x, y, z;
        public Point3D(double x, double y, double z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
        public override bool Equals(object obj)
        {
            Point3D P = (Point3D)obj;
            return (new Vector3D(this, P)).Length < 0.01;
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
        static public Point3D Zero
        {
            get
            {
                return new Point3D(0, 0, 0);
            }
        }
        public Point3D Round()
        {
            return new Point3D(((int)(X * 10.0)) / 10.0, ((int)(Y * 10.0)) / 10.0, ((int)(Z * 10.0)) / 10.0);
        }
    }
}
