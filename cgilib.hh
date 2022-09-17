/*****************************************************************\
 * Author: Kerim BASOL						 *
 * Nick Name: CPU_Kerim or C++ or GTK+				 *
 * ICQ:97683818							 *
 * Written Date: November/08/1998				 *
 * This header file writen by Kerim BASOL for WebDevelopers.	 *
 * If you want to change You must protect my name in sourde file *
 * 								 *
 * Mail1:kkbasol@hotmail.com					 *
 * Mail2:kkbasol@netscape.net					 *
 * Author's sites:						 *
 * 								 *
 * Site:http://www.CGIMarket.com				 *
 *				 				 *
 * 								 *
 * These headers protected under GNU Licence			 *
\*****************************************************************/

#ifndef _CGILIB_H_
#define _CGILIB_H_ 1

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>


#ifdef __POSIX__

#include <sys/types.h>
#include <sys/stat.h>

/* socket */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#endif

using namespace std;

/* These macros are for REQUEST_METHOD type*/

#define UNKNOWN 0
#define POST 1
#define GET 2

/* These macros are for CONTENT_TYPE (Response.Write("",PLAIN) ) */
#define PLAIN 0
#define HTML 1



/* This extern value is for environtment */

extern char **environ;

/* These functions are produce environment dump */

void printenvPLAIN()
{
	char **p = environ;
	
	while(*p)
	{
		printf("%s\n",*p++);
	}

}

void printenvHTML()
{
char **p = environ;

	while(*p)
	{
		printf("%s<br>\n",*p++);
	}
}

/*These functions are for method type */

inline int isget(){
	
	char *p = getenv("REQUEST_METHOD");
		
	if(p == NULL)
		return 0;
	
	if( !strcmp(p,"GET") )
		return 1;
	
	return 0;


}

inline int ispost(){

	char *p = getenv("REQUEST_METHOD");

		
	if(p == NULL)
		return 0;
				
	if( !strcmp(p ,"POST") )
		return 1;
		
	return 0;


}

  ///////////////////////////////////////////
 // This line declines TranslateType Class//
///////////////////////////////////////////



class TranslateType
{
	public:
	char *Decode(char* str2);
	char *Encode(auto char* str);

}Translate;


char *TranslateType::Decode(char* str)
{
	char *str2;// = (char*)malloc(sizeof(char)*1024);
	char number[3];
	
	number[2] = '\0';
	
	if(str == NULL)
		return NULL;
	
	unsigned int k;	/*It can loop only value from 0 to ~4000000000 
			 	  this means is you can decode value from
			  	  only 0 to ~4000000000*/
	
	
	
	
	/*If any varible is not legal this line
	  returns directly str value*/
	for(k = 0; str[k]; ++k)
	{
		if(str[k] == '%')
		{
			k++;
			if( !isxdigit(str[k]) )
				return str;
			k++;
			
			if( !isxdigit(str[k]) )
				return str;
			
		}	
	
	}
	/*If any varible is not legal this line
	  returns directly str value*/
	  
	
	
	
	k = 0;
	
	str2 = str;//strcpy(str2,str);
		
	if(str2 == NULL /*&& str == NULL*/)
		return str;
	
	
		
	for(k = 0; ; ++str,++k)
	{
		if(*str == '\0'){str2[k] = '\0';break;}

		else if(*str == '\x25')
		{ 			
			++str;number[0] = *str;
			++str;number[1] = *str;
			
			str2[k] = (char) strtol(number,NULL,16);
					
		} 
			
		else if(*str == '+'){str2[k] = ' ';}
		
		else str2[k] = *str; 
		
		if(*str == '\0'){str2[k] = '\0';break;}
	}
	
	return str2;
}


