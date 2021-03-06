using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Threading;

namespace Library {
    public class Scene {
        private readonly List<IGraphicsObject3D> graphicObjects = new List<IGraphicsObject3D>();
        private readonly List<Light> lights = new List<Light>();
        private PerspectiveCamera camera;
        private Color defaultColor = Color.LightYellow;
        private double Ka = 0.2;    //фоновая составляющая
        //private double K = 100;     //
        //private double coeff = 1.2; // на сколько уменьшается интенсивность при прохождении лучом каждых 100 единиц
        private object bmpSync = new object();
        private int threadCount = 2;

        private int completedLines = 0;

        public Scene(PerspectiveCamera camera) {
            this.camera = camera;
        }
        public int ThreadCount {
            get {
                return threadCount;
            }
            set {
                threadCount = value;
            }
        }
        public Color InfinityColor {
            set {
                defaultColor = value;
            }
        }
        public PerspectiveCamera Camera {
            get {
                return camera;
            }
        }
        public double Ambient {
            get {
                return Ka;
            }
            set {
                if (value > 0 && value < 1)
                    Ka = value;
                else
                    Ka = 0.2;
            }
        }
        public void AddGraphicObject(IGraphicsObject3D obj) {
            graphicObjects.Add(obj);
        }
        public void AddLight(Light L) {
            lights.Add(L);
        }
        public double Progress {
            get {
                return ((double)completedLines) / camera.Dimention.Width;
            }
        }
        public void ThreadFunction(object obj) {
            DrawingInfo info = (DrawingInfo)obj;
            Color clr;

            for (int i = info.line1; i < info.line2; i++) {
                for (int j = 0; j < camera.Dimention.Height; j++) {
                    clr = RayTracing(camera.GetRay(i, j), 0);
                    lock (bmpSync) {
                        info.bmp.SetPixel(i, j, clr);
                    }
                }
                Interlocked.Increment(ref completedLines);
            }
        }
        public void DrawScene(Bitmap bmp) {
            if (bmp.Width < camera.Dimention.Width || bmp.Height < camera.Dimention.Height)
                camera.Dimention = bmp.Size;

            Size dim = camera.Dimention;

            Thread[] threads = new Thread[threadCount];

            int linesCount = dim.Width / threadCount;
            completedLines = 0;
            for (int i = 0; i < threadCount; i++) {
                threads[i] = new Thread(this.ThreadFunction);
                DrawingInfo info = new DrawingInfo(i * linesCount, (i + 1) * linesCount, bmp);
                threads[i].Start(info);
            }
            for (int i = 0; i < threadCount; i++) {
                threads[i].Join();
            }
            completedLines = camera.Dimention.Width;
        }

        internal Color RayTracing(Ray r, int depth) {
            if (depth > 5)
                return Color.Black;

            IntersectionInfo info = GetFirstIntersection(r);
            if (info == null)   //луч не пересекает предмет
                return defaultColor;

            double R = 0, G = 0, B = 0;
            //луч пересекает предмет

            double IdR = 0, IdG = 0, IdB = 0;
            double IsR = 0, IsG = 0, IsB = 0;
            double pFong = info.Material.FongCoeff;   //

            foreach (Light L in lights) {
                Vector3D V = new Vector3D(info.CrossPoint, L.Position); //направление на источник L
                V *= (1 / V.Length);

                if (this.IsVisible(L, info.CrossPoint)) {
                    double distance = VectorOperations.Distance(L.Position, info.CrossPoint);
                    double attenuation = L.Attenuation(distance);

                    if (info.Material.Diffusion > 0)    //для предмета задано свойство диффузного отражения 
                    {
                        double cos = VectorOperations.Cos(info.Normal, V);
                        if (cos < 0)
                            cos = 0;

                        IdR += L.Color.R * cos / attenuation;
                        IdG += L.Color.G * cos / attenuation;
                        IdB += L.Color.B * cos / attenuation;
                    }
                    if (info.Material.Specularity > 0)  //для предмета задано свойство зеркального отражения 
                    {
                        Vector3D reflected;
                        if (VectorOperations.ReflectedVector(info.Normal, r.Direction, out reflected)) {
                            double cos = VectorOperations.Cos(V, reflected);
                            if (cos < 0)
                                cos = 0;

                            IsR += L.Color.R * Math.Pow(cos, pFong) / attenuation;
                            IsG += L.Color.G * Math.Pow(cos, pFong) / attenuation;
                            IsB += L.Color.B * Math.Pow(cos, pFong) / attenuation;
                        }
                    }
                }
            }
            R += info.Material.Diffusion * IdR * info.Material.Color.R / 255;
            G += info.Material.Diffusion * IdG * info.Material.Color.G / 255;
            B += info.Material.Diffusion * IdB * info.Material.Color.B / 255;

            R += info.Material.Specularity * IsR;
            G += info.Material.Specularity * IsG;
            B += info.Material.Specularity * IsB;

            if (info.Material.Reflection > 0) {
                Vector3D reflected;
                if (VectorOperations.ReflectedVector(info.Normal, r.Direction, out reflected)) {
                    Ray reflectedRay = new Ray(info.CrossPoint, reflected);
                    Color reflectedColor = this.RayTracing(reflectedRay, depth + 1);

                    R += info.Material.Reflection * reflectedColor.R;
                    G += info.Material.Reflection * reflectedColor.G;
                    B += info.Material.Reflection * reflectedColor.B;
                }
            }
            if (info.Material.Transparency > 0) {
                double n12 = info.Material.RefractiveIndex;
                Vector3D refracted;

                if (VectorOperations.RefractedVector(info.Normal, r.Direction, n12, out refracted)) {
                    Ray refractedRay = new Ray(info.CrossPoint, refracted);
                    Color refractedColor = this.RayTracing(refractedRay, depth + 1);

                    R += info.Material.Transparency * refractedColor.R;
                    G += info.Material.Transparency * refractedColor.G;
                    B += info.Material.Transparency * refractedColor.B;
                }
            }

            R += info.Material.Color.R * Ka;
            G += info.Material.Color.G * Ka;
            B += info.Material.Color.B * Ka;
            return Color.FromArgb(Math.Min((int)R, 255), Math.Min((int)G, 255), Math.Min((int)B, 255));
        }

        internal IntersectionInfo GetFirstIntersection(Ray r) {
            IntersectionInfo res = null;
            double distance = Double.MaxValue;
            foreach (IGraphicsObject3D obj in graphicObjects) {
                IntersectionInfo info = obj.Intersection(r);
                if (info != null)
                    if (VectorOperations.Distance(info.CrossPoint, r.Origin) < distance) {
                        distance = VectorOperations.Distance(info.CrossPoint, r.Origin);
                        res = info;
                    }
            }
            return res;
        }
        internal bool IsVisible(Light L, Point3D P) {//видим ли источник света из данной точки
            Vector3D v = new Vector3D(P, L.Position);
            //для упрощения: если источник закрыт прозрачным предметом, то считаем, что он в тени
            IntersectionInfo info = this.GetFirstIntersection(new Ray(P, v));
            if (info == null)
                return true;
            else
                return (VectorOperations.Distance(P, L.Position) < VectorOperations.Distance(P, info.CrossPoint));
        }
    }


    internal class DrawingInfo {
        public int line1;
        public int line2;
        public Bitmap bmp;

        public DrawingInfo(int l1, int l2, Bitmap bmp) {
            line1 = l1;
            line2 = l2;
            this.bmp = bmp;
        }
    }
}
