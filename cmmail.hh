#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <curses.h>
#include <sys/time.h>
#include <stdlib.h>

struct url_info{
	int port_no;
	char *host_name;
};

typedef url_info url_info;

class MailType{
	
	struct timeval tv;
	
	
	struct sockaddr_in clnt;
	struct hostent hst;
	struct url_info url;
	int s;
	int err;
	FILE *fsck;
	
	public:
		
	MailType(url_info *url)
	{	
		
		err = 0;
		int i = 0;
		char *tmpp;
		int mx,z;
		fd_set rx_set;
		tv.tv_sec = 5;
		tv.tv_usec = 0;
			
		clnt.sin_addr.s_addr = inet_addr( url->host_name );
		clnt.sin_port = htons( url->port_no );
		clnt.sin_family = AF_INET;
		
		s = socket(PF_INET, SOCK_STREAM, 0);
		
		if( s == -1){
			perror("socket(2)");
			err = 1;
			return;
		}
		
		mx = s + 1;
		
		z = connect(s, (struct sockaddr *)&clnt, sizeof(clnt));
		
		if( z == -1 ){
			err = 1;
			perror("connect(2)");
			close(s);
			exit(EXIT_FAILURE);
		}
		
		FD_ZERO(&rx_set);
		FD_SET(s, &rx_set);
		
		for(;;){
			
			z = select(mx, &rx_set, NULL, NULL, &tv);
			
			if( z == -1 )
				perror("select(2)");
			else{
			
			}if( FD_ISSET(s, &rx_set) ){
				
				write(s, "HELO kerim",strlen("HELO kerim "));
				write(STDOUT_FILENO, "HELO kerim",strlen("HELO kerim "));
			}
		}
				
					
	}
	
	
	
	~MailType()
	{
		if( err == 0 ){
			fprintf(fsck, "QUIT\r\n");
			fprintf(stdout, "QUIT\r\n");
			close(s);
			fclose(fsck);
		}
	}
};


