#include <stdio.h>
#include <arpa/inet.h>

main( ) {
	struct in_addr inp;
	const	char	*ipAddr ="192.168.0.43";
	char		*addr;

	inet_aton(ipAddr, &inp);
	printf("ip(dotted decimal)[%s] -> ip(binary)[0x%x]\n", ipAddr, ntohl(inp.s_addr));

 	addr = inet_ntoa(inp);
	printf("ip(binary)[0x%x] -> ip(dotted decimal)[%s]\n", ntohl(inp.s_addr), addr);
}
