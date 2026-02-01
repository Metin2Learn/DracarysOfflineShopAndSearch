
# Add in const


#ifdef ENABLE_OFFLINESHOP_SYSTEM
	PyModule_AddIntConstant(poModule, "ENABLE_OFFLINESHOP_SYSTEM", 1);
	PyModule_AddIntConstant(poModule, "ENABLE_OFFLINE_SHOP_DECORATION", 1);
	PyModule_AddIntConstant(poModule, "WJ_CHANGELOOK_SYSTEM", 0);
#else
	PyModule_AddIntConstant(poModule, "ENABLE_OFFLINESHOP_SYSTEM", 0);
#endif
