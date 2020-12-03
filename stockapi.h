#include "stockapi.h"

static size_t WriteMemoryCallback
(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;

	BufferStruct * mem = (BufferStruct *) data;

	mem->buffer = (char*) realloc(mem->buffer, mem->size + realsize + 1);

	if ( mem->buffer )
	{
		memcpy( &( mem->buffer[ mem->size ] ), ptr, realsize );
		mem->size += realsize;
		mem->buffer[ mem->size