# Add

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
bool CPythonNetworkStream::SendPrivateShopSearchInfo(TPacketCGShopSearch* p)
{
	if (!__CanActMainInstance())
		return true;
	if (!Send(sizeof(TPacketCGShopSearch), p))
	{
		#ifdef ENABLE_CONSOLE_LOG_WINDOW
		Tracen("SendPrivateShopSearchInfo Error");
		#endif
		return false;
	}

	return true;
}

bool CPythonNetworkStream::RecvShopSearchSet()
{
	TPacketGCShopSearchItemSet packet_item_set;
	if (!Recv(sizeof(TPacketGCShopSearchItemSet), &packet_item_set))
		return false;
	for (BYTE a = 0; a < packet_item_set.count; a++)
		CPythonPrivateShopSearch::Instance().AddItemData(packet_item_set.items[a]);
	__RefreshShopSearchWindow();
	return true;
}
#endif

# Search


		case HEADER_GC_DRAGON_SOUL_REFINE:
			ret = RecvDragonSoulRefine();
			break;

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		case HEADER_GC_SHOPSEARCH_SET:
			ret = RecvShopSearchSet();
			break;
#endif

# Search


	if (m_isRefreshGuildWndGradePage)
	{
		m_isRefreshGuildWndGradePage = false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshGuildGradePage", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 300;
	}

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	if (m_isRefreshShopSearchWnd)
	{
		m_isRefreshShopSearchWnd = false;
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshShopSearch", Py_BuildValue("()"));
		s_nextRefreshTime = curTime + 500;
	}
#endif

# Search

void CPythonNetworkStream::__RefreshInventoryWindow()
{
	m_isRefreshInventoryWnd = true;
}

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
void CPythonNetworkStream::__RefreshShopSearchWindow()
{
	m_isRefreshShopSearchWnd = true;
}
#endif
