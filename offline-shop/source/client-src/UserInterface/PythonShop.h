# Search

	BOOL				m_isShoping;

# Add after


#ifdef ENABLE_OFFLINESHOP_SYSTEM
	struct OfflineShopTab
	{
		TOfflineShopItemData items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	};

	DWORD				m_dwDisplayedCount;
	DWORD				m_dwRealWatcherCount;
	OfflineShopTab		m_aOfflineShoptabs[SHOP_TAB_COUNT_MAX];
	std::map<TItemPos, TOfflineShopItemTable>	m_OfflineShopItemStock;
	BOOL				m_isOfflineShop;
	char				sign[SHOP_SIGN_MAX_LEN + 1];
	bool				m_bHasOfflineShop;
	long long			m_llCurrentOfflineShopMoney;
	long long			m_shopFlag;
	int					time;
	DWORD				type;
#endif

# Search

	BOOL IsOpen() { return m_isShoping; }

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	void SetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData& c_rShopItemData);
	BOOL GetOfflineShopItemData(DWORD dwIndex, const TOfflineShopItemData** c_ppItemData);

	void SetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData& c_rShopItemData);
	BOOL GetOfflineShopItemData(BYTE tabIdx, DWORD dwSlotPos, const TOfflineShopItemData** c_ppItemData);

	void SetShopDisplayedCount(DWORD dwDisplayedCount) { m_dwDisplayedCount = dwDisplayedCount; }
	void SetShopSign(const char* g_sign) { strcpy(sign, g_sign); }
	const char* GetShopSign() { return sign; }
	DWORD	GetShopDisplayedCount() { return m_dwDisplayedCount; }
	BOOL IsOfflineShop() { return m_isOfflineShop; }
	void ClearOfflineShopStock() { m_OfflineShopItemStock.clear(); }
	void AddOfflineShopItemStock(TItemPos ItemPos, BYTE byDisplayPos, long long dwPrice);
	void DelOfflineShopItemStock(TItemPos ItemPos);
	long long	 GetOfflineShopItemPrice(TItemPos ItemPos);
	BYTE	GetOfflineShopItemStatus(TItemPos ItemPos);
	void BuildOfflineShop(const char* c_szName, DWORD shopVnum, BYTE shopTitle);

	void	SetCurrentOfflineShopMoney(long long llMoney) { m_llCurrentOfflineShopMoney = llMoney; }
	long long	GetCurrentOfflineShopMoney() { return m_llCurrentOfflineShopMoney; }

	bool	HasOfflineShop() { return m_bHasOfflineShop; }
	void	SetHasOfflineShop(bool bStatus) { m_bHasOfflineShop = bStatus; }

	DWORD	GetRealWatcherCount() { return m_dwRealWatcherCount; }
	void	SetRealWatcherCount(DWORD p) { m_dwRealWatcherCount = p; }

	long long	GetShopFlag() { return m_shopFlag; }
	void	SetShopFlag(long long p) { m_shopFlag = p; }

	int		GetShopTime() { return time; }
	void	SetShopTime(int a) { time = a; }

	DWORD	GetShopType() { return type; }
	void	SetShopType(DWORD a) { type = a; }
#endif