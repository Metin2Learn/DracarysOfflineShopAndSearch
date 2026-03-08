
# Add

#define ENABLE_SHOP_SEARCH_SYSTEM

/

# Search

	CItemData *		GetSelectedItemDataPointer();

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		std::map<DWORD, CItemData*>			GetItemsVector(){ return m_ItemMap; }
#endif