char *TranslateType::Encode(char* str)
{
	
	int lengthofStr = strlen(str) * 3 + 1;
	char *str2 = (char*) malloc( sizeof(char) * lengthofStr );
	char *str2Seg = str2;

			
	if(str == NULL)
		return NULL;
	
	unsigned int k;
	unsigned int i;
	
	for(k = 0,i = 0; str[k]; k++,i++,str2Seg++)
	{
		if( isalnum(str[k]) || str[k] == '*' || str[k] == '_' || str[k] == '-' || str[k] == '.'){str2[i] = str[k];continue;}
		
		else if(str[k] == ' '){str2[i] = '+';continue;}
		{
			
			str2[i] = '%';++str2Seg;++i;
			sprintf(str2Seg,"%X",str[k]);++str2Seg;++i;
			continue;			
			
		}
		
			
		
	}
	/*++i;*/str2[i] = '\0';
	
	str = str2;
	return str;
}


  //////////////////////////////////////////
 // This line declines ResponseType Class//
//////////////////////////////////////////

class ResponseType
{
	char *directory;
	int flg_of_content;
	
	public:
	
	ResponseType::ResponseType()
	{
		this->flg_of_content = 0;
		
	}
	
	void ContentType(char *str);
	void Redirect(char *str);
	void Expires(char *str);
	void Header(char *title);
	void Header(char *title,char *bodypar);
	void Header(char *title,char *bodypar,char *headpar);
	void Footer();
	void Write(char chr);
	void WriteNBR(char chr);
	void Write(char *str);
	void WriteNBR(char *str);
	void Write(char *str,char parameter);
	bool FileOutput(char *fname);/* return variable 1 for success 0 for fail */
	bool FileOutput(char *fname,char parameter);/* return variable 1 for success 0 for fail */
	void Script(char *lng, char *script);
	void Script(char *lng, char *script, char *parameter);
	void Cookie(char *name,int value);
	void Cookie(char *name,char *value);
	void Cookie(char *name, char *value, char *param);
	void Cookie(char *name, int value, char *param);
	void SetRootDirectory(char *root);
	bool CmdOutput(char *command);
	bool CmdOutput(char *command, char parameters);
	
	#ifdef __POSIX__
					
		void URLOutput(char *url);
	
	#endif
	
	~ResponseType();
}Response;


inline void ResponseType::ContentType(char *str)
{
	if( this->flg_of_content == 0) {
		printf("Content-Type: %s\r\n\r\n",str);
		this->flg_of_content++;
	}
}


inline void ResponseType::Redirect(char *str)
{

	printf("Location: %s \r\n\r\n",str);

}


inline void ResponseType::Expires(char *str){

	printf("Expires: %s\r\n",str);
	
}

inline void ResponseType::Header(char *title){

	printf( "<html><head>\n"
		"<title>%s</title>\n"
		"</head><body>\n",title);

}

inline void ResponseType::Header(char *title,char *bodypar)
{

	printf("<html><head>\n"
		"<title>%s</title>\n"
		"</head><body %s >\n",title,bodypar);
	
}
void ResponseType::Header(char *title,char *bodypar,char *headpar)
{
	
	printf("<html><head>\n"
	       "<title>%s</title>\n"
               "%s\n"
	       "</head><body %s >\n",title,headpar,bodypar
	       );
	
	       

}


inline void ResponseType::Footer()
{

	printf("\n</body>\n"
	       "</html>\n");

}

void ResponseType::Write(char chr){

                        if( isalnum(chr) )printf("%c",chr);

                        else switch(chr){

                        case '\"': printf("&quot;"); break;

                        case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;

                        case '>': printf("&gt;"); break;

                        case ' ': printf("&nbsp;"); break;

                        case '\r': case '\n': printf("<br>"); break;

                        default: printf("&#x%X;",(unsigned char) chr);

			}



}

void ResponseType::WriteNBR(char chr){

                        if( isalnum(chr) )printf("%c",chr);

                        else switch(chr){

                        case '\"': printf("&quot;"); break;

                        case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;

                        case '>': printf("&gt;"); break;

                        case ' ': printf("&nbsp;"); break;

                        default: printf("&#x%X;",(unsigned char) chr);

			}



}

