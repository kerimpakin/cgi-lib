/*****************************************************************\
 * Author: Kerim BASOL						 *
 * Nick Name: CPU_Kerim or C++ or GTK+				 *
 * ICQ:NA							 *
 * Written Date: November/08/1998				 *
 * This header file writen by Kerim BASOL for WebDevelopers.	 *
 * If you want to change You must protect my name in sourde file *
 * Mail: kerim@math.com						 *
 * Mail1:kkbasol@hotmail.com					 *
 * Mail2:kkbasol@netscape.net					 *
 * Author's sites:						 *
 * 								 *
 * Site:http://www.CGIMarket.com				 *
 *				 				 *
 * 								 *
 * These headers protected under GNU Licence			 *
\*****************************************************************/

#include "/root/cgi-lib/cgilib.hh"
#include "/root/cgi-lib/cgiout.hh"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
using namespace std;



class MultiPart{
	
	#define ARRAY_SIZE 300     /*You can change the array size 
				    * for your usage of file number
				    */
	
	char *name[ARRAY_SIZE];	   /* name string array 
				    * from content-disposition
		        	    */
	
	char *filename[ARRAY_SIZE];/* filename string array
			 	    * from content-disposition
			 	    */
	
	char *data[ARRAY_SIZE];	   /* data is being used by only
			 	    * fgets function for file proess
			 	    */
	
	char *content[ARRAY_SIZE]; /* content value is being used for
			 	    * content-type control if a
			 	    * content has a content-type
			 	    */
	
	char tempfile[ARRAY_SIZE][FILENAME_MAX];/* this value is being used by 
			 	    * tmpnam function for tempror
			 	    * file usage
			 	    */
	
	FILE *fp[ARRAY_SIZE];	   	   /* this file pointer array(string array)
			 	    * is using
			 	    * for temprory usage
			 	    */
	
	int cgindex;	/* This value is for global cgindex 
			 * changing by other functions
			 * for increment of name,filename,
			 * content,tempfile
			 */
	
	int cgierr;	/* when an error occured 
			 * the value is different then 0 
			 * this value shows how many error occured
			 * using in bail function
			 */
	
	int lenOfVar;	/* variable length
			 * this value only changing in constructor
			 */
	
	/*
	 * Note: every neccesary variable
	 * is setting 0 in contructor
	 * cgindex,cgierr,lenOfVar
	 * tempfile[lenOfVar],fp[lenOfVar] are setting NULL
	 */
	
	void bail(char *what_on,int line){// error reporting function
		
		printf( "Content-Type: text/plain\r\n\r\n"
			"error: %s\n"
			"file: %s\n"
			"line: %i\n"
			"written by Kerim BASOL\n"
			,(char*)what_on,__FILE__,(int)line
			);
	
		cgierr++;//for error control other functions
	}
				
	public:
	
	MultiPart();
	~MultiPart();// closing our files and removing temprory files
	
	/* our methods for handel of cgi */
	
	char *getFileNamebyName(char *namef);
	char *getFileNamebyContentType(char *namef);
	char *getFileNamebyArray(int array);
	
	FILE *getFilebyFileName(char *filenamef);
	FILE *getFilebyName(char *namef);
	FILE *getFilebyArray(int array);
	FILE *getFilebyContentType(char *contentf);
			
	FILE *getNextFile();
	char *getNextFileName();
	char *getNextContentType();
	char *getNextName();
	
	char *getFileName();
	char *getContentType();
	FILE *getFile();
	char *getName();
	
	int arrayLength();
	
	/* Temprory method decleration */
	
	char *getTempFileName(int array);

};

