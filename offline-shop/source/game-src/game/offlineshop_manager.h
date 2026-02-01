#pragma once
#ifdef ENABLE_OFFLINESHOP_SYSTEM
class COfflineShopManager : public singleton<COfflineShopManager>
{
	public:
		COfflineShopManager();
		~COfflineShopManager();
		void			Initialize();

		LPOFFLINESHOP	FindOfflineShopPID(DWORD pid);
		void			CompareOffShopEventTime();

		void			OpenMyOfflineShop(LPCHARACTER ch, const char* c_pszSign, TOfflineShopItemTable* pTable, BYTE bItemCount, DWORD shopVnum, BYTE titleType);
		void			CreateOfflineShop(TOfflineShop* offlineshop);
		void			StopShopping(LPCHARACTER ch);
		void			OpenOfflineShop(LPCHARACTER ch);
		void			OpenOfflineShopWithVID(LPCHARACTER ch, DWORD vid);
		bool			HasOfflineShop(LPCHARACTER ch);

		void			Buy(LPCHARACTER ch, DWORD vid, BYTE bPos);
		void			BuyItemReal(TOfflineShopBuy* item);

		void			AddItem(LPCHARACTER ch, BYTE bDisplayPos, TItemPos bPos, long long iPrice);
		void			AddItemReal(OFFLINE_SHOP_ITEM* item);
		
		void			OpenSlot(LPCHARACTER ch, BYTE bPos);
		void			OpenSlotReal(TOfflineShopOpenSlot* ch);

		void			RemoveItem(LPCHARACTER ch, BYTE bPos);
		void			RemoveItemReal(OFFLINE_SHOP_ITEM* item);
		
		void			ShopLogRemove(LPCHARACTER ch);
		void			ShopLogRemoveReal(DWORD ch);

		void			ChangeDecoration(LPCHARACTER ch, TShopDecoration* data);
		void			ChangeDecorationReal(TShopDecoration* ch);

		void			WithdrawMoney(LPCHARACTER ch);
		void			WithdrawMoneyReal(DWORD ch);

		void			DestroyOfflineShop(LPCHARACTER ch);
		void			DestroyOfflineShopReal(DWORD ch);

		void			ChangeTitle(LPCHARACTER ch, const char* title);
		void			ChangeTitleReal(TOfflineShopChangeTitle* p);

		void			CloseOfflineShopForTime(LPOFFLINESHOP offlineshop);
		void			CloseOfflineShopForTimeReal(DWORD offlineshop);

		void			GetBackItem(LPCHARACTER ch);
		void			GetBackItemReal(TOfflineShopBackItem* ch);

		void			ShopAddTime(LPCHARACTER ch);
		void			ShopAddTimeReal(DWORD ch);

		void			RecvPackets(const char * data);

		std::vector<DWORD> 					m_Map_pkShopTimes;

	private:
		LPEVENT								m_pShopTimeEvent;
		
		std::vector<DWORD> 					m_Map_pkOfflineShopCache;
		std::map<DWORD, COfflineShop*> 		m_Map_pkOfflineShopByNPC;
};
#endif

