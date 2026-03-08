# Add

bool PyTuple_GetImageInstanceEx(PyObject* poArgs, int pos, CGraphicImageInstance** ppRetImageInstance)
{
	int handle;

	if (!PyTuple_GetInteger(poArgs, pos, &handle))
		return false;

	if (!handle)
		return false;

	*ppRetImageInstance = (CGraphicImageInstance*)handle;
	return true;
}

PyObject* wndImageLoadImageInstance(PyObject* poSelf, PyObject* poArgs)
{
	UI::CWindow* pWindow;
	if (!PyTuple_GetWindow(poArgs, 0, &pWindow))
		return Py_BuildException();
	CGraphicImageInstance* pImageInstance;
	if (!PyTuple_GetImageInstanceEx(poArgs, 1, &pImageInstance))
		return Py_BadArgument();
	if (!((UI::CImageBox*)pWindow)->LoadImage(pImageInstance))
		return Py_BuildNone();
	return Py_BuildNone();
}


# Search

	{ "LoadImage",					wndImageLoadImage,					METH_VARARGS },

# Add after

	{ "LoadImageInstance",			wndImageLoadImageInstance,					METH_VARARGS },
