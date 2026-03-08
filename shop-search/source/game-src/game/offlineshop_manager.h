# Search

	void			RecvPackets(const char * data);

# add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		void			ClearItem(DWORD id);
		void			InsertItem(OFFLINE_SHOP_ITEM* p);
		void			SearchItem(LPCHARACTER ch, const char * data, bool bVnum);
		void			RemoveInMemory(OFFLINE_SHOP_ITEM* item);
		void			SaveInMemory(OFFLINE_SHOP_ITEM* item);
		bool			getMap(TPacketCGShopSearch* pinfo, std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator& it, std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator& itend);
#endif

# Search

		std::map<DWORD, COfflineShop*> 		m_Map_pkOfflineShopByNPC;

# add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMap;
		// sword, two-handed,dagger,bow,claw,fan,bell = 8
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapWeapon;
		// armour,shield,earrings,necklaces,bracelets,shoes,belt,helmets,talisman = 10
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapEquipment;
		// body,hair,weapon,sash = 5
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapCostume;
		// alchemy,beans = 3
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapDragonsoul;
		//std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapConsumables;
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapBook;
		// refinementitems,biologist,quest,energyshards,chests = 5
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapOther;
		// enchant,switcher,advanceditems,stone,rings = 5
		//std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapHelpfulItems[5];
		//std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapOre;
		// namescrolls,skillbook,pets,systempets,egg = 5
		std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapPets;
		//std::unordered_map<DWORD,OFFLINE_SHOP_ITEM*>	m_itemMapMount;
#endif
