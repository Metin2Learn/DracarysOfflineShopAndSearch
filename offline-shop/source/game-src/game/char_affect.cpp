# Search


			if ( IS_NO_CLEAR_ON_DEATH_AFFECT(pkAff->dwType) || IS_NO_SAVE_AFFECT(pkAff->dwType) )
			{
				++it;
				continue;
			}

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
			if(AFFECT_DECORATION == pkAff->dwType)
			{
				++it;
				continue;
			}
#endif
