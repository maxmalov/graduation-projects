using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Library
{
    public class PerspectiveCamera
    {
        private Point3D cameraPosition; //координаты камеры в системе с камерой
        private SizeF windowSize;       //размер окна проектирования
        private double cameraFocus;     //расстояние от камеры до плоскости проектирования
        private Size dim;               //кол-во пикселей по горизонтали и вертикали
        private Rotation rotation;      //преобразование, переводящее мировую сист. коорд в систему с камерой
        
        
        public PerspectiveCamera(Point3D position, Rotation rot, SizeF windowSize, Size dimension, double focus)
        {
            this.cameraPosition = position;
            this.windowSize = windowSize;
            this.cameraFocus = focus;
            this.dim = dimension;
            this.rotation = rot;
        }
        public Point3D CameraPosition
        {
            set
            {
                cameraPosition = value;
            }
            get
            {
                return cameraPosition;
            }
        }
        public SizeF Window
        {
            set
            {
                windowSize = value;
            }
        }
        public double CameraFocus
        {
            get
            {
                return cameraFocus;
            }
            set
            {
                cameraFocus = value;
            }
        }
        public Size Dimention
        {
            set
            {
                dim = value;
            }
            get
            {
                return dim;
            }
        }
        public Rotation Rotation
        {
            set
            {
                rotation = value;
            }
            get
            {
                return rotation;
            }
        }

        public Ray GetRay(int i, int j) //получить луч (i, j) в мировой системе координат
        {
            double Hx = windowSize.Width / dim.Width;
            double Hy = windowSize.Height / dim.Height;

            Point3D Pij = new Point3D(windowSize.Width/2 - (i + 0.5)*Hx, 
                                     -windowSize.Height/2 + (j + 0.5)*Hy, 
                                     cameraPosition.Z - cameraFocus
                                     );
            Vector3D v =  rotation.Transform(new Vector3D(cameraPosition, Pij));
            v *= (1 / v.Length);
            Point3D cameraInWorldCoord = rotation.Transform(cameraPosition);
            return new Ray(cameraInWorldCoord, v);   
        }
    }
}
