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

/* These macros are for HTML output */

#ifndef _CGIOUT_H_
#define _CGIOUT_H_ 1

#define BR printf("<br>\n");

#define B printf("<b>");
#define _B printf("</b>");

#define I printf("<i>");
#define _I printf("</i>");

#define P printf("<p>\n");
#define _P printf("</p>\n");

#define CENTER printf("<center>");
#define _CENTER printf("</center>\n");

#define DEBUG printf("Line Passed Success %d\n",__LINE__);

/*These inlines short definations are for HTML output */

void chrtoHtmlOutput(char chr){
	
	if( isalnum(chr) )printf("%c",chr);
			
			else switch(chr){
			
			case '\"': printf("&quot;"); break;
			
			case '&': printf("&amp;"); break;
			
			case '<': printf("&lt;"); break;
			
			case '>': printf("&gt;"); break;
			
			case ' ': printf("&nbsp;"); break;
			
			case '\r': case '\n': printf("<br>"); break;
			
			default: printf("&#x%X;",chr);
			
			}
	
}

inline void a(char *link){

	printf("<a href='%s'>",link);
	
}
inline void a(char *link,char *parameters){

	printf("<a href='%s' %s >",link,parameters);

}

inline void _a(){

	printf("</a>");

}

inline void Div(char *str){
	
	printf("<div %s >",str);
	
}

inline void _Div(){

	printf("</div>");

}

inline void h(unsigned char val){

	printf("<h%d>",val);

}

inline void _h(unsigned char val){

	printf("</h%d>",val);

}

inline void image(char* image){

	printf("<img src='%s' />",image);

}

inline void image(char* image,char* parameters){

	printf("<img src='%s' %s />",image,parameters);

}


inline void table(){

	printf("<table>");

}

inline void table(char *param){
	
	printf("<table %s >",param);

}

inline void _table(){

	printf("</table>");

}

inline void tr(){

	printf("<tr>");

}

inline void tr(char *param){

	printf("<tr %s >",param);

}

inline void _tr(){

	printf("</tr>");

}
inline void th(){

	printf("<th>");

}

inline void th(char *param){

	printf("<th %s >",param);

}

inline void _th(){

	printf("</th>");

}

inline void td(){

	printf("<td>");
	
}

inline void td(char *param){

	printf("<td %s >",param);

}

inline void _td(){

	printf("</td>");

}

inline void form(char *method,char *action)
{

	printf("<form method='%s' action='%s' >",method,action);

}

inline void form(char *method, char *action, char *param){

	printf("<form method=%s action='%s' %s>",method,action,param);
	
}
inline void formInputType(char *type,char *name){

	printf("<input type='%s' name='%s'>",type,name);

}

inline void formInputType(char *type,char *name, int value){

	printf("<input type='%s' name='%s' value='%d'>",type,name,value);

}

inline void formInputType(char *type,char *name, char *value){

	printf("<input type='%s' name='%s' value='%s'>",type,name,value);

}
inline void formInputType(char *type, char *name, int value, long max){

	printf("<input type='%s' name='%s' value='%d' maxlength='%ld'>",type,name,value,max);
	

}

inline void formInputType(char *type,char *name,char *value,long max)
{

	printf("<input type='%s' name='%s' value='%s' max='%ld'>",type,name,value,max);

}

inline void formSelect(char *name){

	printf("<select name='%s'>",name);

}

inline void formSelect(char *name,char *param){

	printf("<select name='%s' %s >",name,param);

}

inline void formOption(char *value,char *str){

	printf("<option value='%s'>%s</option>",value,str);

}

inline void formOption(int value,char *str){

	printf("<option value='%d'>%s</option>",value,str);

}

inline void formOption(int value,int str){

	printf("<option value='%d'>%d</option>",value,str);

}

inline void formOption(char *value,int str){
	
	printf("<option value='%s'>%d</option>",value,str);
	
}

inline void _formSelect(){

	printf("</select>");
	
}

inline void endForm()
{

	printf("\n</form>\n");

}

inline void Submit(char *value){

	printf("<input type=submit value='%s'>",value);
}

inline void Reset(char *value){

	printf("<input type=reset value='%s'>",value);
}

inline void advertise(){

	CENTER  
		h(5); printf("&copy;Copyright 2000 by CGIMarket.com<br>All rights reserved.\n"); _h(5); 
		printf("<font size=1>");Response.Write("Beta Version 0.1");printf("</font>");
		printf("<br>Author: Kerim BASOL");
	_CENTER
	
	
}
/*
void aboutMe(){

	printf( 
		"<center>"
		"This CGI is not Freeware.Usage by Advertisement only<br/>"
		"If you want to buy full version.You must buy from www.CGIMarket.com or www.proweb2001.com<br/>"
		"</center><br/>"
		"This CGI was written by<br/>Kerim&amp;Kadir BASOL<br/>"
		);
	
	a("http://www.cgimarket.com","onMouseOver='window.status=\"WebMasters` Solution\"' onMouseOut=\"window.status=''\" "); Response.Write("www.CGIMarket.com\n"); _a();

}
*/

#endif /* _CGIOUT_H_ */
