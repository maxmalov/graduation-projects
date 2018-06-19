using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Library {

    public class PlaneMap {
        
        private LinkedList<Triangle2D> triangles;
        private int rows, columns;
        private Point2D top_left, bottom_left, top_right, bottom_right;

        public PlaneMap(int rows, int columns) {
            this.rows = rows;
            this.columns = columns;

            this.top_left = new Point2D(-1, 1);
            this.top_right = new Point2D(1, 1);
            this.bottom_left = new Point2D(-1, -1);
            this.bottom_right = new Point2D(1, -1);

            triangles = new LinkedList<Triangle2D>();

            Point2D v1, v2, v3, v4;
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    v1 = new Point2D(bottom_left.X + 2.0 / columns * j, bottom_left.Y + 2.0 / rows * i);
                    v2 = new Point2D(bottom_left.X + 2.0 / columns * (j+1), bottom_left.Y + 2.0 / rows * i);
                    v3 = new Point2D(bottom_left.X + 2.0 / columns * j, bottom_left.Y + 2.0 / rows * (i + 1));
                    v4 = new Point2D(bottom_left.X + 2.0 / columns * (j + 1), bottom_left.Y + 2.0 / rows * (i + 1));
                    
                    triangles.AddLast(new Triangle2D(v1, v2, v3));
                    triangles.AddLast(new Triangle2D(v2, v4, v3));
                }
            }
        }

        public LinkedList<BaseTriangle3D> Stretch(Point3D p1, Point3D p2, Point3D p3, Point3D p4) {
            LinkedList<BaseTriangle3D> res = new LinkedList<BaseTriangle3D>();

            foreach (Triangle2D t in triangles) {
                res.AddLast(new BaseTriangle3D(Interpolation.call(p1, p2, p3, p4, t.V1),
                    Interpolation.call(p1, p2, p3, p4, t.V2),
                    Interpolation.call(p1, p2, p3, p4, t.V3), 
                    null));    
            }            
            return res;
        }
    }
}
