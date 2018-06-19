using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Library;

namespace WinApp
{
    public partial class CompGraphicsForm : Form
    {
        private Size monitorSize;
        private Bitmap bmp;
        private Scene scene;

        public CompGraphicsForm()
        {
            InitializeComponent();

            monitorSize = SystemInformation.PrimaryMonitorSize;
            float coeff = monitorSize.Width / monitorSize.Height;
            bmp = new Bitmap(monitorSize.Width, monitorSize.Height);

            scene = CreateScene2();
            scene.DrawScene(bmp);
            this.imageControl.Invalidate();
        }

        private Scene CreateScene2()
        {
            Point3D cameraPosition = new Point3D(0, 0, 1000);
            double cameraFocus = 750;
            SizeF windowSize = new SizeF(120, 120);
            System.Drawing.Size dim = new Size(500, 500);
            Rotation rot = new Rotation(1, 0, -1);
            PerspectiveCamera camera = new PerspectiveCamera(cameraPosition, rot, windowSize, dim, cameraFocus);

            Scene scene = new Scene(camera);

            Material m = new Material(Color.Red, 0.5, 0.3, 0, 0, 5);
            Material m2 = new Material(Color.FromArgb(100, 200, 100), 0.5, 0.3, 0, 0, 5);

            double x = 50; 
            Point3D p1 = new Point3D(x, x, 0);
            Point3D p2 = new Point3D(x, -x, 0);
            Point3D p3 = new Point3D(-x, -x, 0);
            Point3D p4 = new Point3D(-x, x, 0);
            Point3D p5 = new Point3D(0, 0, 1.3*x);

            LinkedList<Triangle3D> t = new LinkedList<Triangle3D>();
            t.AddLast(new Triangle3D(p1, p2, p3, m));
            t.AddLast(new Triangle3D(p1, p3, p4, m));
            t.AddLast(new Triangle3D(p2, p1, p5, m));
            t.AddLast(new Triangle3D(p3, p2, p5, m));
            t.AddLast(new Triangle3D(p1, p4, p5, m));
            t.AddLast(new Triangle3D(p4, p3, p5, m));

            TriangleCollection triangles = new TriangleCollection(t);
            scene.AddGraphicObject(triangles);

            Sphere s = new Sphere(new Point3D(-70, 0, 0), 20, m2);
            scene.AddGraphicObject(s);

            Light L1 = new Light(new Point3D(100, 100, 500), Color.White);
            Light L2 = new Light(new Point3D(-100, -100, 500), Color.Azure);
            scene.AddLight(L1);

            return scene;
        }

        private void imageControl_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawImage(bmp, this.imageControl.ClientRectangle,
            new Rectangle(0, 0, scene.Camera.Dimention.Width, scene.Camera.Dimention.Height), GraphicsUnit.Pixel);

        }

        private void CompGraphicsForm_SizeChanged(object sender, EventArgs e)
        {
            this.imageControl.Invalidate();
        }

    }
}