void ResponseType::Write(char *str){

		short k;
		
		for(k = 0;str[k];k++)
		{
				
			if( isalnum(str[k]) )printf("%c",str[k]);
			
			else switch(str[k]){
			
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;
			
			case '\r': case '\n': printf("<br>"); break;
			
			default: printf("&#x%X;",(unsigned char) str[k]);
			
			}
		
		}


}

void ResponseType::WriteNBR(char *str){

		short k;
		
		for(k = 0;str[k];k++)
		{
				
			if( isalnum(str[k]) )printf("%c",str[k]);
			
			else switch(str[k]){
			
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;			
			
			default: printf("&#x%X;",(unsigned char) str[k]);
			
			}
		
		}


}

void ResponseType::Write(char *str ,char parameter)
{
	short k;
		
	if(parameter)
		
		for(k = 0;str[k];k++)
		{
				
			if( isalnum(str[k]) )printf("%c",str[k]);
		
			else switch(str[k]){
			
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;
			
			case '\r': case '\n': printf("<br>"); break;
					
			default: printf("&#x%X;",(unsigned char) str[k]);
		
			}
		}
	
	else printf("%s",str);
	
}

bool ResponseType::FileOutput(char *fname){

	FILE *fp;
	
	fp = fopen(fname,"r");
	
	if( fp == NULL ){
		fclose(fp);
		return 0;
	}
		
	int chr;
	
				
		
	while( ( chr = fgetc(fp) ) != EOF ){
		
		if( isalnum(chr) )printf("%c",chr);
		
		else switch(chr){
			
		case '\"': printf("&quot;"); break;
			
		case '&': printf("&amp;"); break;
			
		case '<': printf("&lt;"); break;
			
		case '>': printf("&gt;"); break;
			
		case ' ': printf("&nbsp;"); break;
			
		case '\r': case '\n': printf("<br>"); break;
		
		default: printf("&#x%X;",(unsigned char) chr);
		
		}

			
	}
	 		
	fclose(fp);
	return 1;
}

bool ResponseType::FileOutput(char *fname, char parameter){
		
	FILE *fp;
	
	fp = fopen(fname,"r");
	
	if( fp == NULL ){
		fclose(fp);
		return 0;
	}
		
	int chr;
	
	if(parameter){			
		
		while( ( chr = fgetc(fp) ) != EOF ){
		
			if( isalnum(chr) )printf("%c",chr);
		
			else switch(chr){
			
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;
			
			case '\r': case '\n': printf("<br>"); break;
		
			default: printf("&#x%X;",(unsigned char) chr);
		
			}

			
		}
	 		
	}else{
				
		while( (chr = fgetc(fp) ) != EOF )			
			printf("%c",(unsigned char) chr);		
	}

	fclose(fp);
	return 1;
}

inline void ResponseType::Script(char *lng, char *script){
	
	printf("<script language=\"%s\">\n%s\n</script>",lng, script);

}

inline void ResponseType::Script(char *lng, char *script, char *parameter){
	
	printf("<script language=\"%s\" %s>\n%s\n</script>",lng, parameter, script);
	
}

inline void ResponseType::Cookie(char *name,char *value){

	printf("Set-Cookie: %s=%s;\r\n",name,value);

}

inline void ResponseType::Cookie(char *name,int value){

	printf("Set-Cookie: %s=%d;\r\n",name,value);
	
}

inline void ResponseType::Cookie(char *name, char *value, char *param)
{
	
	printf("Set-Cookie: %s=%s; %s\r\n",name,value,param);
			
}

inline void ResponseType::Cookie(char *name, int value, char *param){

	printf("Set-Cookie: %s=%d; %s\r\n",name,value,param);

}

