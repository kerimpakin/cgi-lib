#ifndef _PARS_H_
#define _PARS_H_ 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <cgilib.hh>

static char* cenviron = "";

#ifdef __cplusplus
extern "C"{
#endif

int strstrlen(char *s, char *query){
	
	int i = 0;
	int len = strlen(query);
	
	while( strncmp(s, query, len) && s != NULL){
		i++;
		s++;
	}
	
	return i;
}

void parse_insert_variable(char *varname, char *variable)
{
	#define NULL_LEN 1
	#define EQUAL_SIGN 1
	#define AMP_LEN 1
	
	int str_len = strlen(variable) * 3 + 1;
	char *tmpp = (char*) malloc( sizeof(char) * str_len ); //temprory pointer
	char *str2Seg = tmpp;
	
	
	unsigned int k;
	unsigned int i;
	
	for(k = 0,i = 0; variable[k]; k++,i++,str2Seg++)
	{
		if( variable[k] != '=' && variable[k] != '&'  && variable[k] != '%' ){
			tmpp[i] = variable[k];
			continue;
		} else {
			
			tmpp[i] = '%';++str2Seg;++i;
			sprintf(str2Seg,"%X",variable[k]);++str2Seg;++i;
			continue;			
			
		}
		
			
		
	}
	tmpp[i] = '\0';
	variable = tmpp;
	
	/* Building our query variable*/
	
	str_len = sizeof(char) * strlen(varname) + NULL_LEN + EQUAL_SIGN;
	
	char *query = (char *) malloc( str_len );
	
	memset(query, 0,  str_len);
	
	strcat(query, varname);
	
	strcat(query, "=");
	
	char *new_variable;
	
	
	int variable_len = strlen(variable) + strlen(query);
	
	
	
	if( !( tmpp = strstr(cenviron, query) ) ) {
	//eger elimizde o deger yok ise
		
		str_len = strlen(cenviron);
		
		new_variable = (char *)malloc(sizeof(char) * ( str_len + variable_len + NULL_LEN + AMP_LEN ) );
		
		if( new_variable == NULL ){
			printf("not enough memory\n");
			abort();
		}
		
		strcpy(new_variable, cenviron);
		
		if( strcmp(cenviron, "") )
			strcat(new_variable, "&");
		
		strcat(new_variable, query);
		strcat(new_variable, variable);
		
	} else {
		
		tmpp = strchr(tmpp,'=');tmpp++;//jumping from '=' sign
			
		int first_len = strstrlen(cenviron, query);
			
		int last_len = strlen( (tmpp = strchr(tmpp,'&')) );
	
		new_variable = (char *) malloc(sizeof(char) * (first_len + variable_len + last_len + NULL_LEN ) );
		
		if( new_variable == NULL ){
			printf("not enough memory\n");
			abort();
		}
		
		strncpy(new_variable, cenviron, first_len);	
		strcat(new_variable, query);
		strcat(new_variable, variable);	
		strcat(new_variable, tmpp);
	
	}
	
	//Bu bolumde cenviron u bosaltmak icin bir bellek cozumu gelirse
	//daha iyi olur
	
	/*
		sorun bir garbage collection olusturulmali ki
		burada her yeni gelen deger icin eski bellektekiler
		bellekte kalmasin
	*/		
	cenviron = new_variable;
	
}

char *parse_request_variable(char *str)
{
	
	char *string = cenviron;
	char *stringType;

	if(string == NULL)
		return NULL;
	
	int str_len = strlen(cenviron);
	
	if(!(stringType = (char*) malloc( sizeof(char)* str_len + 1 )))
	{
		printf("error: not enough memory to decode\n");
		exit(1);
	}
	
	memset(stringType, 0, str_len);
	
	int k;			
		
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
		
			str = stringType;	
		
			char *str2;
			
			char number[3];
		
			number[2] = '\0';
					
				
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
			
			str2 = str;
			
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
					
				//else if(*str == '+'){str2[k] = ' ';}
				
				else str2[k] = *str; 
				
				if(*str == '\0'){str2[k] = '\0';break;}
			}
	
			return str2;
			
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
	
	return NULL;

}



#ifdef __cplusplus
}
#endif

#endif /* _PARS_H_ */

