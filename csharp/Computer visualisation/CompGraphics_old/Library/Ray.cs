using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{

    public enum RayType
    {
        Primary,
        Reflected,
        Refracted
    }

    public class Ray
    {
        private Point3D origin;
        private Vector3D direction;
        private RayType type = RayType.Primary;

        public Ray(Point3D x, Vector3D v)
        {
            origin = x;
            direction = v;
        }
        public Point3D Origin
        {
            get
            {
                return origin;
            }
        }
        public Vector3D Direction
        {
            get
            {
                return direction;
            }
        }
        public RayType Type
        {
            get
            {
                return type;
            }
            set
            {
                type = value;
            }
        }
    }
}
