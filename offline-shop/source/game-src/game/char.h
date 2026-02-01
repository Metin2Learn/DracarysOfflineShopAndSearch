
# Search

class CPetSystem;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
class COfflineShop;
typedef class COfflineShop* LPOFFLINESHOP;
#endif

# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	public:
		void 				SetOfflineShop(LPOFFLINESHOP pkOfflineShop){m_pkOfflineShop=pkOfflineShop;}
		LPOFFLINESHOP		GetOfflineShop() { return m_pkOfflineShop; }

		bool				IsOfflineShopNPC() { return (IsNPC() && GetOfflineShop()); }

		bool				GetOfflineShopPanel() {return isOfflineShopPanelOpen;}
		void				SetOfflineShopPanel(bool flag) {isOfflineShopPanelOpen= flag;}

		long long	GetOfflineShopFlag() { return m_pkOfflineShopFlag; }
		void				SetOfflineShopFlag(long long ptr) { m_pkOfflineShopFlag = ptr; }

		void				SetProtectTime(const std::string& flagname, int value);
		int					GetProtectTime(const std::string& flagname) const;

		bool				CheckWindows(bool bChat);
		bool				CanAddItemShop();
		bool				CanDestroyShop();
		bool				CanOpenOfflineShop();
		bool				CanOpenShopPanel();
		bool				CanRemoveItemShop();
		bool				CanCreateShop();
		bool				CanRemoveLogShop();
		bool				CanWithdrawMoney();
		bool				CanChangeTitle();
		bool				CanChangeDecoration();
		bool				CanBuyItemOfflineShop();
		bool				CanGetBackItems();
		bool				CanAddTimeShop();

	protected:
		LPOFFLINESHOP		m_pkOfflineShop;
		bool				isOfflineShopPanelOpen;
		long long			m_pkOfflineShopFlag;
		std::map<std::string, int>  m_protection_Time;
#endif



# Done
