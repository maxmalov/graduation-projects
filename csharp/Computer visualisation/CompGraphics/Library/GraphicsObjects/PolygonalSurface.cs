using System;
using System.Collections.Generic;

namespace Library {
   
    public class PolygonalSurface : IGraphicsObject3D {
        private Material front, back;
        protected LinkedList<BaseTriangle3D> polygons;

        public PolygonalSurface(Material front, Material back) {
            this.polygons = new LinkedList<BaseTriangle3D>();
            this.front = front;
            this.back = back;
        }

        public IntersectionInfo Intersection(Ray r) {
            double distance = Double.MaxValue;
            IntersectionInfo result = null;

            foreach (BaseTriangle3D polygon in polygons) {
                IntersectionInfo ii = polygon.Intersection(r);
                if (ii != null) {
                    if (distance > (new Vector3D(r.Origin, ii.CrossPoint)).Length) {
                        result = ii;
                    }
                }
            }
            return result;
        }

        public void AddPolygon (Point3D p1, Point3D p2, Point3D p3) {
            polygons.AddLast(new BaseTriangle3D(p1,p2,p3,this));
        }

        public void AddPolygons(LinkedList<BaseTriangle3D> lt) {
            foreach (BaseTriangle3D bt in lt) {
                polygons.AddLast(new BaseTriangle3D(bt.VertexA, bt.VertexB, bt.VertexC, this));
            }
        }

        public Material MaterialFront {
            get {
                return front;
            }
            set {
                front = value;
            }
        }

        public Material MaterialBack {
            get {
                return back;
            }
            set {
                back = value;
            }
        }
    }
}