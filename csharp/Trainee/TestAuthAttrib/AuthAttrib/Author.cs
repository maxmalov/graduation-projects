using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;

namespace AuthAttrib
{
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = true)]
    public class Author : Attribute
    {
        private string name;

        public Author(string name)
        {
            this.name = name;
        }

        public string Name
        {
            get { return name; }
        }
    }

    [AttributeUsage(AttributeTargets.Assembly)]
    public class AssemblySupport : Attribute
    { }
}

