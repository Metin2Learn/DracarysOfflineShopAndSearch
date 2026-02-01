# Add

bool getInjectText(const char* data)
{
	std::string text = data;
	std::string words[] = { "SELECT", "TRUNCATE", "INSERT", "REPLACE", "DELETE", "ALTER", "DROP", ";", ":", "*", "'", "=" };
	for (size_t j = 0; j < (sizeof(words) / sizeof(words[0])); ++j)
	{
		if (text.find(words[j]) != -1)
			return true;
	}
	return false;
}
