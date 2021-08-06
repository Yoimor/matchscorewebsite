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
	recordset -> close = atof (strtok (NULL, ",\n"));
	recordset -> volume = atof (strtok (NULL, ",\n"));
	recordset -> adj_close = atof (strtok (NULL, ",\n"));

	g_ptr_array_add (data, recordset);
	return 1;
}

/*
static size_t WriteMemoryCallback
(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	int output = *((int*) data);
	write (output, (char*) ptr, realsize);
	
	STOCK record [10000];
	GPtrArray* ticker;
	char buffer[realsize + 1];
   	strncpy (buffer, (char*) ptr, realsize);
	buffer [realsize] = '\0';	
	char* line = strtok (buffer, "\n");
	int i = 0;
	while (line) {
		printf ("%d ... %s\n", ++ i, line);
		line = strtok (NULL, "\n");
	}

	return realsize;
}
*