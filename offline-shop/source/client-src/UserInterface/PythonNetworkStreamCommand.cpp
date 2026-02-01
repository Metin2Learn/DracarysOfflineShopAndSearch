# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "PythonShop.h"
#endif


# Search

	else if (!strcmpi(szCmd, "ObserverTeamInfo"))

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	else if (!strcmpi(szCmd, "OfflineShopSetFlag"))
	{
		long long flag = atoi(TokenVector[1].c_str());
		CPythonShop::Instance().SetShopFlag(flag);
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "RefreshOfflineShop", Py_BuildValue("()"));
	}
#endif

