
# Search

void initBackground()

# Add before

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
#include "PythonCharacterManager.h"
PyObject * backgroundCreatePrivateShopPos(PyObject * poSelf, PyObject * poArgs)
{
	int iVID;
	if (!PyTuple_GetInteger(poArgs, 0, &iVID))
		return Py_BadArgument();

	std::string g_strEffectShopPos = "d:/ymir work/effect/etc/direction/direction_land2.mse";

	CInstanceBase * pCharacterInstance = CPythonCharacterManager::Instance().GetInstancePtr(iVID);
	if (!pCharacterInstance)
		return Py_BuildNone();

	TPixelPosition kPixelPosition;
	pCharacterInstance->NEW_GetPixelPosition(&kPixelPosition);

	CPythonBackground::Instance().CreateSpecialShopPosEffect(iVID, +kPixelPosition.x, -kPixelPosition.y, +kPixelPosition.z, g_strEffectShopPos.c_str());

	return Py_BuildNone();
}

PyObject * backgroundDeletePrivateShopPos(PyObject * poSelf, PyObject * poArgs)
{
	CPythonBackground::Instance().DeleteSpecialShopPosEffect();
	return Py_BuildNone();
}
#endif

/

# Search

	{ NULL, NULL, NULL },

# Add before

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		{ "CreatePrivateShopPos", backgroundCreatePrivateShopPos, METH_VARARGS },
		{ "DeletePrivateShopPos", backgroundDeletePrivateShopPos, METH_VARARGS },
#endif

