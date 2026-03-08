# Search


	{ NULL,								NULL,									NULL		 },

# Add before


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		{"GetItemsByName", itemGetItemsByName, METH_VARARGS},
#endif

# Search


void initItem()

# Add before


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
PyObject* itemGetItemsByName(PyObject* poSelf, PyObject* poArgs)
{
	char* szItemName;
	if (!PyTuple_GetString(poArgs, 0, &szItemName))
		return Py_BadArgument();
	std::map<DWORD, CItemData*> m_vec_ItemRange = CItemManager::Instance().GetItemsVector();
	int n = m_vec_ItemRange.size();
	std::string searchedFileName(szItemName);
	PyObject* poList = PyList_New(0);

	std::map<DWORD, CItemData*>::iterator i;
	for (i = m_vec_ItemRange.begin(); i != m_vec_ItemRange.end(); ++i)
	{
		CItemData* p = i->second;
		const CItemData::TItemTable* pTable = p->GetTable();
		if (pTable)
		{
			std::string tempFileName(pTable->szLocaleName);
			std::transform(tempFileName.begin(), tempFileName.end(), tempFileName.begin(),[](unsigned char c) { return std::tolower(c); });
			if (tempFileName.compare(0, searchedFileName.length(), searchedFileName) == 0)
			{
				PyObject* poItemVnum = PyInt_FromLong(pTable->dwVnum);
				PyList_Append(poList, poItemVnum);
			}
		}
	}
	return poList;
}
#endif