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
		mem->buffer[ mem->size ] = 0;
	}
	return realsize;
}

int str_to_array (char* line, GPtrArray* data) {

	STOCK* recordset = (STOCK*) malloc (sizeof (STOCK));
	char* token = strtok (NULL, ",\n");
	
	if (!token) {

		return 0;
	}

	strcpy (line, token);
	
	strcpy (recordset -> date, line);
	recordset -> open = atof (strtok (NULL, ",\n"));
	recordset -> high = atof (strtok (NULL, ",\n"));
	recordset -> low = atof (strtok (NULL, ",\n"));
	recordset -> 