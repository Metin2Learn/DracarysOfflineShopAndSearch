# Search


		self.serverInfo = None

# Add after

		if app.ENABLE_SHOP_SEARCH_SYSTEM:
			self.ShopSearch=0

# Search

			self.serverInfo = self.GetChild("ServerInfo")

# add after

			if app.ENABLE_SHOP_SEARCH_SYSTEM:
				self.ShopSearch = self.GetChild("SearchShop")
				self.ShopSearch.SetEvent(ui.__mem_func__(self.ShowShopSearch))

# Search

	def Destroy(self):
		self.HideMiniMap()

		self.AtlasWindow.Destroy()
		self.AtlasWindow = None

		self.ClearDictionary()

		self.__Initialize()

# Add after

	if app.ENABLE_SHOP_SEARCH_SYSTEM:
		def ShowShopSearch(self):
			try:
				interface = constInfo.GetInterfaceInstance()
				if interface:
					interface.OpenPrivateShopSearch(0)
			except:
				pass