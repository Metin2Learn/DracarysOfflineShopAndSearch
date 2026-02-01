# Add

if app.ENABLE_OFFLINESHOP_SYSTEM:
	SHOPNAMES_RANGE = 2500
	MAX_SHOP_TYPE = 13
	MAX_SHOP_TITLE = 6
	def NumberToString(n) :
		if n <= 0 :
			return "0"
		return "%s" % ('.'.join([ i-3<0 and str(n)[:i] or str(n)[i-3:i] for i in range(len(str(n))%3, len(str(n))+1, 3) if i ]))

	_interface_instance = None
	def GetInterfaceInstance():
		global _interface_instance
		return _interface_instance
	def SetInterfaceInstance(instance):
		global _interface_instance
		if _interface_instance:
			del _interface_instance
		_interface_instance = instance

	_game_instance = None
	def GetGameInstance():
		global _game_instance
		return _game_instance
	def SetGameInstance(instance):
		global _game_instance
		if _game_instance:
			del _game_instance
		_game_instance = instance
	
	def IS_SET(value, flag):
		return (value & flag) == flag
	def SET_BIT(value, bit):
		return value | (bit)
	def REMOVE_BIT(value, bit):
		return value & ~(bit)
	def getFlagValue(value):
		return 1 << value
	
	def getInjectCheck(text):
		words = ["SELECT", "TRUNCATE", "INSERT", "REPLACE", "DELETE", "ALTER", "DROP",";", ":", "*", "'", '"', "="]
		characters = []
		for word in words:
			if text.find(word) != -1:
				return True
		return False
