# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
bool CPythonNetworkStream::SendBuildOfflineShopPacket(const char* c_szName, const std::vector<TOfflineShopItemTable>& c_rSellingItemStock, DWORD shopVnum, BYTE shopTitle)
{
	TPacketCGMyOfflineShop packet;
	packet.bHeader = HEADER_CG_MY_OFFLINE_SHOP;
	strncpy(packet.szSign, c_szName, SHOP_SIGN_MAX_LEN);
	packet.bCount = c_rSellingItemStock.size();
	packet.shopVnum = shopVnum;
	packet.shopTitle = shopTitle;
	if (!Send(sizeof(packet), &packet))
		return false;

	for (std::vector<TOfflineShopItemTable>::const_iterator itor = c_rSellingItemStock.begin(); itor < c_rSellingItemStock.end(); ++itor)
	{
		const TOfflineShopItemTable& c_rItem = *itor;
		if (!Send(sizeof(c_rItem), &c_rItem))
			return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::RecvOfflineShopSignPacket()
{
	TPacketGCShopSign p;
	if (!Recv(sizeof(TPacketGCShopSign), &p))
		return false;
	CInstanceBase* pInstance = CPythonCharacterManager::instance().GetInstancePtr(p.dwVID);
	if (pInstance)
	{
		if (pInstance->IsShop())
		{
			if (0 == strlen(p.szSign))
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Disappear", Py_BuildValue("(i)", p.dwVID));
			else
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_OfflineShop_Appear", Py_BuildValue("(is)", p.dwVID, p.szSign));
		}
	}
	return true;
}

bool CPythonNetworkStream::RecvOfflineShopPacket()
{
	TPacketGCShop  packet_shop;
	if (!Recv(sizeof(packet_shop), &packet_shop))
		return false;
	std::vector<char> vecBuffer;
	vecBuffer.clear();
	int iSize = packet_shop.size - sizeof(packet_shop);

	switch (packet_shop.subheader)
	{
	case SHOP_SUBHEADER_GC_REFRESH_MONEY:
	case SHOP_SUBHEADER_GC_REFRESH_DISPLAY_COUNT:
	case SHOP_SUBHEADER_GC_CHECK_RESULT:
	case SHOP_SUBHEADER_GC_REFRESH_COUNT:
	case SHOP_SUBHEADER_GC_REALWATCHER_COUNT:
	case SHOP_SUBHEADER_GC_CHANGE_TITLE:
		break;
	default:
		if (iSize > 0)
		{
			vecBuffer.resize(iSize);
			if (!Recv(iSize, &vecBuffer[0]))
				return false;
		}
	}

	switch (packet_shop.subheader)
	{
	case SHOP_SUBHEADER_GC_START:
	{
		CPythonShop::Instance().Clear();
		TPacketGCOfflineShopStart* pShopStartPacket = (TPacketGCOfflineShopStart*)vecBuffer.data();
		for (BYTE iItemIndex = 0; iItemIndex < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++iItemIndex)
			CPythonShop::Instance().SetOfflineShopItemData(iItemIndex, pShopStartPacket->items[iItemIndex]);
		CPythonShop::Instance().SetShopDisplayedCount(pShopStartPacket->m_dwDisplayedCount);
		CPythonShop::Instance().SetRealWatcherCount(pShopStartPacket->m_dwRealWatcherCount);
		CPythonShop::Instance().SetCurrentOfflineShopMoney(pShopStartPacket->price);
		CPythonShop::Instance().SetShopSign(pShopStartPacket->title);
		CPythonShop::Instance().SetShopFlag(pShopStartPacket->flag);
		CPythonShop::Instance().SetShopType(pShopStartPacket->type);
		CPythonShop::Instance().SetShopTime(pShopStartPacket->time);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ClearOfflineShopLog", Py_BuildValue("()"));
		for (int logIndex = OFFLINE_SHOP_HOST_ITEM_MAX_NUM-1; logIndex >= 0; --logIndex)
			if (pShopStartPacket->log[logIndex].price != 0) {
				PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AppendShopLog", Py_BuildValue("(ssiiL)", pShopStartPacket->log[logIndex].name, pShopStartPacket->log[logIndex].date, pShopStartPacket->log[logIndex].itemVnum, pShopStartPacket->log[logIndex].itemCount, pShopStartPacket->log[logIndex].price));
			}

		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "StartOfflineShop", Py_BuildValue("(ii)", pShopStartPacket->owner_vid, pShopStartPacket->IsOwner == true ? 1 : 0));
	}
	break;

	case SHOP_SUBHEADER_GC_END:
	{
		CPythonShop::instance().Clear();
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "ClearOfflineShopLog", Py_BuildValue("()"));
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "EndOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_UPDATE_ITEM:
	{
		TPacketGCOfflineShopUpdateItem* pShopUpdateItemPacket = (TPacketGCOfflineShopUpdateItem*)vecBuffer.data();
		CPythonShop::Instance().SetShopDisplayedCount(pShopUpdateItemPacket->m_dwDisplayedCount);
		CPythonShop::Instance().SetRealWatcherCount(pShopUpdateItemPacket->m_dwRealWatcherCount);
		CPythonShop::Instance().SetShopFlag(pShopUpdateItemPacket->flag);
		CPythonShop::Instance().SetShopTime(pShopUpdateItemPacket->time);
		CPythonShop::Instance().SetShopSign(pShopUpdateItemPacket->title);
		CPythonShop::Instance().SetShopType(pShopUpdateItemPacket->type);
		CPythonShop::Instance().SetOfflineShopItemData(pShopUpdateItemPacket->pos, pShopUpdateItemPacket->item);
		CPythonShop::Instance().SetCurrentOfflineShopMoney(pShopUpdateItemPacket->price);
		if (pShopUpdateItemPacket->log.price != 0) {
			PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AppendShopLogFirst", Py_BuildValue("(ssiiL)", pShopUpdateItemPacket->log.name, pShopUpdateItemPacket->log.date, pShopUpdateItemPacket->log.itemVnum, pShopUpdateItemPacket->log.itemCount, pShopUpdateItemPacket->log.price));
		}
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_NOT_ENOUGH_MONEY:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "NOT_ENOUGH_MONEY"));
		break;

	case SHOP_SUBHEADER_GC_SOLD_OUT:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "SOLDOUT"));
		break;

	case SHOP_SUBHEADER_GC_OK:
		//PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "SOLDOUT"));
		break;

	case SHOP_SUBHEADER_GC_INVENTORY_FULL:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVENTORY_FULL"));
		break;

	case SHOP_SUBHEADER_GC_INVALID_POS:
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "OnShopError", Py_BuildValue("(s)", "INVALID_POS"));
		break;

	case SHOP_SUBHEADER_GC_REFRESH_MONEY:
	{
		long long llMoney = 0;
		if (!Recv(sizeof(long long), &llMoney))
			return false;
		CPythonShop::Instance().SetCurrentOfflineShopMoney(llMoney);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_CHECK_RESULT:
	{
		BYTE bHasOfflineShop = 0;
		if (!Recv(sizeof(BYTE), &bHasOfflineShop))
			return false;
		CPythonShop::instance().SetHasOfflineShop(bHasOfflineShop == 1 ? true : false);
	}
	break;

	case SHOP_SUBHEADER_GC_REFRESH_DISPLAY_COUNT:
	{
		DWORD displayCount = 0;
		if (!Recv(sizeof(DWORD), &displayCount))
			return false;
		CPythonShop::Instance().SetShopDisplayedCount(displayCount);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;
	case SHOP_SUBHEADER_GC_REALWATCHER_COUNT:
	{
		DWORD realWatcher = 0;
		if (!Recv(sizeof(DWORD), &realWatcher))
			return false;
		CPythonShop::Instance().SetRealWatcherCount(realWatcher);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_REFRESH_COUNT:
	{
		DWORD count[2] = { 0,0 };
		if (!Recv(sizeof(count), &count))
			return false;
		CPythonShop::Instance().SetShopDisplayedCount(count[0]);
		CPythonShop::Instance().SetRealWatcherCount(count[1]);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	case SHOP_SUBHEADER_GC_CHANGE_TITLE:
	{
		char sign[SHOP_SIGN_MAX_LEN + 1];
		if (!Recv(sizeof(sign), &sign))
			return false;
		CPythonShop::Instance().SetShopSign(sign);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
	break;

	default:
		TraceError("CPythonNetworkStream::RecvOfflineShopPacket: Unknown subheader %d\n", packet_shop.subheader);
		break;
	}

	return true;
}
#endif

# Search


		case HEADER_GC_DRAGON_SOUL_REFINE:
			ret = RecvDragonSoulRefine();
			break;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		case HEADER_GC_OFFLINE_SHOP:
			ret = RecvOfflineShopPacket();
			break;

		case HEADER_GC_OFFLINE_SHOP_SIGN:
			ret = RecvOfflineShopSignPacket();
			break;
#endif
