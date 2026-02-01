# Search

	PyModule_AddIntConstant(poModule, "SHOP_SLOT_COUNT", SHOP_HOST_ITEM_MAX_NUM);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "OFFLINE_SHOP_SLOT_COUNT", OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
#endif

# Search

	{ "GetItemPrice",				shopGetItemPrice,				METH_VARARGS },

# Addd after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		{ "Clear",						shopClear,						METH_VARARGS },
#ifdef WJ_CHANGELOOK_SYSTEM
		{ "GetOfflineShopItemTransmutation", shopGetOfflineShopItemTransmutation, METH_VARARGS },
#endif
		{ "IsOfflineShop", shopIsOfflineShop, METH_VARARGS },
		{ "GetOfflineShopItemID", shopGetOfflineShopItemID, METH_VARARGS },
		{ "GetOfflineShopItemCount", shopGetOfflineShopItemCount, METH_VARARGS },
		{ "GetOfflineShopItemVnum", shopGetOfflineShopItemVnum, METH_VARARGS },
		{ "GetOfflineShopItemPrice", shopGetOfflineShopItemPrice, METH_VARARGS },
		{ "GetOfflineShopItemMetinSocket", shopGetOfflineShopItemMetinSocket, METH_VARARGS },
		{ "GetOfflineShopItemAttribute", shopGetOfflineShopItemAttribute, METH_VARARGS },
		{ "GetSign", shopGetSign, METH_VARARGS },
		{ "ClearOfflineShopStock", shopClearOfflineShopStock, METH_VARARGS },
		{ "AddOfflineShopItemStock", shopAddOfflineShopItemStock, METH_VARARGS },
		{ "DelOfflineShopItemStock", shopDelOfflineShopItemStock, METH_VARARGS },
		{ "GetOfflineShopItemPriceReal", shopGetOfflineShopItemPriceReal, METH_VARARGS },
		{ "GetOfflineShopItemStatus", shopGetOfflineShopItemGetStatus, METH_VARARGS },
		{ "GetOfflineShopItemBuyerName", shopGetOfflineShopItemGetBuyerName, METH_VARARGS },
		{ "BuildOfflineShop", shopBuildOfflineShop, METH_VARARGS },
		{ "GetDisplayedCount", shopGetDisplayedCount, METH_VARARGS },
		{ "GetOfflineShopID", shopGetOfflineShopID, METH_VARARGS },
		{ "GetCurrentOfflineShopMoney", shopGetCurrentOfflineShopMoney, METH_VARARGS },
		{ "HasOfflineShop", shopHasOfflineShop, METH_VARARGS },
		{ "GetRealWatcherCount", shopGetRealWatcherCount, METH_VARARGS },
		{ "ChangeDecoration", shopChangeDecoration, METH_VARARGS },
		{ "GetShopFlag", shopGetShopFlag, METH_VARARGS },
		{ "SetShopFlag", shopSetShopFlag, METH_VARARGS },
		{ "GetShopType", shopGetShopType, METH_VARARGS },
		{ "SetShopType", shopSetShopType, METH_VARARGS },
		{ "GetShopTime", shopGetShopTime, METH_VARARGS },
		{ "SetShopTime", shopSetShopTime, METH_VARARGS },
#endif


# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
void CPythonShop::SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData& c_rShopItemData)
{
	BYTE tabIdx = dwIndex / OFFLINE_SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % OFFLINE_SHOP_HOST_ITEM_MAX_NUM;

	SetOfflineShopItemData(tabIdx, dwSlotPos, c_rShopItemData);
}

void CPythonShop::SetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData& c_rShopItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return;
	}

	m_aOfflineShoptabs[tabIdx].items[dwSlotPos] = c_rShopItemData;
}

BOOL CPythonShop::GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData** c_ppItemData)
{
	BYTE tabIdx = dwIndex / OFFLINE_SHOP_HOST_ITEM_MAX_NUM;
	DWORD dwSlotPos = dwIndex % OFFLINE_SHOP_HOST_ITEM_MAX_NUM;

	return GetOfflineShopItemData(tabIdx, dwSlotPos, c_ppItemData);
}

