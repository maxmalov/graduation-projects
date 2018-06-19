using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace Library {

    public class HyperbolicParaboloidInfo {
        private double a, b,
            x_left, x_right,
            y_left, y_right;
        
        public HyperbolicParaboloidInfo(double a, double b, double x_left, double x_right, double y_left, double y_right) {
            this.a = a;
            this.b = b;
            
            this.x_left = x_left;
            this.x_right = x_right;

            this.y_left = y_left;
            this.y_right = y_right;
        }

        public HyperbolicParaboloidInfo(String fName) {
            BinaryReader br = new BinaryReader(new FileStream(fName,FileMode.Open));
            this.a = br.ReadDouble();
            this.b = br.ReadDouble();

            this.x_left = br.ReadDouble();
            this.x_right = br.ReadDouble();

            this.y_left = br.ReadDouble();
            this.y_right = br.ReadDouble();

            br.Close();
        }

        public double A {
            get {
                return a;
            }
        }

        public double B {
            get {
                return b;
            }
        }

        public double LeftX {
            get {
                return x_left;
            }
        }
        public double RightX {
            get {
                return x_right;
            }
        }

        public double LeftY {
            get {
                return y_left;
            }
        }
        public double RightY {
            get {
                return y_right;
            }
        }
    }
    
    public class HyperbolicParaboloid : PolygonalSurface {
        private HyperbolicParaboloidInfo hpi;
        private static int ROWS = 1, COLUMNS = 1;
        private int nx, ny;
        
        private Point3D[,] GetPartition() {
            Point3D[,] res = new Point3D [nx, ny];
            double xh = (hpi.RightX - hpi.LeftX) / (nx - 1),
                yh = (hpi.RightY - hpi.LeftY) / (ny - 1);
            double x,y,z;
            for (int i = 0; i < nx; ++i) {
                for (int j = 0; j < ny; ++j) {
                    x = hpi.LeftX + j * xh;
                    y = hpi.LeftY + i * yh;
                    z = (Math.Pow(x, 2) / Math.Pow(hpi.A, 2) - Math.Pow(y, 2) / Math.Pow(hpi.B, 2)) / 2; 
                    res[i, j] = new Point3D(x, y, z);
                }
            }
            return res;
        }

        private void Triangulation(PlaneMap pm) {
            Point3D[,] dots = GetPartition();
            for (int i = 0; i < nx - 1; ++i) {
                for (int j = 0; j < ny - 1; ++j) {
                    this.AddPolygons(pm.Stretch(dots[i + 1,j + 1],
                                                dots[i + 1, j],
                                                dots[i,j],
                                                dots[i, j + 1]));
                }
            }
        }

        public HyperbolicParaboloid(Material mf, Material mb, String fName, int nx, int ny) : base(mf,mb) {
            hpi = new HyperbolicParaboloidInfo(fName);
            this.nx = nx; 
            this.ny = ny;
            PlaneMap pm = new PlaneMap(ROWS, COLUMNS);
            Triangulation(pm);
        }

        public HyperbolicParaboloid(Material mf, Material mb, double a, double b, double x_left, double x_right, double y_left, double y_right, int nx, int ny)
            : base(mf, mb) {
            hpi = new HyperbolicParaboloidInfo(a, b, x_left, x_right, y_left, y_right);
            this.nx = nx;
            this.ny = ny;
            PlaneMap pm = new PlaneMap(ROWS, COLUMNS);
            Triangulation(pm);
        }
    }
}
