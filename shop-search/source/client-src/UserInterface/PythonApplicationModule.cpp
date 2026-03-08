
# Add in const

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_SHOP_SEARCH_SYSTEM", 1);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_SHOP_SEARCH_SYSTEM", 0);
#endif