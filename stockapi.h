#include "stockapi.h"

static size_t WriteMemoryCallback
(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t r