bool ResponseType::CmdOutput(char *command){

	FILE *pp;
	
	pp = popen(command, "r");
	
	if( pp == NULL ){
		pclose(pp);
		return 0;
	}
	
	int chr;				
		
	while( ( chr = fgetc(pp) ) != EOF ){
		
		if( isalnum(chr) )printf("%c",chr);
		
		else switch(chr){
			
		case '\"': printf("&quot;"); break;
			
		case '&': printf("&amp;"); break;
			
		case '<': printf("&lt;"); break;
			
		case '>': printf("&gt;"); break;
			
		case ' ': printf("&nbsp;"); break;
			
		case '\r': case '\n': printf("<br>"); break;
		
		default: printf("&#x%X;",(unsigned char) chr);
		
		}

			
	}
	
	pclose(pp);
	return 1;	

}

bool ResponseType::CmdOutput(char *command, char parameters){

	FILE *pp;
	
	pp = popen(command, "r");
	
	if( pp == NULL ){
		pclose(pp);
		return 0;
	}
	
	int chr;				
	
	if(parameters){
		
		while( ( chr = fgetc(pp) ) != EOF ){
			
			if( isalnum(chr) )printf("%c",(unsigned char)chr);
			
			else switch(chr){
				
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;
			
			case '\r': case '\n': printf("<br>"); break;
		
			default: printf("&#x%X;",(unsigned char) chr);
		
			}

			
		}
	
	}else{
				
		while( (chr = fgetc(pp) ) != EOF )			
			printf("%c",(unsigned char) chr);		
	}

	pclose(pp);
	return 1;	

}

#ifdef __POSIX__

void ResponseType::URLOutput(char *url)
{
	
	struct sockaddr_in srvr;
	
	char *path, *site, *tmpp;
	short int port;
	int s;
	int i;
	
	FILE *fp;
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	
	if( s == -1){
		printf("error: socket(2)");
		return;
	}
	
	memset(&srvr, 0, sizeof srvr);
		
	/* find domain name for http protocol */
	
	if( !strncmp(url, "http://", 7 /*len of http:// string */) ){
		
		url += 7;
		
		i = 0;
		site = url; // for temp usage
		while( *site != '/') {
			site++;
			i++;
		}
		
		site = (char *)malloc(sizeof(char)*i + 1/*for null*/);
		
		if(url == NULL ){
			printf("Not enough memory<br>\n");
			return;
		}
		
		memset(site, 0, i + 1);
		
		strncat(site, url, i);// inserting site name
		
		path = url + i;// inserting path name
				
		if( (tmpp = strrchr(site, ':')) != NULL ) {
			
			tmpp++;
			port = strtol(tmpp, NULL, 10);// inserting port number
						
			tmpp--;
			*tmpp = 0; // redefined our site name
		} else {
			port = 80;
		}
		
		tmpp = (char *)malloc(sizeof(char) * strlen(site) + 1 ); // for ipv4 parse usage
		
		if( tmpp == NULL) {
			printf("Not enough memory<br>\n");
			return;
		}
		
		/* ipv4 name resoluation */
		
		strcpy(tmpp, site);
		
		i = 0;
		while( *tmpp != '\0' ){
			
			if(isdigit(*tmpp)){
				tmpp++;
				continue;
			}else if( *tmpp == '.'){
				i++;
				tmpp++;
			}else {
				i = 0;
				break;
			}			
		}
		
		if( i != 3 ){ // Domain resolution
				
				struct hostent *hstent;
				
				if( !( hstent = gethostbyname(site)) ){
					printf("error: gethostbyname(3)");
					return;
				}
				
				srvr.sin_addr = * (struct in_addr *)hstent->h_addr_list[0];
				//srvr.sin_addr = *host_addr;//inet_addr(site);
				
		}else{ 
			srvr.sin_addr.s_addr = inet_addr(site);			
		}
		
		srvr.sin_family = AF_INET;
		srvr.sin_port = htons(port);
		
		if( srvr.sin_addr.s_addr == INADDR_NONE ){
			printf("Wrong domain");
			return;
		}
				
		tmpp = (char *)malloc(sizeof(char) * 
					strlen(path) + 
					3   /* GET /     */ + 
					1  /* 1 x SPACE */ +
					//8 /* HTTP/1.1  */+
					1/* NULL      */ );
		
		strcpy(tmpp, "GET ");
		strcat(tmpp, path);
		//strcat(tmpp, " HTTP/1.1");
		
		path = tmpp; // finish out path parameters
		
						
		connect(s, (struct sockaddr *)&srvr, sizeof srvr);
			
		write(s, path, strlen(path)+1);
		//write(s, "\r\n",2 );
		//write(s, "host: www.cgimarket.com", 23);
		write(s,"\r\n\r\n", 4);
		
		shutdown(s, SHUT_WR);
				
		fp = fdopen(s, "r");
		
		int ch;
		
		while( (ch = fgetc(fp)) != EOF ){
			printf("%c", (char)ch);
			fflush(fp);
		}
			
	}/* http */	
	
	fclose(fp);
	close(s);
	
}

