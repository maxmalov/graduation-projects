using System;

namespace Library {
    public interface IGraphicsObject3D {
        IntersectionInfo Intersection(Ray r);
    }

}
