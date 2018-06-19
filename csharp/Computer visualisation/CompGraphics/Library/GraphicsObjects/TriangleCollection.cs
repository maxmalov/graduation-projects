using System;
using System.Collections.Generic;

namespace Library {

    public class TriangleCollection : IGraphicsObject3D {
        protected readonly ICollection<Triangle3D> triangles;

        public TriangleCollection(ICollection<Triangle3D> triangles) {
            this.triangles = triangles;
        }

        public IntersectionInfo Intersection(Ray r) {
            double distance = Double.MaxValue;
            IntersectionInfo result = null;

            foreach (Triangle3D triangle in triangles) {
                IntersectionInfo ii = triangle.Intersection(r);
                if (ii != null) {
                    if (distance > (new Vector3D(r.Origin, ii.CrossPoint)).Length) {
                        result = ii;
                    }
                }
            }
            return result;
        }
    }
}
