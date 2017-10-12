#include <b64/b64.h>
#include <stdio.h>
#include <assert.h>

int main()
{
	const char* input = "[\"0.0.0.0\"]";
    printf("%s\n%s\n", input, "WyIwLjAuMC4wIl0=");
	char* encoded;
	char* decoded;
	
	/* encode the data */
	encoded = encode(input);
	printf("encoded: %s", encoded); /* encoded data has a trailing newline */

	/* decode the data */
	decoded = decode(encoded);
	printf("decoded: %s\n", decoded);
	
	/* compare the original and decoded data */
	assert(strcmp(input, decoded) == 0);
	
	free(encoded);
	free(decoded);
	return 0;
}


