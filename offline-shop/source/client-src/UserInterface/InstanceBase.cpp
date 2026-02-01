# Search

	SetEventHandler(CActorInstance::IEventHandler::GetEmptyPtr());

# Addd after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	m_myShop=0;
#endif

# Search
	
	__EffectContainer_Destroy();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (m_myShop)
	{
		__DetachEffect(m_myShop);
		m_myShop = 0;
	}
#endif

# Search

	m_GraphicThingInstance.SetBattleHitEffect(ms_adwCRCAffectEffect[EFFECT_HIT]);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
			if (IsShop())
			{
				if (m_myShop == 0 && strstr(c_rkCreateData.m_stName.c_str(), CPythonPlayer::Instance().GetName()))
					m_myShop =	__AttachEffect(EFFECT_REFINED + EFFECT_MYOFFSHOP);
			}
#endif

