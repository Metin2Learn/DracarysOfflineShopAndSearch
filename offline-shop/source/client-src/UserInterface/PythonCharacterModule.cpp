
# Search

PyObject * chrGetPixelPosition(PyObject* poSelf, PyObject* poArgs)

# Change

PyObject * chrGetPixelPosition(PyObject* poSelf, PyObject* poArgs)
{
	int iVirtualID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVirtualID))
		return Py_BuildException();

	CInstanceBase * pkInst = CPythonCharacterManager::Instance().GetInstancePtr(iVirtualID);

	if (!pkInst)
		//return Py_BuildException();
		return Py_BuildNone();

	TPixelPosition PixelPosition;
	pkInst->NEW_GetPixelPosition(&PixelPosition);

	return Py_BuildValue("fff", PixelPosition.x, PixelPosition.y, PixelPosition.z);
}

# Search

	PyModule_AddIntConstant(poModule, "NEW_AFFECT_AUTO_HP_RECOVERY", CInstanceBase::NEW_AFFECT_AUTO_HP_RECOVERY);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "NEW_AFFECT_DECORATION", CInstanceBase::NEW_AFFECT_DECORATION);
#endif

