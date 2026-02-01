
# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
typedef struct offline_shop_item
{
	DWORD		id;
	DWORD		owner_id;
	BYTE		pos;
	int			count;
	long long	price;
	DWORD		vnum;
	long		alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute	aAttr[ITEM_ATTRIBUTE_MAX_NUM];
	BYTE		status;
	char 		szBuyerName[CHARACTER_NAME_MAX_LEN+1];
#ifdef ENABLE_CHANGELOOK_SYSTEM
	DWORD		transmutation;
#endif
	char 		szOwnerName[CHARACTER_NAME_MAX_LEN+1];
} OFFLINE_SHOP_ITEM;
typedef struct ShopLog {
	char	name[CHARACTER_NAME_MAX_LEN+1];
	char	date[25];
	DWORD	itemVnum;
	BYTE	itemCount;
	long long	price;
}TShopLog;
typedef struct SShopDecoration {
	char	sign[SHOP_SIGN_MAX_LEN + 1];
	DWORD	owner_id;
	BYTE	vnum;
	BYTE	type;
}TShopDecoration;
typedef struct SGDOfflineShopCreate
{
	DWORD	owner_id;
	char	owner_name[CHARACTER_NAME_MAX_LEN+1];
	char	sign[SHOP_SIGN_MAX_LEN + 1];
	long	x;
	long	y;
	long	z;
	DWORD	mapindex;
	DWORD	type;
	BYTE	channel;
	long long	slotflag;
	OFFLINE_SHOP_ITEM items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	long long	price;
	ShopLog		log[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	int		time;
} TOfflineShop;
typedef struct SOfflineShopBuy
{
	OFFLINE_SHOP_ITEM	item;
	DWORD	customer_id;
	char	customer_name[CHARACTER_NAME_MAX_LEN + 1];
	ShopLog	log;
	int		log_index;
}TOfflineShopBuy;
typedef struct SOfflineShopChangeTitle
{
	DWORD	owner_id;
	char	sign[SHOP_SIGN_MAX_LEN + 1];
}TOfflineShopChangeTitle;
typedef struct SOfflineShopItemTable
{
	DWORD		vnum;
	int			count;
	TItemPos	pos;
	long long		price;
	BYTE		display_pos;
} TOfflineShopItemTable;
typedef struct SOfflineShopAddItem
{
	TItemPos	bPos;
	BYTE		bDisplayPos;
	long long		lPrice;
} TOfflineShopAddItem;
typedef struct SOfflineShopOpenSlot
{
	DWORD	owner_id;
	long long	flag;
} TOfflineShopOpenSlot;
typedef struct SOfflineShopBackItem
{
	DWORD	owner_id;
	OFFLINE_SHOP_ITEM items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
} TOfflineShopBackItem;
enum {
	// db
	CREATE_OFFLINESHOP,
	DESTROY_OFFLINESHOP,
	REMOVE_ITEM,
	ADD_ITEM,
	BUY_ITEM,
	WITHDRAW_MONEY,
	CHANGE_TITLE,
	CLEAR_LOG,
	CHANGE_DECORATION,
	CHANGE_OPEN_SLOT,
	TIME_DONE,
	GET_BACK_ITEM,
	ADD_TIME,

};
struct shop_decoration {
	BYTE subheader;
	TShopDecoration decoration;
};
struct shop_create {
	BYTE subheader;
	TOfflineShop offlineshop;
};
struct shop_buy {
	BYTE subheader;
	TOfflineShopBuy buyItem;
};
struct shop_title {
	BYTE subheader;
	TOfflineShopChangeTitle title;
};
struct shop_owner {
	BYTE subheader;
	DWORD owner_id;
};
struct shop_item {
	BYTE subheader;
	OFFLINE_SHOP_ITEM item;
};
struct shop_slot {
	BYTE subheader;
	TOfflineShopOpenSlot ch;
};
struct shop_back {
	BYTE subheader;
	TOfflineShopBackItem back;
};
#endif


# Search

} TPlayerTable;

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	long long	shopFlag;
#endif


# Search

HEADER_GD_BREAK_MARRIAGE					= 116,

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	HEADER_GD_OFFLINESHOP= 117,
#endif

# Search

	HEADER_DG_GUILD_WAR_BET

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	HEADER_DG_OFFLINESHOP = 109,
#endif

# Done



