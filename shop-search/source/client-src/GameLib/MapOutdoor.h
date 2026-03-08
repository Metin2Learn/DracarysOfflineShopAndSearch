
# Add

#define ENABLE_SHOP_SEARCH_SYSTEM

/ 

# Search

	public:
		void SpecialEffect_Create(DWORD dwID, float x, float y, float z, const char* c_szEffName);
		void SpecialEffect_Delete(DWORD dwID);
		void SpecialEffect_Destroy();

# Add before

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	private:
		int m_iLastShopPos;
	public:
		void SpecialShopPosEffect_Create(DWORD dwID, float x, float y, float z, const char* c_szEffName);
		void SpecialShopPosEffect_Delete();
#endif