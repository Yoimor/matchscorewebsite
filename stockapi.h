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
*/


/* curl_global_init (CURL_GLOBAL_ALL); */

long get_stock_from_yahoo (char* code, 
		char* from_mm, char* from_dd, char* from_yy, 
		char* to_mm, char* to_dd, char* to_yy, GPtrArray* data) {
		
		STOCK record [10000];	
		int fd[2];

		int curse;
		
		char* temp = "http://ichart.finance.yahoo.com/table.csv?s=";
		char url [100];
		memset (url, 0x00, sizeof (url));
		strcpy (url, temp);
		curse = (int) strlen (url);

		strcpy (url + curse, code);
		curse = (int) strlen (url);
		
		strcpy (url + curse, "&a=");
		curse = (int) strlen (url);

		strcpy (url + curse, from_mm);
		curse = (int) strlen (url);

		strcpy (url + curse, "&b=");
		curse = (int) strlen (url);

		strcpy (url + curse, from_dd);
		curse = (int) strlen (url);
	

		strcpy (url + curse, "&c=");
		curse = (int) strlen (url);

		strcpy (url + curse, from_yy);
		curse = (int) strlen (url);
		
		strcpy (url + curse, "&d=");
		curse = (int) strlen (url);

		strcpy (url + curse, to_mm);
		curse = (int) strlen (url);
		
		strcpy (url + curse, "&e=");
		curse = (int) strlen (url);

		strcpy (url + curse, to_dd);
		curse = (int) strlen (url);
		
		strcpy (url + curse, "&f=");
		curse = (int) strlen (url);

		strcpy (url + curse, to_yy);
		curse = (int) strlen (url);

		strcpy (url + curse, "&g=d&ignore=.csv");
		
	/*	int output = open ("output2.csv", O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (output == -1) return 1; */
		BufferStruct buffer;
		buffer.buffer = NULL;
		buffer.size = 0;
		CURL* curlHandle = curl_easy_init ();
		curl_easy_setopt (curlHandle, CURLOPT_URL, url);
		curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
		curl_easy_setopt (curlHandle, CURLOPT_WRITEDATA, (void*) &buffer);
		curl_easy_perform (curlHandle);
		
		long statLong;
		curl_easy_getinfo (curlHandle, CURLINFO_HTTP_CODE, &statLong);
		
		if (statLong != 200L) {
			return statLong;
		}
		
		int i = 0;
		char* line = strtok (buffer.buffer, ",\n");
		for (i=0;i<6;i++) {
			strtok (NULL, ",\n");
		}
	
		int t = 1;
		while (str_to_array (line, data)) {
			
		}
		curl_easy_cleanup (curlHandle);

		return statLong;
	/*	close (output);	*/
}

