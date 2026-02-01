# Search

	bool SendMessengerRemovePacket(const char* c_szKey, const char* c_szName);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	bool RecvOfflineShopPacket();
	bool RecvOfflineShopSignPacket();
#endif

# Search

	bool SendGiveItemPacket(DWORD dwTargetVID, TItemPos ItemPos, int iItemCount);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	// Offline Shop
	bool SendBuildOfflineShopPacket(const char* c_szName, const std::vector<TOfflineShopItemTable>& c_rSellingItemStock, DWORD shopVnum, BYTE shopTitle);
#endif

# Search

	bool SendShopSellPacketNew(WORD wSlot, WORD wCount);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	// Offline Shop
	bool SendOfflineShopEndPacket();
	bool SendOfflineShopBuyPacket(DWORD vid, BYTE pos);
	bool SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long lPrice);
	bool SendRemoveOfflineShopItem(BYTE bPos);
	bool SendOpenShopSlot(BYTE bPos);
	bool SendGetBackItems();
	bool SendAddTime();
	bool SendDestroyOfflineShop();
	bool SendTakeOfflineMoney();
	bool SendOfflineShopChangeTitle(const char* title);
	bool SendOfflineShopCheck();
	bool SendOfflineShopButton();
	bool SendOfflineShopRemoveLogs();
	bool SendOfflineOpenWithVID(DWORD vid);
	bool SendOfflineShopChangeDecoration(const char* sign, DWORD vnum, DWORD type);
#endif

