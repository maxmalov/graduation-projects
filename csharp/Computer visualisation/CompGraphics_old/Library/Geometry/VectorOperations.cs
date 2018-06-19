using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class VectorOperations
    {
        static public double ScalarProduct(Vector3D a, Vector3D b)
        {
            return (a.X * b.X + a.Y * b.Y + a.Z * b.Z);
        }
        static public Vector3D VectorProduct(Vector3D a, Vector3D b)
        {
            return new Vector3D(a.Y*b.Z - a.Z*b.Y,
                                a.Z*b.X - a.X*b.Z,
                                a.X*b.Y - a.Y*b.X);
        }
        static public double Distance(Point3D a, Point3D b)
        {
            return (new Vector3D(a, b)).Length;
        }
        static public double Distance(Plane plane, Point3D M)
        {
            return Math.Abs(ScalarProduct(plane.Normal, new Vector3D(M)) -
                            ScalarProduct(plane.Normal, new Vector3D(plane.Point))) / plane.Normal.Length;
        }
        static public double Distance(Line3D L, Point3D M)
        {
            return VectorProduct(new Vector3D(L.Point, M), L.Direction).Length / L.Direction.Length;
        }
        static public double Cos(Vector3D V1, Vector3D V2)  //косинус угла между векторами
        {
            double cos =  ScalarProduct(V1, V2) / (V1.Length * V2.Length);
            if (Math.Abs(cos) <= 0.01)
                return 0.0;
            else
                return cos;
        }

        //not implemented
        static public bool ReflectedVector(Vector3D N, Vector3D V, out Vector3D reflectedVector)
        {
            reflectedVector = null;
            return false;

        }
        static public bool RefractedVector(Vector3D N, Vector3D V, double n12, out Vector3D refractedVector)
        {
            refractedVector = null;
            return false;
        }
    }
}
