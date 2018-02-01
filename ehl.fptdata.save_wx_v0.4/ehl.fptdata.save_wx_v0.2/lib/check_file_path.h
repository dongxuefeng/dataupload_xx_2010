
#ifndef _check_file_path_h__
#define _check_file_path_h__

#include "replace_info.h"
#include "iostream"
#include <shlwapi.h>
#include <winbase.h>
//shlwapi.lib
using namespace std;


//��bAddSpec Ϊ�棬��ȷ��szDst·��ĩβ����"\", ��bAddSpecΪ�٣���ȥ��lpszPathĩβ��"\"��"/"  

inline void ModifyPathSpec( TCHAR * szDst, BOOL  bAddSpec )  
{  
    int nLen = lstrlen(szDst);  

    TCHAR  ch  = szDst[ nLen - 1 ];  
    if( ( ch == ('\\') ) || ( ch == ('/') ) )  
    {  
        if(!bAddSpec )  
        {  
            szDst[ nLen - 1 ] = ('\0');  
        }
    }
    else  
    {
        if( bAddSpec )  
        {
            szDst[ nLen ] = ('\\');  
            szDst[ nLen + 1 ] = ('\0');  
        }
    }
};


inline bool get_parent_dir(string &strdir )
 {
	 //strdir.replace(strdir.begin(),strdir.end(),'\\','/');
	  replace_all_distinct(strdir,"\\","/") ;
	 int itmp = strdir.rfind('/');
	
	 strdir.at(itmp) = '\0';
	 return true;

 }

inline bool get_parent_dir1(string &strdir)
{
	//strdir.replace(strdir.begin(),strdir.end(),'\\','/');
	replace_all_distinct(strdir, "\\", "/");
	int itmp = strdir.rfind('/');

	strdir.at(itmp) = '\0';
	return true;

}

inline bool get_parent_dir(const char * strdir,  char * pardir)
{
	string strtmp = strdir;
	bool bresult = get_parent_dir1(strtmp);
	sprintf(pardir, strtmp.c_str());
	return bresult;
};

inline bool check_file_path(char * lpszDir)
{
	//��֤�ļ�Ŀ¼�Ƿ����
    if( ::PathIsDirectory( lpszDir ) ) return TRUE;  
  
    TCHAR   szPreDir[ MAX_PATH ];  
    sprintf( szPreDir, lpszDir );  
    //ȷ��·��ĩβû�з�б��  
    ModifyPathSpec( szPreDir, FALSE );  
  
    //��ȡ�ϼ�Ŀ¼  
   // BOOL  bGetPreDir  = ::PathRemoveFileSpec( szPreDir );  

	string strtmp = szPreDir;
	BOOL  bGetPreDir = get_parent_dir(strtmp);
    if( !bGetPreDir ) return FALSE;  
  
    //����ϼ�Ŀ¼������,��ݹ鴴���ϼ�Ŀ¼  
    if( !::PathIsDirectory( strtmp.c_str() ) )  
    {  
        check_file_path( (char *)strtmp.c_str());  
    }  
    return ::CreateDirectory( lpszDir, NULL );  
};

#include <direct.h>

#include <io.h>

inline bool DeleteDirectory(char* sDirName)  
{  
	//CFileFind tempFind;  
	char sTempFileFind[256] ; 
	sprintf(sTempFileFind,"%s/*.*",sDirName); 
	struct _finddata_t c_file;
	long hFile;

   // Find first .c file in current directory 
   if( (hFile = _findfirst( sTempFileFind, &c_file )) == -1L )
      printf( "No *.* files in current directory!\n" );
   else
   {

	   do {
		   char sFoundFileName[260];  
			//strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(256)); 
		   strcpy(sFoundFileName,c_file.name); 
		   if (c_file.attrib & _A_SUBDIR  )
		   {
				//Ŀ¼
			    if((strcmp(sFoundFileName,".")&&strcmp(sFoundFileName,"..")))
				{
					char sf[256];
					sprintf(sf,"%s/%s",sDirName,sFoundFileName);
					DeleteDirectory(sf);
				}
		   }
		   else
		   {
			   //�ļ�
			   		char sf[256];
					sprintf(sf,"%s/%s",sDirName,sFoundFileName);
					cout << "delete file succ:" << sf << endl;
					remove(sf);
		   }

	   } while( _findnext( hFile, &c_file ) == 0 );
	   _findclose( hFile );
	   rmdir(sDirName);
	   cout << "delete dir succ:" << sDirName << endl;
   };
	return true;
} 

#include "c_time.h"
inline bool free_disk(char * datapath,int daycount)
{
	c_time mtime;
	mtime.get_local_time();
	mtime.addday(-daycount);

	char deletefilepath[200];
	sprintf(deletefilepath, "%s",mtime.get_date());

	cout << "ɾ��"<<deletefilepath<<"ǰ������"<<endl;

	//���ҵ�ǰĿ¼�µ���Ŀ¼
	char sTempFileFind[256] ; 
	sprintf(sTempFileFind,"%s/*.*",datapath); 
	struct _finddata_t c_file;
	long hFile;
	 // Find first .c file in current directory 
	if( (hFile = _findfirst( sTempFileFind, &c_file )) == -1L )
	{
      printf( "No *.* files in current directory!\n" );
	}
	else
	{

	   do {
		   char sFoundFileName[260];  
			//strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(256)); 
		   strcpy(sFoundFileName,c_file.name); 
		   if (c_file.attrib & _A_SUBDIR  )
		   {
			    if((strcmp(sFoundFileName,".")&&strcmp(sFoundFileName,"..")))
				{
				
					if(strcmp(deletefilepath,sFoundFileName)>=0)
					{
						//ʱ����
						char dd[256];
						sprintf(dd,"%s/%s",datapath,sFoundFileName);
						cout << "����ɾ��Ŀ¼:"<< dd <<endl;
						DeleteDirectory(dd);
					}
				}
		   }


	   } while( _findnext( hFile, &c_file ) == 0 );
	}
	//
	   _findclose( hFile );
	return true;
}

#endif