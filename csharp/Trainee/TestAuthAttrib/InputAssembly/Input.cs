using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;

using AuthAttrib;

//тестирующая сборка для проекта TestAuthAttrib
[assembly: AssemblySupport]
namespace InputAssembly
{
    [Author("P. Petrov")]
    class Class1
    { }

    [Author("S. Spiridonov")/*, Author("P. Petrov")*/]
    class Class2
    { }

    class Class3
    { }

    [Author("S. Sidorov"), Author("I. Ivanov")]
    class Class4
    { }
}
