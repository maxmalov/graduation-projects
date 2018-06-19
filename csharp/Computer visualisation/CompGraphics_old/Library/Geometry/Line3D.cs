using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class Line3D
    {
        private Point3D pointOnLine;
        private Vector3D direction;

        public Line3D(Point3D P, Vector3D v)
        {
            pointOnLine = P;
            direction = v;
        }
        public Vector3D Direction
        {
            get
            {
                return direction;
            }
        }
        public Point3D Point
        {
            get
            {
                return pointOnLine;
            }
        }
    }
}
