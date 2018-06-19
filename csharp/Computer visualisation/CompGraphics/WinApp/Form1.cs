using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using Library;

namespace WinApp {
    public partial class CompGraphicsForm : Form {
        
        private Size monitorSize;
        private Bitmap bmp;
        private Scene scene;

        public CompGraphicsForm() {
            InitializeComponent();
            
            monitorSize = SystemInformation.PrimaryMonitorSize;
            float coeff = monitorSize.Width / monitorSize.Height;
            bmp = new Bitmap(monitorSize.Width, monitorSize.Height);

            scene = CreateScene();
            ConfigScene(scene);
            scene.DrawScene(bmp);
            this.imageControl.Invalidate();

            this.KeyDown += new KeyEventHandler(CompGraphicsForm_KeyDown);
        }

        private void imageControl_Paint(object sender, PaintEventArgs e) {
            e.Graphics.DrawImage(bmp, this.imageControl.ClientRectangle,
            new Rectangle(0, 0, scene.Camera.Dimention.Width, scene.Camera.Dimention.Height), GraphicsUnit.Pixel);
            bmp.Save("result.bmp");
        }

        private void CompGraphicsForm_SizeChanged(object sender, EventArgs e) {
            this.imageControl.Invalidate();
        }

        private void CompGraphicsForm_KeyDown(object sender, KeyEventArgs e) {
            PerspectiveCamera c = scene.Camera;
            int dif = 100;

            switch(e.KeyCode) {
                case Keys.W:
                    c.MoveForward(dif);
                    break;
                case Keys.S:
                    c.MoveBackward(dif);
                    break;
                case Keys.A:
                    c.MoveLeft(dif);
                    break;
                case Keys.D:
                    c.MoveRight(dif);
                    break;
                case Keys.PageUp:
                    c.MoveUp(dif);
                    break;
                case Keys.PageDown:
                    c.MoveDown(dif);
                    break;    
            }
            scene.DrawScene(bmp);
            this.imageControl.Invalidate();
        }

        private Scene CreateScene() {
            Point3D cameraPosition = new Point3D(0, 0, 1000);
            double cameraFocus = 750;
            SizeF windowSize = new SizeF(200, 200);
            System.Drawing.Size dim = new Size(400, 400);
            Rotation rot = new Rotation(1.2, 0, 1.2);
            PerspectiveCamera camera = new PerspectiveCamera(cameraPosition, rot, windowSize, dim, cameraFocus);
            return new Scene(camera);
        }

        private void ConfigScene(Scene scene) {
            Material m = new Material(Color.Red, 0.5, 0.3, 0.9, 0, 5);
            Material m2 = new Material(Color.Green, 0.5, 0.3, 0.9, 0, 5);

            HyperbolicParaboloid hp = new HyperbolicParaboloid(m, m2, 4.0, 4.0, -50.0, 50.0, -50.0, 50.0, 30, 30); 
            scene.AddGraphicObject(hp);

            Light L1 = new Light(new Point3D(-400, 300, 1000), Color.White);
            scene.AddLight(L1);
        }
    }
}
