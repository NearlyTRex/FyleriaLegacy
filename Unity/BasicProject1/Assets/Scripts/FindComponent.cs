using System;
using System.Collections.Generic;
using UnityEngine;

namespace UnityEngine
{
	public static class FindComponent
	{
		public static T GetChildComponentByTag<T>(this GameObject obj, string tag) where T : Component
		{
			foreach (T child in obj.GetComponentsInChildren<T>())
			{
				if (child.CompareTag(tag))
				{
					return child;
				}
			}
			return null;
		}

		public static T GetChildComponentByName<T>(this GameObject obj, string name) where T : Component
		{
			foreach (T child in obj.GetComponentsInChildren<T>())
			{
				if (child.name == name)
				{
					return child;
				}
			}
			return null;
		}
	}
}
