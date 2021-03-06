using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;


namespace Library
{
    public class Light
    {
        private Point3D S;  //коорд. в мировой системе координат
        private Color color;
        private double attenuation = 0;

        public Light(Point3D position, Color color)
        {
            this.S = position;
            this.color = color;
        }
        public Point3D Position
        {
            get
            {
                return S;
            }
        }
        public Color Color
        {
            get
            {
                return color;
            }
        }
        public double Attenuation(double distance)
        {
            return attenuation * distance + 1;
        }
        public double AttenuationCoeff
        {
            get
            {
                return attenuation;
            }
            set
            {
                attenuation = value;
            }
        }
    }
}
