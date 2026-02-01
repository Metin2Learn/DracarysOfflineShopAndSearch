# Search

fprintf(fp, "GAMMA\t%d\n", m_Config.gamma);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	fprintf(fp, "shop_range\t%.3f\n", m_Config.shopnames_range);
#endif

# Search

		else if (!stricmp(command, "GAMMA"))
			m_Config.gamma = atoi(value);

# add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		else if (!stricmp(command, "shop_range"))
		{
			if (strchr(value, '.') == 0)
			{
				m_Config.shopnames_range = pow(10.0f, (-1.0f + (((float)atoi(value)) / 5.0f)));
				if (atoi(value) == 0)
					m_Config.shopnames_range = 0.5f;
			}
			else
				m_Config.shopnames_range = atof(value);
		}
#endif

# Search


	m_Config.gamma = 3;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	m_Config.shopnames_range = 0.5f;
#endif