BOOL CPythonShop::GetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData** c_ppItemData)
{
	if (tabIdx >= SHOP_TAB_COUNT_MAX || dwSlotPos >= OFFLINE_SHOP_HOST_ITEM_MAX_NUM)
	{
		TraceError("Out of Index. tabIdx(%d) must be less than %d. dwSlotPos(%d) must be less than %d", tabIdx, SHOP_TAB_COUNT_MAX, dwSlotPos, OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
		return FALSE;
	}

	if (m_aOfflineShoptabs[tabIdx].items[dwSlotPos].vnum)
	{
		*c_ppItemData = &m_aOfflineShoptabs[tabIdx].items[dwSlotPos];
		return TRUE;
	}

	*c_ppItemData = NULL;
	return FALSE;
}
struct OfflineShopItemStockSortFunc
{
	bool operator() (TOfflineShopItemTable& rkLeft, TOfflineShopItemTable& rkRight)
	{
		return rkLeft.display_pos < rkRight.display_pos;
	}
};
void CPythonShop::AddOfflineShopItemStock(TItemPos ItemPos, BYTE dwDisplayPos, long long dwPrice)
{
	DelOfflineShopItemStock(ItemPos);
	TOfflineShopItemTable SellingItem;
	SellingItem.vnum = 0;
	SellingItem.count = 0;
	SellingItem.pos = ItemPos;
	SellingItem.price = dwPrice;
	SellingItem.display_pos = dwDisplayPos;
	m_OfflineShopItemStock.insert(std::make_pair(ItemPos, SellingItem));
}

void CPythonShop::DelOfflineShopItemStock(TItemPos ItemPos)
{
	if (m_OfflineShopItemStock.end() == m_OfflineShopItemStock.find(ItemPos))
		return;

	m_OfflineShopItemStock.erase(ItemPos);
}

long long CPythonShop::GetOfflineShopItemPrice(TItemPos ItemPos)
{
	auto itor = m_OfflineShopItemStock.find(ItemPos);

	if (m_OfflineShopItemStock.end() == itor)
		return 0;

	TOfflineShopItemTable& rShopItemTable = itor->second;
	return rShopItemTable.price;
}

void CPythonShop::BuildOfflineShop(const char* c_szName, DWORD shopVnum, BYTE shopTitle)
{
	std::vector<TOfflineShopItemTable> ItemStock;
	ItemStock.reserve(m_OfflineShopItemStock.size());

	auto itor = m_OfflineShopItemStock.begin();
	for (; itor != m_OfflineShopItemStock.end(); ++itor)
	{
		ItemStock.push_back(itor->second);
	}

	std::sort(ItemStock.begin(), ItemStock.end(), OfflineShopItemStockSortFunc());

	CPythonNetworkStream::Instance().SendBuildOfflineShopPacket(c_szName, ItemStock, shopVnum, shopTitle);
}

#ifdef WJ_CHANGELOOK_SYSTEM
PyObject* shopGetOfflineShopItemTransmutation(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->transmutation);

	return Py_BuildValue("i", 0);
}
#endif

PyObject* shopIsOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop& rkShop = CPythonShop::Instance();
	return Py_BuildValue("i", rkShop.IsOfflineShop());
}

PyObject* shopGetOfflineShopItemID(PyObject* poSelf, PyObject* poArgs)
{
	int nPos;
	if (!PyTuple_GetInteger(poArgs, 0, &nPos))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(nPos, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemCount(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->count);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemVnum(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->vnum);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemPrice(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return PyLong_FromLongLong(c_pItemData->price);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetSign(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("s", CPythonShop::Instance().GetShopSign());
}

PyObject* shopGetOfflineShopItemMetinSocket(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iMetinSocketIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iMetinSocketIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->alSockets[iMetinSocketIndex]);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemAttribute(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	int iAttrSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &iAttrSlotIndex))
		return Py_BuildException();

	if (iAttrSlotIndex >= 0 && iAttrSlotIndex < ITEM_ATTRIBUTE_SLOT_MAX_NUM)
	{
		const TOfflineShopItemData* c_pItemData;
		if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
			return Py_BuildValue("ii", c_pItemData->aAttr[iAttrSlotIndex].bType, c_pItemData->aAttr[iAttrSlotIndex].sValue);
	}

	return Py_BuildValue("ii", 0, 0);
}

PyObject* shopClear(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop::instance().Clear();
	return Py_BuildNone();
}

PyObject* shopClearOfflineShopStock(PyObject* poSelf, PyObject* poArgs)
{
	CPythonShop::Instance().ClearOfflineShopStock();
	return Py_BuildNone();
}

PyObject* shopAddOfflineShopItemStock(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();
	int iDisplaySlotIndex;
	if (!PyTuple_GetInteger(poArgs, 2, &iDisplaySlotIndex))
		return Py_BuildException();
	long long iPrice;
	if (!PyTuple_GetLongLong(poArgs, 3, &iPrice))
		return Py_BuildException();

	CPythonShop::Instance().AddOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex), iDisplaySlotIndex, iPrice);
	return Py_BuildNone();
}

PyObject* shopDelOfflineShopItemStock(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();

	CPythonShop::Instance().DelOfflineShopItemStock(TItemPos(bItemWindowType, wItemSlotIndex));
	return Py_BuildNone();
}

