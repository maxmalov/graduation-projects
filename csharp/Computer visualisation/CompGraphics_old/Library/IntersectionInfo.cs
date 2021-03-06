using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public class IntersectionInfo
    {
        private Point3D crossPoint; //точка пересечения
        private Vector3D N; //внешняя нормаль в точке пересечения
        private Material material;  //
        public IntersectionInfo(Point3D x, Vector3D N, Material material)
        {
            crossPoint = x;
            this.N = N;
            this.material = material;
        }
        public Point3D CrossPoint
        {
            get
            {
                return crossPoint;
            }
        }
        public Vector3D Normal
        {
            get
            {
                return N;
            }
        }
        public Material Material
        {
            get
            {
                return material;
            }
        }
    }
}
