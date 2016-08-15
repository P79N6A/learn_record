/*
  Copyright (c) 2009 Dave Gamble
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
 
  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
	char *out;
	cJSON *json;
	cJSON *js;
	json=cJSON_Parse(text);
	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
	else
	{
		int i, size;
		out=cJSON_Print(json);
		printf("object count : %d\n", cJSON_GetArraySize(json));
		printf("cjson  type %d\n", json->type);
		printf("%s\n", out);
		free(out);

		//get array
		js = cJSON_GetObjectItem(json, "msg");
		size = cJSON_GetArraySize(js);
		printf("arry size : %d\n", size);
		printf("cjson  type %d\n", js->type);
		for (i=0; i<size; i++) {
			printf("%d : %d\n", i, (unsigned char)cJSON_GetArrayItem(js, i)->valueint);
		}

		cJSON_Delete(json);
	}
}

int main (int argc, const char * argv[]) {
	/* a bunch of json: */
	char text3[]="{\n \"msg\": [11, 22, 33, 22, 33], \"other\" : 78 \n}";
	doit(text3);

	return 0;
}