#endif /* __POSIX__ */

ResponseType::~ResponseType()
{
	//printf("\n<!-- www.CGIMarket.com -->");
	fflush(stdout);
}


  /////////////////////////////////////////
 // This line declines RequestType Class//
/////////////////////////////////////////

class RequestType
{
	char *std;
	unsigned int lengthofstr;
	char type;
	
	public:
	RequestType();
 	
	
	
	char *ServerVariables(char *str);
	char *QueryString();
	char *QueryString(char *str);
	char *Cookie(char *str);
	char *Form();
	char *Form(char *str);
	char *FileString(char *fname);

	char *CmdString(char *cmd);//Daha yazilmadi
			
}Request;



RequestType::RequestType()
{	

	char *str;
	
		
	if( ( str = getenv("REQUEST_METHOD") ) == NULL)
		std = NULL;
	
	else
	{
		if(!strcmp(str,"POST"))
		{
			lengthofstr = atoi(getenv("CONTENT_LENGTH"));
			std = (char*)malloc(sizeof(char) * lengthofstr + 1);
			fgets(std, lengthofstr + 1, stdin);
			type = POST;
		}
		else if(!strcmp(str, "GET")){
			std = getenv("QUERY_STRING");
			lengthofstr = strlen(std);
			type = GET;
			}	
		else{ std = NULL; type = UNKNOWN; lengthofstr = 0; }
	}
		
			
}


char* RequestType::ServerVariables(char *str)
{
	char *var;
	
	var = getenv(str);
	 
	 if( var == NULL)
	 	return NULL;
	 	
	 return var;

	
}

char* RequestType::QueryString(){

	if( type != GET )
		return NULL;
			
	return std;

}

