using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class Plane
    {
        private Point3D pointOnPlane;
        private Vector3D normal;

        public Plane(Point3D P, Vector3D normal)
        {
            pointOnPlane = P;
            this.normal = normal;
        }
        public Vector3D Normal
        {
            get
            {
                return normal;
            }
        }
        public Point3D Point
        {
            get
            {
                return pointOnPlane;
            }
        }
    }
}
