
# Add

	if app.ENABLE_SHOP_SEARCH_SYSTEM:
		def OpenPrivateShopSearch(self, type):
			if self.interface:
				self.interface.OpenPrivateShopSearch(type)

		def RefreshShopSearch(self):
			if self.interface:
				self.interface.RefreshShopSearch()

		def BuyShopSearch(self):
			self.interface.RefreshShopSearch()

		def BuyShopSearch2(self):
			if self.interface:
				if self.interface.wndPrivateShopSearch.IsShow():
					self.interface.wndPrivateShopSearch.StartSearch()