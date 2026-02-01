# Search

	str_to_number(pkTab->horse_skill_point, row[col++]);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	str_to_number(pkTab->shopFlag, row[col++]);
#endif


# Search

	"..., horse_skill_point"

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
			",shop_flag "
#endif

# Search

		pkTab->horse_skill_point,

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		,pkTab->shopFlag
#endif

# Search

	"horse_skill_point = %d, "

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		"shop_flag = %lld, "
#endif