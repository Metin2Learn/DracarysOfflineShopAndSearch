# Search

	bool SendMessengerRemovePacket(const char* c_szKey, const char* c_szName);

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	bool SendPrivateShopSearchInfo(TPacketCGShopSearch* p);
	bool RecvShopSearchSet();
#endif

# Search

	bool m_isRefreshGuildWndGradePage;

# add after


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	bool m_isRefreshShopSearchWnd;
#endif

# Search

void __RefreshTargetBoard();

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	void __RefreshShopSearchWindow();
#endif

