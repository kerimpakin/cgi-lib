#include "cmmail.hh"

int main()
{	
	url_info url;
	url.port_no = 25;
	url.host_name = "127.0.0.1";
	
	MailType mail(&url);
	
}
