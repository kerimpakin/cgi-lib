/*****************************************************************\
 * Author: Kerim BASOL						 *
 * Nick Name: CPU_Kerim or C++					 *
 * ICQ:97683818							 *
 * Written Date: November/08/1998				 *
 * This header file writen by Kerim BASOL for WebDevelopers.	 *
 * If you want to change You must protect my name in sourde file *
 * 								 *
 * Mail1:kkbasol@hotmail.com					 *
 * Mail2:kkbasol@netscape.net					 *
 * Author's sites:						 *
 * 								 *
 * Site1:http://www.CGIMarket.com				 *
 * Site2:http://www.proweb2001.com				 *
 * 								 *
 * This software protected under GNU Licence			 *
\*****************************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
//#include "cgiout.hh"
using namespace std;

/* These macros are for REQUEST_METHOD type*/

#define UNKNOWN 0
#define POST 1
#define GET 2

/* These macros are for CONTENT_TYPE (Response.Write("",PLAIN) ) */
#define PLAIN 0
#define HTML 1



/* This extern value is for environtment */

//extern char **environ;

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
		printf("%s<br/>",*p++);
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

  //////////////////////////////////////////
 // This line declines ResponseType Class//
//////////////////////////////////////////

class ResponseType
{
	
	
	public:
	
	void ContentType(char *str);
	void Redirect(char *str);
	void Expires(char *str);
	void Header(char *title);
	void Header(char *title,char *bodypar);
	void Header(char *title,char *bodypar,char *headpar);
	void Footer();
	void Write(char *str);
	void Write(char *str,char parameter);
	void Cookie(char *name,int value);
	void Cookie(char *name,char *value);
	void Cookie(char *name, char *value, char *param);
	void Cookie(char *name, int value, char *param);
	~ResponseType();
}Response;

inline void ResponseType::ContentType(char *str)
{

	printf("Content-Type: %s\r\n\r\n",str);

}


inline void ResponseType::Redirect(char *str)
{

	printf("Location: %s \r\n\r\n",str);

}


inline void ResponseType::Expires(char *str){

	printf("Expires: %s\r\n",str);
	
}

inline void ResponseType::Header(char *title){

	printf( "<html>\n"
		"<head>\n"
		"<title>%s</title>\n"
		"</head>\n"
		"<body>\n",title);

}

inline void ResponseType::Header(char *title,char *bodypar)
{

	printf("<html>\n"
		"<head>\n"
		"<title>%s</title>\n"
		"</head>\n"
		"<body %s >\n",title,bodypar);
	
}
void ResponseType::Header(char *title,char *bodypar,char *headpar)
{
	
	printf("<html>\n"
	       "<head>\n"
	       "<title>%s</title>\n"
               "%s\n"
	       "</head>\n"
	       "<body %s >\n",title,headpar,bodypar
	       );
	
	       

}


inline void ResponseType::Footer()
{

	printf("\n</body>\n"
	       "</html>\n");

}

void ResponseType::Write(char *str){

		short k;
		
		for(k = 0;str[k];k++)
		{
				
			if( isalnum(str[k]) )printf("%c",str[k]);
		
			else if(str[k] == '\x20')printf("&nbsp;");
		
			else if(str[k] == '\n' || str[k] == '\r')printf("<br/>\n");
		
			else printf("&#x%X;",(unsigned char) str[k]);
		
		}


}

void ResponseType::Write(char *str ,char parameter)
{
	short k;
		
	if(parameter)
		
		for(k = 0;str[k];k++)
		{
				
			if( isalnum(str[k]) )printf("%c",str[k]);
		
			else if(str[k] == '\x20')printf("&nbsp;");
		
			else if(str[k] == '\n' || str[k] == '\r')printf("<br/>\n");
		
			else printf("&#x%X;",(unsigned char) str[k]);
		
		}
	
	else printf("%s",str);
	
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

ResponseType::~ResponseType()
{
	printf("\n<!-- www.CGIMarket.com -->");
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
	char *QueryString(char *str);
	char *Cookie(char *str);
	char *Form(char *str);
	
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

	 if(getenv(str) == NULL)
	 	return NULL;
	 	
	 return getenv(str);

	
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
			
		return stringType;
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
			
		return stringType;
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
  		return string = 0;
  		
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
			
		return stringType;
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
	
	unsigned int k;	/*It can loop only value from 0 to 4000000000 
			 	  this means is you can decode value from
			  	  only 0 to 4000000000*/
	
	
	
	
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
	++i;str2[i] = '\0';
	
	str = str2;
	return str;
}

class LocalType{
	
	private:
	char *memfile;
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
		
	/* control for this point for counting your number of character from file */
	
	while( (ctrlc = fgetc(file)) != EOF){
	
		if(ctrlc == '#'){
			while( (ctrlc = fgetc(file)) != EOF){
				if(ctrlc == '\n')
					break;
			}	
			
			continue;
		}
		ctrl++;		
	}
	rewind(file);
	
	/* memfile settign in this location */
	
	memfile = (char *)malloc( sizeof(char)*ctrl + 1 );
	
	ctrl=0;//ctrl usage for segment indexing
	
	while( (ctrlc = fgetc(file)) != EOF){
		
		if(ctrlc == '#'){
			while( (ctrlc = fgetc(file)) != EOF){
				if(ctrlc == '\n')
					break;
			}
			continue;
		}
		
		memfile[ctrl] = (unsigned char)ctrlc;
		++ctrl;
	}
	memfile[ctrl]='\0';	
	
		
	
}


char *LocalType::QueryString(char *str){

	printf("%s",memfile);
	return str;

}

