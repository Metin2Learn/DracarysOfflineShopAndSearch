# Add


if app.ENABLE_SHOP_SEARCH_SYSTEM:
	import uiPrivateShopSearch

# Search

	self.mallPageDlg = None

# Add after

		if app.ENABLE_SHOP_SEARCH_SYSTEM:
			self.wndPrivateShopSearch=None

# Search

		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

# Add after

		if app.ENABLE_SHOP_SEARCH_SYSTEM:
			if self.wndPrivateShopSearch:
				self.wndPrivateShopSearch.Hide()
				self.wndPrivateShopSearch.Destroy()
				del self.wndPrivateShopSearch
				self.wndPrivateShopSearch=0

# Add

	if app.ENABLE_SHOP_SEARCH_SYSTEM:
		def __MakePrivateShopSearchWindow(self):
			self.wndPrivateShopSearch = uiPrivateShopSearch.PrivateShopSearchDialog()
			self.wndPrivateShopSearch.LoadWindow()
			#self.wndPrivateShopSearch.Hide()

		def OpenPrivateShopSearch(self, type):
			if self.wndPrivateShopSearch == None:
				self.__MakePrivateShopSearchWindow()
				self.wndPrivateShopSearch.Open(type)
				return

			if self.wndPrivateShopSearch.IsShow():
				self.wndPrivateShopSearch.Hide()
			else:
				self.wndPrivateShopSearch.Open(type)
		def RefreshShopSearch(self):
			if self.wndPrivateShopSearch == None:
				self.__MakePrivateShopSearchWindow()
			self.wndPrivateShopSearch.RefreshMe()
			self.wndPrivateShopSearch.RefreshList()