MultiPart::MultiPart(){//contructor
		
	#define BUF_SIZE 1024 //this variable buffer sizeof datacnt for pike(in turkish) method
	#define CONTENT_TYPE "CONTENT_TYPE"
	#define CONTENT_DISPOSITION "Content-Disposition:"
		
	char datacnt[BUF_SIZE];
	unsigned short int i;
	
	/* setting up default variables */
	
	cgindex = 0;
	cgierr = 0;
	lenOfVar = 0;
				
	#ifdef TEST	
	Response.ContentType("text/plain");
	#endif
	
	char *env = getenv(CONTENT_TYPE);
	
	if(env == NULL){
		bail("content-type",__LINE__);
		return;	
	}
	
	if( strstr(env, "multipart/form-data;" ) == NULL){
		printf("not multipart form data!\n"
			"Usage: <form method=POST action:\"/cgi-bin/exec.cgi\" ENCTYPE=\"multipart/form-data\">\n");
		return;
	}

	char *cntlen = getenv("CONTENT_LENGTH"); // This variable for data length
	
	if( cntlen == NULL ){
		bail("not enough memory",__LINE__);
		return;	
	}
	unsigned int len = strtoul(cntlen, NULL, 10) + 1 ;//how much memory will we use
	
	/* allocating memory */
	
	char *data = (char*) calloc(len, sizeof(char) );
	char *cnt;	
	
	free(cntlen);//freeing the memory of cntlen
			
		
	/* Getting the header of the content for the correct type of header */
		
	for(;;){
	
		i = 0;
				
		cnt = (char*) calloc(len, sizeof(char) );
		
		fgets(cnt, len, stdin);	
			
		if( cnt == NULL ){
			bail("content",__LINE__);
			return;
		}
		
		
		
		/* Content control of the header */	
		
		if( strncmp(cnt, CONTENT_DISPOSITION, 20) ){		
			bail("content-disposition",__LINE__);
			return;
		}
			
			
			
		/* Name of the "name" parameter */
		
		cnt = strpbrk(cnt,"\"");
			
		if( cnt == NULL){		
			bail("\"name\" paramter",__LINE__);
			return;		
		}
			
		cnt++;//jumping from '\"' character
					
		i = 0;
		while( *cnt != '\0' && *cnt != '\"' ){
				
			datacnt[i] = *cnt;
			cnt++;i++;
			
		}
		datacnt[i] = '\0';//name value
			
				
			/*Copying the name value */
			
			name[lenOfVar] = (char*)malloc( (sizeof(char) * i) + 1 ); 
			
			if( !(name[lenOfVar]) ){
				bail("not enough memory for name",__LINE__);
				return;
			}
			
			strcpy(name[lenOfVar], datacnt);
			
		
		#ifdef TEST			
		printf("name:\"%s\"\n",datacnt);
		#endif
		
				
		/* Parsing the "filename" parameter */
			
			
		cnt++;//jump from '\"' character
		
			
		/* resolving the filename value */
				
		if( strstr(cnt,"filename") != NULL ){//If we have filename parameter
				
			cnt = strpbrk(cnt,"\"");	
			cnt++;//jump from '\"' character
						
			i = 0;//reset the cgindex value
			while( *cnt != '\0' && *cnt != '\"' /*&& i != 254*/ ){
					
				datacnt[i] = *cnt;
				cnt++;i++;
			}
			datacnt[i] = '\0';//filename value
				
				/* copying the filename */
					
				filename[lenOfVar] = (char*)malloc( sizeof(char) * i + 1 );
			
				if( !(filename[lenOfVar]) ){
					bail("not enough memory for filename parameter",__LINE__);
					return;
				}
				
				strcpy(filename[lenOfVar],datacnt);
				
					
			#ifdef TEST
			printf("filename:\"%s\"\n",datacnt);
			#endif
		}else{
			filename[lenOfVar] = NULL;//If we have no filename parameter set NULL
			
		}
		
		fgets(cnt, len, stdin);
			
		if( strstr(cnt,"Content-Type:") ){//If we have known type of content
			
			cnt = strpbrk(cnt," ");//jumping to whitespace
			cnt++;//jump from ' ' characters
			
			i = 0;
			while( *cnt != '\0' && *cnt != '\"' ){
				
				datacnt[i] = *cnt;
				i++;
				cnt++;
				
			}
			datacnt[i] = '\0';//content value
				
				/* copying the content */
				
				content[lenOfVar] = (char*) malloc( (sizeof(char) * i ) + 1);
				
				if( !(content[lenOfVar]) ){
					bail("not enough memory for content",__LINE__);
					return;
				}
				
				strcpy(content[lenOfVar], datacnt);
				
								
			#ifdef TEST
			printf("Content-Type: %s",datacnt);
			#endif
			
			fgets(cnt, len,stdin);//This function for <CR><LF>
		}
		
		else content[lenOfVar] = NULL;
							
		/* Parsing content "boundary" */
		
		cnt = getenv("CONTENT_TYPE");
		
		cnt = strpbrk(cnt, "=");
			
		cnt++;//jump from '=' character
			
		i = 2;
		while(*cnt != '\0' ){
			datacnt[i] = *cnt;
			cnt++;i++;
		}
		datacnt[0] = '-'; 
		datacnt[1] = '-';//Setting up firt two array for adding http multi
			
		datacnt[i] = '\0';
		
		#ifdef TEST
		printf("boundary: \"%s\"\n",datacnt);
		#endif								
				
		/* Upload section for the file */
							
			tmpnam(tempfile[lenOfVar]);
			
			if( !tempfile[lenOfVar] ){
				bail("tmpnam(2)",__LINE__);
				return;
			}
						
			if( !(fp[lenOfVar] = fopen(tempfile[lenOfVar],"w+b") ) ){
				bail("fopen(2)",__LINE__);
				return;
			}
			
		#ifdef TEST
		printf("file: %s opened\n",tempfile[lenOfVar]);					
		#endif
		
		for(;;){			
									
				fgets(data, len, stdin);
					
				if( data == NULL )
					break;
						
				if( !strncmp(data, datacnt,strlen(datacnt)) )
					break;
									
				fprintf(fp[lenOfVar], "%s",data);
				
				#ifdef TEST
				//printf(data);
				#endif					
					
		}
				
		fclose(fp[lenOfVar]);
		
		//rewind(fp[lenOfVar]);
			
		datacnt[i] = '-';// null converted to '-'
		i++;
		datacnt[i] = '-';
		i++;
		datacnt[i] = '\0';
						
		/* setting up for next loop */
		
		if( lenOfVar >= ARRAY_SIZE)//break the loop if file number is equal loop
			break;
		
		lenOfVar++;//icrementing for how many forms uploaded
		
		
		name[lenOfVar] = NULL;
								
		if( !strncmp(data, datacnt,strlen(datacnt)) )
			break;
	
		
	}
	
	
			
	#ifdef TEST
	printf("final boundary: \"%s\"\n",datacnt);
	#endif
	
}