char* RequestType::QueryString(char *str)
{
	char *string = std;
	char *stringType;
	
	if( type != GET )
		return NULL;	
	
	if( !(stringType = (char*) malloc( sizeof(char) * lengthofstr +1 )) )
	{
		printf("Request.QueryString:not enough memory to decode\n");
		exit(1);
	}
	
	if(string == NULL)
		return NULL;

	short k;			
		
	for(;;)
	{
		/*B 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		k = 0;
		while(*string != '=' && *string != '\0')
		{	
				
			stringType[k] = *string;
			k++;string++;		
		
		}
		stringType[k] = '\0';	
		if(*string == '&')
			string++;
		
		/*E 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		
		
		
		/*B
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/
		if(!strcmp(str, stringType))
		{	
			k = 0;
			while(*string != '&' && *string != '\0' )
			{
				string++;
				stringType[k] = *string;
				k++;
			}
			--k;
			stringType[k] = '\0';
			
		return Translate.Decode(stringType);
		}
		/*E
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/

		if(*string == '\0')
			return NULL;
		
		while(*string != '&' && *string != '\0')
			string++;
		
		if(*string == '&')
			string++;
			
		else if(*string == '\0')
			return NULL;
	}			
}


char *RequestType::Cookie(char *str)
{

	char *string = getenv("HTTP_COOKIE");
	char *stringType;

	if(string == NULL)
		return NULL;

	
	if(!(stringType = (char*) malloc( sizeof(char)* strlen(getenv("HTTP_COOKIE")) + 1 )))
	{
		printf("Request.Cookie:not enough memory to decode\n");
		exit(1);
	}
	
	
	short k;			
		
	for(;;)
	{
		/*B 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		k = 0;
		while(*string != '=' && *string != '\0')
		{	
				
			stringType[k] = *string;
			k++;string++;		
		
		}
		stringType[k] = '\0';	
		if(*string == ';')
		{
			
			string++;string++;
			
		}
		/*E 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		
		
		
		/*B
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/
		if(!strcmp(str, stringType))
		{	
			k = 0;
			while(*string != ';' && *string != '\0' )
			{
				string++;
				stringType[k] = *string;
				k++;
			}
			--k;
			stringType[k] = '\0';
			
		return Translate.Decode(stringType);
		}
		/*E
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/

		if(*string == '\0')
			return NULL;
		
		while(*string != ';' && *string != '\0')
			string++;
		
		if(*string == ';')
		{
			
			string++;string++;
			
		}else if(*string == '\0')
			return NULL;
	}			
}

char *RequestType::Form(){
	
	return std;
		
}


char *RequestType::Form(char *str)
{
	char *string = std;
	char *stringType;
  
  	if(!(stringType = (char*) malloc( sizeof(char)* lengthofstr + 1 )))
	{
		cout <<"There is not enough memory to Decode your POST\n";
		exit(1);
	}

  	if(string == NULL)
  		return string = NULL;
  		
	unsigned long int k;			
		
	for(;;)
	{
		/*B 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		k = 0;
		while(*string != '=' && *string != '\0')
		{	
				
			stringType[k] = *string;
			k++;string++;		
		
		}
		stringType[k] = '\0';	
		if(*string == '&')
			string++;
		
		/*E 
		Bu hat degiskenin 
		adini ortaya çikarmaktadir*/
		
		
		
		/*B
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/
		if(!strcmp(str, stringType))
		{	
			k = 0;
			while(*string != '&' && *string != '\0' )
			{
				string++;
				stringType[k] = *string;
				k++;
			}
			--k;
			stringType[k] = '\0';
			
		return Translate.Decode(stringType);
		}
		/*E
		Eger degisken dogru ise bu 
		hat uzerinde kotrolu yapimaktadir*/

		if(*string == '\0')
			return NULL;
		
		while(*string != '&' && *string != '\0')
			string++;
		
		if(*string == '&')
			string++;
		else if(*string == '\0')
			return NULL;
	}				
	
}

char *RequestType::FileString(char *fname){

	char *str;	
	FILE *fp;
	
#ifdef __POSIX__
		
		/* This MACRO is for file memory allocate with POSIX standard */
		
		struct stat statbuf;
		
		stat(fname,&statbuf);
		
		str = (char *) malloc(sizeof(char) * statbuf.st_size + 1);
		
		if( str == NULL )
			return NULL;
		
		*str = '\0'; // for strcat function to start point
		
#else
		/* With ANSI/ISO compute for mem allocate */
		
		fp = fopen(fname, "r");
		
		if( fname == NULL ){
			fclose(fp);
			return NULL;
		}
		
		int k = 0;
		
		while( fgetc(fp) != EOF )
			k++;
		
		str = (char *) malloc(sizeof(char) * k  + 1);
				
		k = 0;
		
		if( str == NULL )
			return NULL;
		
		str = '\0'; // for strcat function to start point	
#endif
	
	fp = fopen(fname,"r");
	
	if( fp == NULL ){
		fclose(fp);
		return NULL;
	}
		
	int chr;
			
	char str2[1];
		
	while( (chr = fgetc(fp) ) != EOF ){		
		
		str2[0] = (char)chr;
		
		str2[1] = '\0';
		
		strcat(str, str2);
	 
	 }
	 
	fclose(fp);
	return str;
}


