﻿using System;
using Mono.Cecil;
using Mono.Cecil.Cil;
using Mono.Cecil.Pdb;

namespace DocScanner
{
	class SymbolEngine
	{
		ModuleDefinition m_moduleDef;

		public SymbolEngine(string assemblyPath)
		{
			AssemblyDefinition assemblyDef = AssemblyFactory.GetAssembly(assemblyPath);
			m_moduleDef = assemblyDef.MainModule;
			PdbFactory factory = new PdbFactory();
			ISymbolReader reader = factory.CreateReader(m_moduleDef, assemblyPath);
			m_moduleDef.LoadSymbols(reader);
		}

		string GetFileForMethod(MethodDefinition methodDef)
		{
			SequencePoint sp = methodDef.Body.Instructions[0].SequencePoint;
			return sp.Document.Url;
		}

		string GetFileForType(string typename)
		{
			TypeDefinition typeDef = m_moduleDef.Types[typename];
			return GetFileForMethod(typeDef.Methods[0]);
		}

		string GetFileForMember(string memberName)
		{
			int memberIndex = memberName.LastIndexOf('.');
			string typename = memberName.Substring(0, memberIndex);
			return GetFileForType(typename);
		}

		public string GetFileForSymbol(string symbol)
		{
			string rawName = symbol.Substring(2);
			string prefix = symbol.Substring(0, 2);

			switch(prefix)
			{
				case "T:":
					return GetFileForType(rawName);

				case "M:":
					//break the type out from the full method name
					int parenIndex = rawName.IndexOf('(');
					if(parenIndex == -1)
						parenIndex = rawName.Length;
					int methodIndex = rawName.LastIndexOf('.', parenIndex - 1);
					string typename = rawName.Substring(0, methodIndex);

					return GetFileForType(typename);

				case "P:":
				case "F:":
				case "E:":
					return GetFileForMember(rawName);

				default:
					return null;
			}
		}
	}
}