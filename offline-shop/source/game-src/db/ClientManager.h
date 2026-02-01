# Search

	void RequestChannelStatus(CPeer* peer, DWORD dwHandle);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	std::map<DWORD, TOfflineShop*>	m_Offlineshop;
	void	OfflineShopAssert(TOfflineShop* p);
	void	CreateOfflineShop(TOfflineShop* p);
	void	DeleteOfflineShop(DWORD ownerid);
	void	RemoveItem(OFFLINE_SHOP_ITEM* item);
	void	AddItem(OFFLINE_SHOP_ITEM* item);
	void	BuyItem(TOfflineShopBuy* item);
	void	WithdrawMoney(DWORD ch);
	void	ClearLog(DWORD ch);
	void	ChangeDecoration(TShopDecoration* ch);
	void	ChangeTitle(TOfflineShopChangeTitle* p);
	void	OpenSlot(TOfflineShopOpenSlot* p);
	void	TimeDone(DWORD ch);
	void	GetBackItem(DWORD p);
	void	AddTime(DWORD p);
	void	RecvPackets(const char* data);
	bool	InitializeOfflineShop();
#endif