PyObject* shopGetOfflineShopItemPriceReal(PyObject* poSelf, PyObject* poArgs)
{
	BYTE bItemWindowType;
	if (!PyTuple_GetInteger(poArgs, 0, &bItemWindowType))
		return Py_BuildException();
	WORD wItemSlotIndex;
	if (!PyTuple_GetInteger(poArgs, 1, &wItemSlotIndex))
		return Py_BuildException();
	return PyLong_FromLongLong(CPythonShop::Instance().GetOfflineShopItemPrice(TItemPos(bItemWindowType, wItemSlotIndex)));
}

PyObject* shopGetOfflineShopItemGetStatus(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->status);

	return Py_BuildValue("i", 0);
}

PyObject* shopGetOfflineShopItemGetBuyerName(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();

	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("s", c_pItemData->szBuyerName);

	return Py_BuildValue("s", "None");
}

PyObject* shopBuildOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BuildException();
	int szshopVnum;
	if (!PyTuple_GetInteger(poArgs, 1, &szshopVnum))
		return Py_BuildException();
	int szshopTitle;
	if (!PyTuple_GetInteger(poArgs, 2, &szshopTitle))
		return Py_BuildException();

	CPythonShop::Instance().BuildOfflineShop(szName, (DWORD)szshopVnum, szshopTitle);
	return Py_BuildNone();
}
PyObject* shopGetDisplayedCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopDisplayedCount());
}
PyObject* shopGetOfflineShopID(PyObject* poSelf, PyObject* poArgs)
{
	int iIndex;
	if (!PyTuple_GetInteger(poArgs, 0, &iIndex))
		return Py_BuildException();
	const TOfflineShopItemData* c_pItemData;
	if (CPythonShop::Instance().GetOfflineShopItemData(iIndex, &c_pItemData))
		return Py_BuildValue("i", c_pItemData->owner_id);
	return Py_BuildValue("i", 0);
}
PyObject* shopGetCurrentOfflineShopMoney(PyObject* poSelf, PyObject* poArgs)
{
	return	PyLong_FromLongLong(CPythonShop::instance().GetCurrentOfflineShopMoney());
}
PyObject* shopHasOfflineShop(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().HasOfflineShop());
}

PyObject* shopChangeDecoration(PyObject* poSelf, PyObject* poArgs)
{
	char* sign;
	if (!PyTuple_GetString(poArgs, 0, &sign))
		return Py_BuildException();
	int vnum;
	if (!PyTuple_GetInteger(poArgs, 1, &vnum))
		return Py_BuildException();
	int type;
	if (!PyTuple_GetInteger(poArgs, 2, &type))
		return Py_BuildException();
	CPythonNetworkStream::instance().SendOfflineShopChangeDecoration(sign, vnum, type);
	return Py_BuildNone();
}
PyObject* shopGetRealWatcherCount(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetRealWatcherCount());
}
PyObject* shopGetShopFlag(PyObject* poSelf, PyObject* poArgs)
{
	return PyLong_FromLongLong(CPythonShop::instance().GetShopFlag());
}
PyObject* shopSetShopFlag(PyObject* poSelf, PyObject* poArgs)
{
	long long flag;
	if (!PyTuple_GetLongLong(poArgs, 0, &flag))
		return Py_BuildException();
	CPythonShop::instance().SetShopFlag(flag);
	return Py_BuildNone();
}
PyObject* shopGetShopType(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopType());
}
PyObject* shopSetShopType(PyObject* poSelf, PyObject* poArgs)
{
	int type;
	if (!PyTuple_GetInteger(poArgs, 0, &type))
		return Py_BuildException();
	CPythonShop::instance().SetShopType(type);
	return Py_BuildNone();
}
PyObject* shopGetShopTime(PyObject* poSelf, PyObject* poArgs)
{
	return Py_BuildValue("i", CPythonShop::instance().GetShopTime());
}
PyObject* shopSetShopTime(PyObject* poSelf, PyObject* poArgs)
{
	int type;
	if (!PyTuple_GetInteger(poArgs, 0, &type))
		return Py_BuildException();
	CPythonShop::instance().SetShopTime(type);
	return Py_BuildNone();
}
#endif

# Search

void CPythonShop::Clear()

# Add in

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	ClearOfflineShopStock();
	m_isOfflineShop = FALSE;
	m_bHasOfflineShop = false;
	m_llCurrentOfflineShopMoney = 0;
	m_dwDisplayedCount = 0;
	m_shopFlag = 0;
	time = 0;
	type = 0;
	m_dwRealWatcherCount = 0;
	SetShopSign("NONE");
	for (int i = 0; i < SHOP_TAB_COUNT_MAX; i++)
		memset(m_aOfflineShoptabs[i].items, 0, sizeof(TOfflineShopItemData) * OFFLINE_SHOP_HOST_ITEM_MAX_NUM);
#endif


