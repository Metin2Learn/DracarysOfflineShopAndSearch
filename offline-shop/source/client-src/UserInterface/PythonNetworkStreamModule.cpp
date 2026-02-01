# Search

	{ "RecvGuildSymbol",						netRecvGuildSymbol,							METH_VARARGS },

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		{ "SendOfflineShopEndPacket", netSendOfflineShopEndPacket, METH_VARARGS },
		{ "SendOfflineShopBuyPacket", netSendOfflineShopBuyPacket, METH_VARARGS },
		{ "SendAddOfflineShopItem", netSendAddOfflineShopItem, METH_VARARGS },
		{ "SendRemoveOfflineShopItem", netSendRemoveOfflineShopItem, METH_VARARGS },
		{ "SendDestroyOfflineShop", netSendDestroyOfflineShop, METH_VARARGS },
		{ "SendTakeOfflineMoney", netSendTakeOfflineMoney, METH_VARARGS },
		{ "SendOfflineShopChangeTitle", netSendOfflineShopChangeTitle, METH_VARARGS },
		{ "SendOfflineShopCheck", netSendOfflineShopCheck, METH_VARARGS },
		{ "SendOfflineShopButton", netSendOfflineShopButton, METH_VARARGS },
		{ "SendOfflineShopRemoveLogs", netSendOfflineShopRemoveLogs, METH_VARARGS },
		{ "SendOpenShopSlot", netSendOpenShopSlot, METH_VARARGS },
		{ "SendGetBackItems", netSendGetBackItems, METH_VARARGS },
		{ "SendAddTime", netSendAddTime, METH_VARARGS },
		{ "SendOpenWithVID", netSendOpenWithVID, METH_VARARGS },
#endif


# Addd


#ifdef ENABLE_OFFLINESHOP_SYSTEM
PyObject* netSendOfflineShopEndPacket(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopEndPacket();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopBuyPacket(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();
	int pos;
	if (!PyTuple_GetInteger(poArgs, 1, &pos))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendOfflineShopBuyPacket((DWORD)vid, pos);
	return Py_BuildNone();
}

PyObject* netSendAddOfflineShopItem(PyObject* poSelf, PyObject* poArgs)
{
	int bDisplayPos;
	int bPos;
	long long iPrice;
	BYTE bWindowType;

	if (!PyTuple_GetInteger(poArgs, 0, &bDisplayPos))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 1, &bPos))
		return Py_BuildException();
	if (!PyTuple_GetLongLong(poArgs, 2, &iPrice))
		return Py_BuildException();
	if (!PyTuple_GetInteger(poArgs, 3, &bWindowType))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendAddOfflineShopItem(TItemPos(bWindowType, bDisplayPos), bPos, iPrice);
	return Py_BuildNone();
}

PyObject* netSendRemoveOfflineShopItem(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bPos))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendRemoveOfflineShopItem(bPos);
	return Py_BuildNone();
}

PyObject* netSendDestroyOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendDestroyOfflineShop();
	return Py_BuildNone();
}

PyObject* netSendTakeOfflineMoney(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendTakeOfflineMoney();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopChangeTitle(PyObject* poSelf, PyObject* poArgs)
{
	char* title;
	if (!PyTuple_GetString(poArgs, 0, &title))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopChangeTitle(title);
	return Py_BuildNone();
}

PyObject* netSendOfflineShopCheck(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopCheck();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopButton(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopButton();
	return Py_BuildNone();
}

PyObject* netSendOfflineShopRemoveLogs(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineShopRemoveLogs();
	return Py_BuildNone();
}

PyObject* netSendOpenShopSlot(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bPos;
	if (!PyTuple_GetInteger(poArgs, 0, &bPos))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOpenShopSlot(bPos);
	return Py_BuildNone();
}

PyObject* netSendGetBackItems(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendGetBackItems();
	return Py_BuildNone();
}

PyObject* netSendAddTime(PyObject* poSelf, PyObject* poArgs)
{
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendAddTime();
	return Py_BuildNone();
}

PyObject* netSendOpenWithVID(PyObject* poSelf, PyObject* poArgs)
{
	int vid;
	if (!PyTuple_GetInteger(poArgs, 0, &vid))
		return Py_BuildException();
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::instance();
	rkNetStream.SendOfflineOpenWithVID(vid);
	return Py_BuildNone();
}

#endif

