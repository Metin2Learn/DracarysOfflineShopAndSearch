# Search

	{ NULL,							NULL,								NULL		 }

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		{ "SetShopNamesRange",			systemSetShopNamesRange, METH_VARARGS },
		{ "GetShopNamesRange",			systemGetShopNamesRange, METH_VARARGS },
#endif


# Search

void initsystem()


# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
PyObject* systemSetShopNamesRange(PyObject* poSelf, PyObject* poArgs)
{
	float fRange;
	if (!PyTuple_GetFloat(poArgs, 0, &fRange))
		return Py_BuildException();

	CPythonSystem::Instance().SetShopNamesRange(fRange);
	return Py_BuildNone();
}

PyObject* systemGetShopNamesRange(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("f", CPythonSystem::Instance().GetShopNamesRange());
}
#endif
