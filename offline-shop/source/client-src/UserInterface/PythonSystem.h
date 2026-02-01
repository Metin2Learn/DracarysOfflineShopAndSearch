# Search

	bool							IsAutoTiling() { return (m_Config.bSoftwareTiling == 1) ? true : false; }

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	void							SetShopNamesRange(float fRange) { m_Config.shopnames_range = fRange; }
	float							GetShopNamesRange() { return m_Config.shopnames_range; }
#endif


# Search

		int				gamma;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		float			shopnames_range;
#endif