class LocalType{
	
	private:
	char *memfile;
	unsigned int lengthofstr;
	FILE *file;
	//
	int filelength;
	
	public:
	
	LocalType(char *filename);
	~LocalType(){fclose(file);};
	char *QueryString(char *str);
	

};


LocalType::LocalType(char *filename){

	int ctrlc;
	unsigned long int ctrl = 0;
	
	file = fopen(filename,"r");
	
	if(file == NULL){
		memfile == NULL;
		return;
	}
	/* control for this point for counting your number of character from file */
	
	while( (ctrlc = fgetc(file)) != EOF){
		
		if(ctrlc == '#'){
			while( (ctrlc = fgetc(file)) != EOF){
				if(ctrlc == '\n')
					break;
			}	
		}
		if(ctrlc == EOF)
			break;

		++ctrl;		
	}
	rewind(file);
	
	/* memfile settign in this location */
	
	memfile = (char *)malloc( sizeof(char)*ctrl + 1 );
	
	ctrl = 0;//ctrl usage for memfile's segment indexing
	
	while( (ctrlc = fgetc(file)) != EOF){
		
		/* control of # */
		
		if(ctrlc == '#'){
			while( (ctrlc = fgetc(file)) != EOF){
				if(ctrlc == '\n'){
					break;
				}
				
				if(ctrlc == EOF)
					break;

				//continue;
			}
		}
		
		if(ctrlc == EOF){
			break;
		}
		memfile[ctrl] = (unsigned char)ctrlc;
		++ctrl;
		
	}
	memfile[ctrl]='\0';	
	//printf("%s",memfile);
	lengthofstr = strlen(memfile);
}

char *LocalType::QueryString(char *str){

	char *memrec;
	unsigned int ctrl = 0, ctrl2 = 0;
	
	if(memfile == NULL)
		return NULL;

	memrec = (char *)malloc( sizeof(char)*lengthofstr + 1 );
	ctrl = 0;			
	ctrl2 = 0;
	for(;;){
	
		while(memfile[ctrl] != ':' &&  memfile[ctrl] != '\0'){
			ctrl++;
		}
			
		if(memfile[ctrl] == '\0')
			return NULL;

		ctrl++;
		
		ctrl2 = 0;
		while(memfile[ctrl] != '\n' && memfile[ctrl] != '\0' && memfile[ctrl] != ' '){
			memrec[ctrl2] = memfile[ctrl];
			ctrl++;ctrl2++;
		}
		memrec[ctrl2] = '\0';
		
		if(memfile[ctrl] == '\n')
			ctrl++;
		if(memfile[ctrl] == '\0')
			return NULL;
	
		if(!strcmp(str,memrec)){
			ctrl2 = 0;
			while(memfile[ctrl] != '\0'){
				
				if(memfile[ctrl] == '\n'){
					++ctrl;
					if(memfile[ctrl] == ':')
						break;
					else --ctrl;
				}
				
				memrec[ctrl2] = memfile[ctrl];
				ctrl++;ctrl2++;
			}
			if(memrec[ctrl2 -1] == '\n'){
				memrec[ctrl2 -1] = '\0';
				return memrec;
			}
			memrec[ctrl2] = '\0';
			
			return memrec;
		}
			
	}
}

class ParserType{
	
	private:
	char *p_str;
	
	public:
	
	ParserType(char *str);
};

ParserType::ParserType(char *str){

	char *str2;
	unsigned int i = 0;
	unsigned int i2 = 0;
	
	for(;;){
		
		while( str[i] != '\0'){
			
			if(str[i] == '%'){
				
				++i;
				
				i2 = 0;
				while(str[i] != '\0' && str[i] != ' '){
					
					str2[i2] = str[i];
					i++;
					i2++;
					
				}
			}
			
			
		}
	}
}

#endif /* _CGILIB_H_ */
