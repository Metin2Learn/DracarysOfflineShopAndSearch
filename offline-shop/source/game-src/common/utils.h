# Add in not has -> long long

inline bool str_to_number (long long& out, const char *in)
{
	if (0==in || 0==in[0])	return false;

	out = (long long) strtoul(in, NULL, 10);
	return true;
}