MultiPart::~MultiPart(){
	
	#ifdef TEST
	printf("destructor\n");
	#endif
	
	int i = 0;
	
}

FILE *MultiPart::getFilebyName(char *nameof){

	if( cgierr != 0 )
		return NULL;
	
	int i = cgindex;
	
	cgindex = 0;
			
	do{		
		if( !strcmp(name[cgindex], nameof) ){
			return fp[cgindex];
		}
				
		cgindex++;
		
	}while( cgindex <= lenOfVar );
	
	cgindex = i;//when getFile function doesn't find anything resets the value of cgindex
	
	return NULL;


}

FILE *MultiPart::getFilebyFileName(char *filenamef){
	
	if( cgierr != 0 )
		return NULL;
	
	int i = cgindex;
	
	cgindex = 0;
			
	do{		
		if( !strcmp(filename[cgindex], filenamef) ){
			return fp[cgindex];
		}
		
		cgindex++;
		
	}while( cgindex <= lenOfVar );
	
	cgindex = i;//when getFile function doesn't find anything resets the value of cgindex
	
	return NULL;
}


FILE *MultiPart::getFilebyArray(int array){

	if( cgierr != 0 )
		return NULL;
	
	int i = cgindex;
	
	cgindex = 0;
			
	do{		
		if( cgindex == array ){
			return fp[cgindex];
		}
		
		cgindex++;
		
	}while( cgindex <= lenOfVar );
	
	cgindex = i;//when getFile function doesn't find anything resets the value of cgindex
	
	return NULL;

}

FILE *MultiPart::getFilebyContentType(char *contentf){

	if( cgierr != 0 )
		return NULL;
	
	int i = cgindex;
	
	cgindex = 0;
			
	do{		
		if( !strcmp(content[cgindex], contentf) ){
			return fp[cgindex];
		}
		
		cgindex++;
		
	}while( cgindex <= lenOfVar );
	
	cgindex = i;//when getFile function doesn't find anything resets the value of cgindex
	
	return NULL;


}


FILE *MultiPart::getNextFile(){
	
	if( cgierr != 0 )
		return NULL;

	if( cgindex >= lenOfVar )
		return NULL;
	else{
		cgindex++;
		return fp[cgindex];
	}
}


char *MultiPart::getNextFileName(){
	
	if( cgierr != 0 )
		return NULL;

	if( cgindex >= lenOfVar )
		return NULL;
	else{
		cgindex++;
		return filename[cgindex];
	}

}

char *MultiPart::getNextContentType(){

	if( cgierr != 0 )
		return NULL;

	if( cgindex >= lenOfVar )
		return NULL;
	else{
		cgindex++;
		return content[cgindex];
	}


}

char *MultiPart::getNextName(){

	if( cgierr != 0 )
		return NULL;

	if( cgindex >= lenOfVar )
		return NULL;
	else{
		cgindex++;
		return name[cgindex];
	}


}

