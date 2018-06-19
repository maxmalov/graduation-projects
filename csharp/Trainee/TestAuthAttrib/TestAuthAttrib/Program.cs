using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.IO;
using System.Threading;

using AuthAttrib;

namespace TestAuthAttrib
{
	interface IDict
	{
		void ShowOut ();
	}

	//Класс ассоциативного массива загружаемой сборки.
	//Ключи - имена авторов. Каждому ключу соответствует список классов, написанных автором.
	public class aDictionary : IDisposable, IDict
	{
		private Dictionary<string, LinkedList<Type>> Value;

		public void AddAuthorClass (Author a, Type t)
		{
			if (a.Name.Length > 0) {
				if (!Value.ContainsKey (a.Name)) {
					LinkedList<Type> L1 = new LinkedList<Type> ();
					Value.Add (a.Name, L1);
				}
				Value[a.Name].AddLast (t);
			}
		}
		private void AddTypeAttrs (Type t)
		{
			Attribute[] attrs;
			attrs = Attribute.GetCustomAttributes (t);
			foreach (Attribute attr in attrs) {
				if (attr is Author) {
					Author a = (Author)attr;
					AddAuthorClass (a, t);
				}
			}
		}
		private void Print ()
		{
			foreach (string str in this.Value.Keys) {
				Console.Write ("Author : {0}\n", str);
				
				for (int i = 0; i < this.Value[str].Count; ++i) {
					Console.Write ("   {0}\n", Value[str].ElementAt (i).FullName);
				}
			}
		}

		public void Dispose ()
		{
			GC.SuppressFinalize (this);
		}

		//Path - полный путь к библиотеке, содержащей тестируещую сборку
		public aDictionary (string Path)
		{
			Assembly aLoad = Assembly.LoadFrom (Path);
			Type[] tt = aLoad.GetTypes ();
			Value = new Dictionary<string, LinkedList<Type>> ();
			
			foreach (Type t in tt) {
				AddTypeAttrs (t);
			}
		}

		~aDictionary ()
		{
			Dispose ();
		}

		void IDict.ShowOut ()
		{
			new Thread (this.Print).Start ();
		}

		static void Main (string[] args)
		{
			try {
				string Path = args[0];
				for (int j = 1; j < args.Length; ++j) {
					Path += args[j];
				}
				if (Path.Length < 1) {
					throw new FileNotFoundException ();
				}
				aDictionary aDickt = new aDictionary (Path);
				IDict i = (IDict)aDickt;
				i.ShowOut ();
				
			} catch (FileNotFoundException) {
				Console.WriteLine ("File with input assembly not found!");
			}
		}
	}
}
