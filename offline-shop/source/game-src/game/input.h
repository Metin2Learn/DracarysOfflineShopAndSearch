
# Search

		void		Refine(LPCHARACTER ch, const char* c_pData);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		int			OfflineShop(LPCHARACTER ch, const char* data, size_t uiBytes);
		int			MyOfflineShop(LPCHARACTER ch, const char* c_pData, size_t uiBytes);
#endif
