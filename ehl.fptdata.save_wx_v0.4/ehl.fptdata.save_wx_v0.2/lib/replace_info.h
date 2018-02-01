#ifndef _replace_info_h__
#define _replace_info_h__
#include <string>
using namespace std;
inline string& replace_all_distinct(string& str,const string& old_value,const string& new_value) 
{ 
	for (string::size_type pos(0); pos!=string::npos; pos+=new_value.length()) 
	{ 
		if( (pos=str.find(old_value,pos))!=string::npos ) 
			str.replace(pos,old_value.length(),new_value); 
		else break; 
	} 
	return str; 
} ;


inline char * replace_str (char  *source, char  *result,  char  *sub,  char  *rep) 
{ 
 
 /*pc1  �Ǹ��Ƶ����result��ɨ��ָ��*/
 /*pc2  ��ɨ�� source �ĸ���ָ��*/
 /*pc3  Ѱ���Ӵ�ʱ,Ϊ���仯�е�source�Ƿ����Ӵ����,��ָ��sub��ɨ��ָ�� */
 /*�ҵ�ƥ���,Ϊ�˸��Ƶ������,��ָ��rep��ɨ��ָ��*/
 char  *pc1,  *pc2,  *pc3;     
 int  isource,  isub,  irep; 
 isub  = strlen(sub);   /*�Ա��ַ����ĳ���*/
 irep  = strlen(rep);   /*�滻�ַ����ĳ���*/
 isource= strlen(source); /*Դ�ַ����ĳ���*/ 
 if(NULL == *sub)  
  return strdup(source); 
 /*����������Ҫ�Ŀռ�*/
 //result  = (char *)malloc(( (irep > isub) ? (float)strlen(source) / isub* irep+ 1:isource ) * sizeof(char));
 pc1  =  result; /*Ϊpc1���θ��ƽ������ÿ���ֽ���׼��*/
 while(*source  !=  NULL) 
 { 
  /*Ϊ���source��sub�Ƿ������׼��,Ϊpc2,pc3 ����ֵ*/
	 pc2  =  source;
	 pc3  =  sub;
  /* ��ѭ���ģ���һ�������ǣ� 
      *  *pc2 ������ *pc3 �����Ӵ�����ȣ� 
      *  pc2  ��Դ����β 
      *  pc3  ��Դ����β ����ʱ,�����ȫ���Ӵ�,source����sub��ȣ� 
      *****************************************************/
	 while(*pc2  ==  *pc3  &&  *pc3  !=  NULL  &&  *pc2  !=  NULL)
		 pc2++,  pc3++;// [Page]
	 /* ����ҵ����Ӵ�,�������´�����*/
	 if(NULL  ==  *pc3)
	 {
		 pc3=rep;
		 /*�������׷�ӵ������*/
		 while(*pc3!=NULL)
			 *pc1++=*pc3++;
		 pc2--;
		 source=pc2;
		 /*   ��� source��sub��ȵ�ѭ�������� 
        * pc2 ��Ӧ��λ������ sub �д���������������Դ������һ��λ�á� 
        * �� source ָ����ǰ��һ���ַ��� 
        ***************************************************/
	 }
	 else	/*���û�ҵ��Ӵ�,���渴��source��ָ���ֽڵ������*/
		 *pc1++ = *source;
	 source++; /* ��source�����һ���ַ�*/
 }
 *pc1 = NULL;
 return result;
};

#endif // _replace_info_h__