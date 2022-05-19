#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char target[0x10] = "RAINYDAY";
int main() {
	setvbuf(stdin, 0, 2, 0);
	setvbuf(stdout, 0, 2, 0);
	
	char buf[0x1000];
	printf("target : %p\n", target);
	while(1) {
		gets(buf);
		if(strcmp("stop", buf) == 0)
			break;
		printf(buf);
	}
	
	if(strcmp(target, "SUNNYDAY") == 0)
		system("cat flag");
	else printf("FAILED!!\n");

	return 0;
}