char *MultiPart::getFileName(){
	
	if( cgierr != 0)
		return NULL;
	
	if( cgindex >= lenOfVar )
		return NULL;
	else{
		return filename[cgindex];
	}
}


char *MultiPart::getContentType(){
	
	if( cgierr != 0)
		return NULL;
	
	if( cgindex >= lenOfVar )
		return NULL;
	else{
		return content[cgindex];
	}

}

FILE *MultiPart::getFile(){
	
	if( cgierr != 0)
		return NULL;
	
	if( cgindex >= lenOfVar )
		return NULL;
	else{
		return fp[cgindex];
	}
	

}

char *MultiPart::getName(){//sonradan eklenen

	if( cgierr != 0)
		return NULL;
	
	if( cgindex >= lenOfVar )
		return NULL;
	else{
		return name[cgindex];
	}


}

char *MultiPart::getTempFileName(int array){
	
	return tempfile[array];

}

void filewriter(char *fname,char *mode){
	
	FILE *fp;
	FILE *fpnews;
	int fchar;
	
	fpnews =  fopen("news.dat",mode);
		
	if( fpnews == NULL ){
		Response.Write("news.dat dosyasi bulunamadi");BR
		Response.Footer();
		exit(EXIT_FAILURE);
	}

	fp = fopen(fname,"r");//opening temprory file
		
	if( fp == NULL ){//error checking
		Response.Write("geçici dosya bulunamadi");BR
		Response.Footer();
		fclose(fp);
		exit(EXIT_FAILURE);
	}
		
	while( (fchar = fgetc(fp)) != EOF )//writing to news.dat
		//fprintf(fpnews,"%c",(char*)fchar);
		fprintf(stdout,"%c",(char*)fchar);
			
	fclose(fp);
	remove(fname);
}
		
int main(){
	
	Response.Expires("0");
	Response.ContentType("text/html");
	Response.Header("News");
	/*				
	cout << Upload.getFileName() << "\n";
	cout << Upload.getContentType() << "\n";
	cout << Upload.getNextFileName() << "\n";
	cout << Upload.getTempFileName(0) <<"\n";
	cout << Upload.getTempFileName(1) << "\n";
	cout << Upload.getTempFileName(2) << "\n";
	cout << Upload.getTempFileName(3) << "\n";
	*/
	
	char *method = Request.ServerVariables("REQUEST_METHOD");
	
	if( method == NULL ){
		Response.Write("method belirtilmemis");
	}else{
				
		if( !strcmp(method,"GET") ){
				
			CENTER
			
			table();
				
				tr();td();
			
				form("POST","/cgi-bin/news/news","ENCTYPE=\"multipart/form-data\"");
				
					Response.Write("Tarih:");formInputType("text","date");BR
			
					Response.Write("Haber:");formInputType("text","species");BR
					
					Response.Write("Baþlýk:");formInputType("text","header");BR
						
					Response.Write("Aciklama:");BR
					
					printf("<textarea name=content rows=30 cols=80></textarea>");BR
					
					Response.Write("Resim:");formInputType("FILE","file");BR
					
					Response.Write("Haber ekleme:");formInputType("radio","mode","a+");BR
					Response.Write("Yeni haber:");formInputType("radio","mode","r+");BR
					
					Submit("Yolla");Reset("Yenile");BR
									
				endForm();
				
				_td();_tr();
				
			_table();	
			
			_CENTER
		
		}else{// for POST method
			
			MultiPart Upload;
			
			
			int fchar;//for file characters
					
						
			char *fname;//opening temp files for writing to news.dat
			
			
			fname = Upload.getTempFileName(4);//for file mode
			
			
			/* writing tarih to news.dat */
			
			fname = Upload.getTempFileName(0);
		
			filewriter(fname,"r+");
			
			//free(fname);
			
			/* writing haber to news.dat */
			
			fname = Upload.getTempFileName(1);
		
			filewriter(fname,"r+");
			
			//free(fname);
			
			/* writing baslik to news.dat */
			
			fname = Upload.getTempFileName(2);
		
			filewriter(fname,"r+");
			
			//free(fname);
			
			/* writing aciklama to news.dat */
			
			fname = Upload.getTempFileName(3);
			
			filewriter(fname,"r+");
			
			//free(fname);
			
			/* writing gif to news.dat */
			
			//later
			
			/* file mode */
			fname = Upload.getTempFileName(5);
			
			filewriter(fname,"r+");
			
			//free(fname);
			
					
		}
	}
	Response.Footer();
}

