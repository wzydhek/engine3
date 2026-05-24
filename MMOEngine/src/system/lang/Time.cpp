#include "Time.h"

#ifdef PLATFORM_WIN

 static int conv_num(const char** buf, int* dest, int llim, int ulim)
{
	int result = 0;
	int count = 0;

	while (**buf && std::isdigit((unsigned char)**buf))
	{
		result *= 10;
		result += *(*buf)++ - '0';
		count++;
	}

	if (count == 0 || result < llim || result > ulim)
		return 0;

	*dest = result;
	return 1;
 }

 char* strptime(const char* buf, const char* fmt, struct tm* tm)
{
	while (*fmt && *buf)
	{
		if (*fmt == '%')
		{
			fmt++;

			int val = 0;

			switch (*fmt)
			{
			case 'Y':
				if (!conv_num(&buf, &val, 0, 9999))
					return nullptr;
				tm->tm_year = val - 1900;
				break;

			case 'm':
				if (!conv_num(&buf, &val, 1, 12))
					return nullptr;
				tm->tm_mon = val - 1;
				break;

			case 'd':
				if (!conv_num(&buf, &val, 1, 31))
					return nullptr;
				tm->tm_mday = val;
				break;

			case 'H':
				if (!conv_num(&buf, &val, 0, 23))
					return nullptr;
				tm->tm_hour = val;
				break;

			case 'M':
				if (!conv_num(&buf, &val, 0, 59))
					return nullptr;
				tm->tm_min = val;
				break;

			case 'S':
				if (!conv_num(&buf, &val, 0, 60))
					return nullptr;
				tm->tm_sec = val;
				break;

			default:
				return nullptr;
			}

			fmt++;
		}
		else
		{
			if (*fmt != *buf)
				return nullptr;

			fmt++;
			buf++;
		}
	}

	if (*fmt != '\0')
		return nullptr;

	return const_cast<char*>(buf);
 }

#endif