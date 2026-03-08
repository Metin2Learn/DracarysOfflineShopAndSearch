# Search

	{ "RecvGuildSymbol",						netRecvGuildSymbol,							METH_VARARGS },

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		{ "SendPrivateShopSearchInfo", netSendPrivateShopSearchInfo, METH_VARARGS },
#endif


# Addd

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
PyObject* netSendPrivateShopSearchInfo(PyObject* poSelf, PyObject* poArgs)
{
	int ItemCat;
	if (!PyTuple_GetInteger(poArgs, 0, &ItemCat))
		return Py_BuildException();
	int SubCat;
	if (!PyTuple_GetInteger(poArgs, 1, &SubCat))
		return Py_BuildException();
	int minAvg;
	if (!PyTuple_GetInteger(poArgs, 2, &minAvg))
		return Py_BuildException();
	int maxAvg;
	if (!PyTuple_GetInteger(poArgs, 3, &maxAvg))
		return Py_BuildException();
	int minSkill;
	if (!PyTuple_GetInteger(poArgs, 4, &minSkill))
		return Py_BuildException();
	int maxSkill;
	if (!PyTuple_GetInteger(poArgs, 5, &maxSkill))
		return Py_BuildException();
	int minAbs;
	if (!PyTuple_GetInteger(poArgs, 6, &minAbs))
		return Py_BuildException();
	int maxAbs;
	if (!PyTuple_GetInteger(poArgs, 7, &maxAbs))
		return Py_BuildException();
	int minLevel;
	if (!PyTuple_GetInteger(poArgs, 8, &minLevel))
		return Py_BuildException();
	int maxLevel;
	if (!PyTuple_GetInteger(poArgs, 9, &maxLevel))
		return Py_BuildException();
	int minRefine;
	if (!PyTuple_GetInteger(poArgs, 10, &minRefine))
		return Py_BuildException();
	int maxRefine;
	if (!PyTuple_GetInteger(poArgs, 11, &maxRefine))
		return Py_BuildException();
	int enchant;
	if (!PyTuple_GetInteger(poArgs, 12, &enchant))
		return Py_BuildException();
	int alchemy;
	if (!PyTuple_GetInteger(poArgs, 13, &alchemy))
		return Py_BuildException();
	int sex;
	if (!PyTuple_GetInteger(poArgs, 14, &sex))
		return Py_BuildException();
	int character;
	if (!PyTuple_GetInteger(poArgs, 15, &character))
		return Py_BuildException();
	int value;
	if (!PyTuple_GetInteger(poArgs, 16, &value))
		return Py_BuildException();
	int itemvnum;
	if (!PyTuple_GetInteger(poArgs, 17, &itemvnum))
		return Py_BuildException();

	TPacketCGShopSearch p;
	p.header = HEADER_CG_SHOP_SEARCH;
	p.ItemCat = ItemCat;
	p.SubCat = SubCat;
	p.avg[0] = minAvg;
	p.avg[1] = maxAvg;
	p.skill[0] = minSkill;
	p.skill[1] = maxSkill;
	p.abs[0] = minAbs;
	p.abs[1] = maxAbs;
	p.level[0] = minLevel;
	p.level[1] = maxLevel;
	p.refine[0] = minRefine;
	p.refine[1] = maxRefine;
	p.enchant = enchant;
	p.alchemy = alchemy;
	p.sex = sex;
	p.character = character;
	p.Value = value;
	p.itemVnum = itemvnum;
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendPrivateShopSearchInfo(&p);
	return Py_BuildNone();
}
#endif
