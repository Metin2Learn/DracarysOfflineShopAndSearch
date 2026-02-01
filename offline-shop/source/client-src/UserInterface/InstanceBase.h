# Search

	TPixelPosition			m_kPPosDust;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	DWORD					m_myShop;
#endif

# Search

	EFFECT_REFINED_NUM,

# add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		EFFECT_MYOFFSHOP,
#endif

# Search

	NEW_AFFECT_IS_MARRIAGE = 2000,

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		NEW_AFFECT_DECORATION = 703,
#endif

# Search

	BOOL					IsNPC();

# Add after

	bool					IsShop() {return (GetRace() >= 30000 && GetRace() <= 30020);}
