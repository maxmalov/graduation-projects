using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library
{
    public interface IGraphicsObject3D
    {
        IntersectionInfo Intersection(Ray r);
    }

}
