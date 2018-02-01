// ehl.fptdata.save.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include <iostream>
#include "ehl.ftpdata.save.h"
#include "webref\ehl_webref.h"

#include <string>
#include <map>
#include <windows.h>
#include <list>

#include <stdlib.h>
#include <stdio.h>
#include <ostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * deffilename = "./config/device_info.ini";
using namespace std;

const char * strtmpdef[5][2] = { { "��", "01" }, { "��", "02" }, { "��", "23" }, { "��", "03" }, { "����", "99" } };
char * strnull = "";
class c_data_convert_hkfilename
{

public:
	c_data_convert_hkfilename()
	{
		load_param();
	}
	~c_data_convert_hkfilename()
	{
		free_param();
	}



private:
//	SBBH Ϊ���������� key sbbh_prop_name  value prop_value
// �ٶȲ�������Ϣ�� key cllx_csb   value wfxw
	map<string, string> msbinfo;

private:
	
	void write_param(const char * sbbh, const char * prop_key, const char * default_value, const char * filename = deffilename)
	{
		WritePrivateProfileString(sbbh, prop_key, default_value, filename);
	};
	void load_param_value(const char * secname,const char * key, const char * filename, map<string, string> * mt)
	{
		char value[256];
		char keyname[256];
		sprintf(keyname,"%s_%s",secname, key);
		GetPrivateProfileString(secname, key, "", value,256 ,(LPCTSTR)filename);
		mt->insert(pair<string, string>(keyname, value));
		
	}
	
	void load_param_section(const char * secname, const char * filename, map<string, string> * mt)
	{
		char ac_Result1[2000];
		int m_lRetValue1 = GetPrivateProfileSection(secname, ac_Result1, 2000, (LPCTSTR)filename);
		char * p = ac_Result1;
		for (int j = 0; j < m_lRetValue1; j++)
		{
			if (*p == '\0')
				break;
			char strtmp[256];
			sprintf(strtmp, p);
			char * strtmp1 = strtok(strtmp, "=");			
			char * strtmp2 = strtok(NULL, "=");
			if (strtmp2 == NULL)
				strtmp2 = strnull;
			printf("%s,%s", strtmp1, strtmp);
			char keyname[256];
			sprintf(keyname, "%s_%s", secname, strtmp1);

			mt->insert(pair<string, string>(keyname, strtmp2));
			printf("init map :%s = %s \n", keyname, strtmp2);

			//load_param_value(secname,p, filename, mt);
			p = p + strlen(p)+1;
		}
	}
	void load_param_sections(const char * filename,map<string,string> * mt)
	{
		char ac_Result[2000];
		
		int m_lRetValue;
		m_lRetValue = GetPrivateProfileSectionNames(ac_Result, 2000, (LPCTSTR)filename =deffilename);
		char * p = ac_Result;

		for (int i = 0; i < m_lRetValue; i++)
		{
			load_param_section(p,filename,mt);

			p = p + strlen(p)+1;
		};
	}
	void load_param()
	{
		 load_param_sections(deffilename, &msbinfo);
	};
	void free_param()
	{
		msbinfo.empty();
	};
private:

	const char * read_csinfo(const char * appname, const char * prop_key, const char * default_value)
	{
		string strkey = appname;
		strkey += "_";
		strkey += prop_key;
		map<string, string>::const_iterator iter = msbinfo.find(strkey);
		if (iter != msbinfo.end())
		{
			return iter->second.c_str();
		}
		else
		{
			msbinfo.insert(pair<string,string>(strkey, default_value));
			write_param(appname, prop_key, default_value);
			return default_value;
		};
	};
private:
	//������Ϣ
	string sbid;
	string sj;
	string cs;
	string hphm;
	string hpys;
	string hplx;
	string cllx;
	string fxid;
	string cdid;
	string datatype; //��������
	string tmpdata;
	int imgcount;
	string img1;
	string img2;
	string img3;
	string wfdm;
public:	
	//testdata:20150427111212999_0_70_��A12345_��_01_01_4_3_6109001_hik.jpg
	char sdatainfo[256];
	int read_baseinfo(const char * datainfo, int timgcount, const char * timg1, const char * timg2, const char * timg3)
	{
		
		char ext[10];
		_splitpath(datainfo, 0, 0, sdatainfo, ext);
		int iresult = 0;

		sj = strtok(sdatainfo, "_");
		datatype = strtok(NULL, "_");
		cs = strtok(NULL, "_");
		hphm = strtok(NULL, "_");
		hpys = strtok(NULL, "_");
		hplx = strtok(NULL, "_");
		cllx = strtok(NULL, "_");
		fxid = strtok(NULL, "_");
		cdid = strtok(NULL, "_");
		sbid = strtok(NULL, "_");
		wfdm = strtok(NULL, "_");
		tmpdata = datainfo;
		imgcount = timgcount;
		img1 = timg1;
		img2 = timg2;
		img3 = timg3;
		//tpmc = datainfo;
		printf("sj = %s\n", sj.c_str());
		printf("datatype = %s\n", datatype.c_str());
		printf("hphm = %s\n", hphm.c_str());
		printf("hpys = %s\n", hpys.c_str());
		printf("hplx = %s\n", hplx.c_str());
		printf("cllx = %s\n", cllx.c_str());
		printf("fxid = %s\n", fxid.c_str());
		printf("cdid = %s\n", cdid.c_str());
		printf("sbid = %s\n", sbid.c_str());
		printf("wfdm = %s\n", wfdm.c_str());


		printf("hphm = %s\n", hphm.c_str());
		return iresult;
	}
public:
	int get_datatype()
	{
		return atoi(datatype.c_str());
	}

private:
	const char * get_kkid()
	{
		//return "371600000001";
		return read_csinfo(sbid.c_str(), "kkid", sbid.c_str());
	}
	//	<!--���ƺ���[����Ϊ��]-->
	//	<hphm>��A12345</hphm>
	const char *get_hphm()
	{
		return hphm.c_str();
	};

	const char *get_hpys()
	{
		//<!--������ɫ[����Ϊ�գ����룺�ƣ������ף��ڣ�����]-->
		//<hpys>��< / hpys>
		return hpys.c_str();
		//return "1";
	};

	//	<!--��������[���ɿգ�����GA24.4��Ҫ��]������룺01 - ���ͳ�����02 - С�ͳ�����03 - �⼮������23 - �������ó�����99 - ����-->
	//	<cllx>01< / cllx>

//	1 �������� 0 ----
//		2 С�ͳ� 1 ----
//		3 ���ͳ� 2 ----
//		4 ���� 3 ----
//		5 ���ֳ� 4 ----
//		6 ���ֳ� 5 ----

	const char * get_default_cllx(const char * hpys)
	{
		for (int i = 0; i < 5; i++)
		{
			if (strcmp(strtmpdef[i][0], hpys))
			{
				return strtmpdef[i][1];
			}
		}
		return "99";
	}
	const char *get_cllx()
	{
		//return read_csinfo("cllx", cllx.c_str(), cllx.c_str());
		return read_csinfo("cllx", hpys.c_str(), get_default_cllx(hpys.c_str()));

	};

	//	<!--����ʱ��[����Ϊ�գ�ʱ���ʽ��yyyy - MM - dd hh24 : mm : ss]-->
	//	<gwsj>2009 - 09 - 23 04:11 : 55< / gwsj>
	
	char wfsj[256];
	const char *get_gwsj()
	{
		sprintf(wfsj,"%c%c%c%c-%c%c-%c%c %c%c:%c%c:%c%c"
			, sj.at(0), sj.at(1), sj.at(2), sj.at(3), sj.at(4), sj.at(5), sj.at(6)
			, sj.at(7), sj.at(8), sj.at(9), sj.at(10), sj.at(11), sj.at(12), sj.at(13));
		return wfsj;
	};

	//	<!--������[����Ϊ�գ����루1 - 4�����������£�����1��������2��������3:����4-->
	//	<fxbh>1</fxbh>
	const char * get_fxbh()
	{
		return read_csinfo("fxbh", fxid.c_str(), fxid.c_str());
		//return fxid.c_str();
	};

	//	<!--�������[����Ϊ�գ����룺1 - 99]-->
	//	<cdbh>2< / cdbh>

	const char * get_cdbh()
	{
		//return cdid.c_str();
		return read_csinfo("cdbh", cdid.c_str(), cdid.c_str());
	};
	//	<!--�����ٶ�[����Ϊ�գ����룺1 - 300]-->
	//	<clsd>76< / clsd>
	const char * get_clsd()
	{
		return cs.c_str();
	};
	//	<!--֤���ļ�1[����Ϊ�գ�ȫ��ͼƬ��������Ч��http·��-->
	//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
	string strimg1;
	const char * get_zjwj1()
	{
		strimg1 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
		strimg1.append(img1.c_str());
		return strimg1.c_str();
	};
	//<!--֤���ļ�2[�ܿգ���дͼƬ��������Ч��http·��-->
	//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>
	string strimg2;
	const char * get_zjwj2()
	{
		if (imgcount > 1)
		{
			strimg2 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
			strimg2.append(img2.c_str());
			return strimg2.c_str();
		}
		else
		{
			return "";
		}

	};
	//	<!--֤���ļ�3[�ɿգ�����ͼƬ��������Ч��http·��]-->
	//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
	string strimg3;
	const char * get_zjwj3()
	{
		if (imgcount > 2)
		{
			strimg3 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
			strimg3.append(img3.c_str());
			return strimg3.c_str();
		}
		else
		{
			return "";
		}
	};
	//	<!--֤���ļ�4[[�ɿգ�¼���ļ���������Ч��http·��-->
	//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
	const char * get_zjwj4()
	{
		return "";
	};
	//	<!--��¼���� : [����Ϊ��, 0����������1������������2������������3�����س���4��ռ������5����ʷΥ������6�����г���7�����䳬�ٳ���8������Υ������9������ 10��ת��Υ��  11.�����Υ�� 12.����������ʻ 13.Υ��ͣ��  14.ѹ����] -->
	//	<jllx>0< / jllx>
	const char * get_jllx()
	{
		return datatype.c_str();
	};
	//	<!--���ٺ���[�ɿ�, ���ٵĺ��벿�֣�3λ]-->
	//	<cshm>869< / cshm>
	char cshm[256];
	const char * get_cshm()
	{
		sprintf(cshm, "%c%c%c"
			, sj.at(14), sj.at(15), sj.at(16));
		return cshm;
	};

	//<!--������Դ[����Ϊ�գ�������Դ��1 - ������豸��2 - ��·�����豸��3 - �����豸��4 - ��·���ӣ�Υ��ץ�ģ���5 - �ƶ�����6 - �г���¼�ǣ�9 - ���������豸]-->
	//	<sjly>2< / sjly>
	const char * get_sjly()
	{
		return read_csinfo(sbid.c_str(), "sjlx", "2");
	};

	//	<!--��������[����Ϊ�գ�����GA��׼] ������룺01 - ���ͳ�����02 - С�ͳ�����03 - �⼮������23 - �������ó�����99 - ����-->
	//	<hpzl>01< / hpzl>

	const char * get_hpzl()
	{
		return hplx.c_str();
	};

	//	<!--Υ��ʱ��[����Ϊ�գ�ʱ���ʽ��yyyy - MM - dd hh24 : mm : ss]-->
	//	<wfsj>2009 - 09 - 23 04:11 : 55< / wfsj>
	const char * get_wfsj()
	{
		return get_gwsj();
	};
	//	<!--Υ����Ϊ[����Ϊ�գ�����GA��׼]-->
	//	<wfxw>1030</wfxw>
	string strwfxw;
	const char * get_wfxw()
	{
		
		
		/*
		int ispeed = atoi(cs.c_str());
		int ilimitspeed = atoi(get_clxs());
		int csb = (ispeed * 100) / ilimitspeed;
		if (csb < 20)
		{
			strtmp = read_csinfo(get_cllx(), "csb20", "1020");
		}
		else
		{
			if (csb > 50)
			{
				strtmp = read_csinfo(get_cllx(), "csb50", "1020");
			}
			else
			{
				strtmp = read_csinfo(get_cllx(), "csb205050", "1020");
			}
		};
		return strtmp.c_str();
		*/
		strwfxw = read_csinfo("wfdm", wfdm.c_str(), wfdm.c_str());
		return strwfxw.c_str();
	};

	//	<!--Υ������[�ɿգ���Υ����Ϊ�򵥵�����]-->
	//	<wfnr>����50%< / wfnr>
	string strwfnr;
	const char * get_wfnr()
	{
		strwfnr = read_csinfo("wfnr", wfdm.c_str(), "");
		return strwfnr.c_str();
	};
	//<!--Υ���ص�[���ɿ�]-->
	//	<wfdd>208300315500</wfdd>
	string strwfdd;
	const char * get_wfdd()
	{
		 strwfdd = read_csinfo(sbid.c_str(), "wfdd", sbid.c_str());
		 return strwfdd.c_str();
	};

	//<!--Υ����ַ[���ɿգ�Υ���ص������]-->
	//<wfdz>����·�����·< / wfdz>
	const char * get_wfdz()
	{
		return read_csinfo(sbid.c_str(), "wfdz", "ʮ�����");
	};



	//<!--��������[�ɿգ����룺1 - 300]-->
	//<clxs>70< / clxs>
	const char * get_clxs()
	{
		string strtmp = "speedlimit_";
		strtmp += cllx.c_str();
		return  read_csinfo(sbid.c_str(), strtmp.c_str(), "80");
	};
	//<!--�������[�ɿգ����룺1 - 300]-->
	//<zdxs>60< / zdxs>
	const char * get_zdxs()
	{
		return "1";
	};
	//<!--�ɼ�����[����Ϊ�գ�-->
	//<cjjg>371600000001< / cjjg>
	const char * get_cjjg()
	{
		return  read_csinfo(sbid.c_str(), "cjjg", "371600000001");
	};
	//<!--�ɼ��û�[�ɿգ�-->
	//<cjyh>ץ��Ա< / cjyh>
	const char * get_cjyh()
	{
		return read_csinfo(sbid.c_str(), "cjyh", "9999");
	};
	//<!--�ɼ�ʱ��[�ɿգ�-->
	//<cjsj>2009 - 09 - 23 04:11 : 55< / cjsj>
	const char * get_cjsj()
	{
		return get_wfsj();
	};
	//<!--ִ������[���ɿ�] -->
	//<zqmj>012321< / zqmj>
	const char * get_zqmj()
	{
		return read_csinfo(sbid.c_str(), "cjyh", "9999");
	};
	//<!--��ע��Ϣ[�ɿ�]-->
	//<bz>< / bz>
	const char * get_bz()
	{
		return read_csinfo(sbid.c_str(), "bz", "");
	};

public:
	//void plug_proc_viodata(int itype, const wchar_t * datastr, wchar_t * proc_msg)
	
	int get_viodata_xml(string &strxml)
	{
		//
		char xml[1024];
		strxml = "";
		sprintf(xml, "<?xml version = \"1.0\" encoding = \"GB2312\"?>");
		strxml.append(xml);
		sprintf(xml, "<message System = \"ATMS\" Ver = \"1.0\">");
		strxml.append(xml);

		sprintf(xml, "<systemtype>TGS</systemtype>");
		strxml.append(xml);
		sprintf(xml, "<messagetype>NOTICE</messagetype>");
		strxml.append(xml);
		sprintf(xml, "<sourceIP>3.0</sourceIP>");
		strxml.append(xml);
		sprintf(xml, "<targetIP></targetIP>");
		strxml.append(xml);
		sprintf(xml, "<user>PECCANCY</user>");
		strxml.append(xml);
		sprintf(xml, "<password>PECCANCY</password>");
		strxml.append(xml);
		sprintf(xml, "<peccancyinfo>");
		strxml.append(xml);


		//<!--������Դ[����Ϊ�գ�������Դ��1 - ������豸��2 - ��·�����豸��3 - �����豸��4 - ��·���ӣ�Υ��ץ�ģ���5 - �ƶ�����6 - �г���¼�ǣ�9 - ���������豸]-->
		//	<sjly>2< / sjly>
		sprintf(xml, "<sjly>%s</sjly>", get_sjly());
		strxml.append(xml);

		//	<!--���ƺ���[����Ϊ��]-->
		//	<hphm>��A12345< / hphm>
		sprintf(xml, "<hphm>%s</hphm>", get_hphm());
		strxml.append(xml);

		//	<!--��������[����Ϊ�գ�����GA��׼] ������룺01 - ���ͳ�����02 - С�ͳ�����03 - �⼮������23 - �������ó�����99 - ����-->
		//	<hpzl>01< / hpzl>

		sprintf(xml, "<hpzl>%s</hpzl>", get_hpzl());
		strxml.append(xml);

		//	<!--Υ��ʱ��[����Ϊ�գ�ʱ���ʽ��yyyy - MM - dd hh24 : mm : ss]-->
		//	<wfsj>2009 - 09 - 23 04:11 : 55< / wfsj>
		sprintf(xml, "<wfsj>%s</wfsj>", get_wfsj());
		strxml.append(xml);


		//	<!--Υ����Ϊ[����Ϊ�գ�����GA��׼]-->
		//	<wfxw>1030< / wfxw>
		sprintf(xml, "<wfxw>%s</wfxw>", get_wfxw());
		strxml.append(xml);

		//	<!--Υ������[�ɿգ���Υ����Ϊ�򵥵�����]-->
		//	<wfnr>����50%< / wfnr>
		sprintf(xml, "<wfnr>%s</wfnr>", get_wfnr());
		strxml.append(xml);


		//<!--Υ���ص�[���ɿ�]-->
		//	<wfdd>208300315500< / wfdd>
		sprintf(xml, "<wfdd>%s</wfdd>", get_wfdd());
		strxml.append(xml);
		//<!--Υ����ַ[���ɿգ�Υ���ص������]-->
		//<wfdz>����·�����·< / wfdz>
		sprintf(xml, "<wfdz>%s</wfdz>", get_wfdz());
		strxml.append(xml);
		//<!--�������[���ɿգ����룺1 - 99]-->
		//<cdbh>2< / cdbh>
		sprintf(xml, "<cdbh>%s</cdbh>", get_cdbh());
		strxml.append(xml);
		//<!--������[���ɿ�Υ���ص���� + 1λ������ �����������루1 - 4����������������2��������3��������4:���� - ->
		//<fxbh>6400000000001< / fxbh>
		sprintf(xml, "<fxbh>%s%s</fxbh>",get_wfdd(), get_fxbh());
		strxml.append(xml);
		//<!--�����ٶ�[�ɿգ����룺1 - 300]-->
		//<clsd>76< / clsd>
		sprintf(xml, "<clsd>%s</clsd>", get_clsd());
		strxml.append(xml);
		//<!--��������[�ɿգ����룺1 - 300]-->
		//<clxs>70< / clxs>
		sprintf(xml, "<clxs>%s</clxs>", get_clxs());
		strxml.append(xml);
		//<!--�������[�ɿգ����룺1 - 300]-->
		//<zdxs>60< / zdxs>
		sprintf(xml, "<zdxs>%s</zdxs>", get_zdxs());
		strxml.append(xml);
		//<!--�ɼ�����[����Ϊ�գ�-->
		//<cjjg>371600000001< / cjjg>
		sprintf(xml, "<cjjg>%s</cjjg>", get_cjjg());
		strxml.append(xml);
		//<!--�ɼ��û�[�ɿգ�-->
		//<cjyh>ץ��Ա< / cjyh>
		sprintf(xml, "<cjyh>%s</cjyh>", get_cjyh());
		strxml.append(xml);
		//<!--�ɼ�ʱ��[�ɿգ�-->
		//<cjsj>2009 - 09 - 23 04:11 : 55< / cjsj>
		sprintf(xml, "<cjsj>%s</cjsj>", get_cjsj());
		strxml.append(xml);
		//<!--ִ������[���ɿ�] -->
		//<zqmj>012321< / zqmj>
		sprintf(xml, "<zqmj>%s</zqmj>", get_zqmj());
		strxml.append(xml);
		//<!--��ע��Ϣ[�ɿ�]-->
		//<bz>< / bz>
		sprintf(xml, "<bz>%s</bz>", get_bz());
		strxml.append(xml);

		//	<!--֤���ļ�1[����Ϊ�գ�ȫ��ͼƬ��������Ч��http·��-->
		//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
		sprintf(xml, "<zjwj1>%s</zjwj1>", get_zjwj1());
		strxml.append(xml);
		//<!--֤���ļ�2[�ܿգ���дͼƬ��������Ч��http·��-->
		//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>
		sprintf(xml, "<zjwj2>%s</zjwj2>", get_zjwj2());
		strxml.append(xml);
		//	<!--֤���ļ�3[�ɿգ�����ͼƬ��������Ч��http·��]-->
		//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
		sprintf(xml, "<zjwj3>%s</zjwj3>", get_zjwj3());
		strxml.append(xml);
		//	<!--֤���ļ�4[[�ɿգ�¼���ļ���������Ч��http·��-->
		//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
		sprintf(xml, "<zjwj4>%s</zjwj4>", get_zjwj4());
		strxml.append(xml);

		sprintf(xml, "</peccancyinfo>");
		strxml.append(xml);
		//	< / message>
		sprintf(xml, "</message>");
		strxml.append(xml);
		return 0;
	};
	int get_passcar_xml(string &strxml)
	{
		//
		//	FILE * fp = wfopen("test.data",);
		char xml[1024];
		sprintf(xml, "<?xml version = \"1.0\" encoding = \"GB2312\"?>");
		strxml.append(xml);
		sprintf(xml, "<message System = \"ATMS\" Ver = \"1.0\">");
		strxml.append(xml);
		sprintf(xml, "<systemtype>TGS</systemtype>");
		strxml.append(xml);
		sprintf(xml, "<messagetype>NOTICE</messagetype>");
		strxml.append(xml);
		sprintf(xml, "<sourceIP>3.0</sourceIP>");
		strxml.append(xml);
		sprintf(xml, "<targetIP></targetIP>");
		strxml.append(xml);
		sprintf(xml, "<user>PASSCAR</user>");
		strxml.append(xml);
		sprintf(xml, "<password>PASSCAR</password>");
		strxml.append(xml);
		sprintf(xml, "<passcarinfo>");
		strxml.append(xml);

		//		<!--���ڱ��[����Ϊ��] -->
		//<kkid>371600000001< / kkid>
		sprintf(xml, "<kkid>%s</kkid>", get_kkid());
		strxml.append(xml);

		//	<!--���ƺ���[����Ϊ��, ����:ʶ��ĳ��ƺ��룬δ��ȫʶ��д����ʶ���ơ�-->
		//	<hphm>��A12345< / hphm>
		sprintf(xml, "<hphm>%s</hphm>", get_hphm());
		strxml.append(xml);
		//<!--������ɫ[����Ϊ�գ����룺�ƣ������ף��ڣ�����]-->
		//<hpys>��< / hpys>
		sprintf(xml, "<hpys>%s</hpys>", get_hpys());
		strxml.append(xml);

		//	<!--��������[���ɿգ�����GA24.4��Ҫ��]������룺01 - ���ͳ�����02 - С�ͳ�����03 - �⼮������23 - �������ó�����99 - ����-->
		//	<cllx>01< / cllx>
		sprintf(xml, "<cllx>%s</cllx>", get_cllx());
		strxml.append(xml);

		//	<!--����ʱ��[����Ϊ�գ�ʱ���ʽ��yyyy - MM - dd hh24 : mm : ss]-->
		//	<gwsj>2009 - 09 - 23 04:11 : 55< / gwsj>
		sprintf(xml, "<gwsj>%s</gwsj>", get_gwsj());
		strxml.append(xml);

		//	<!--������[����Ϊ�գ����루1 - 4�����������£�����1��������2��������3:����4-->
		//	<fxbh>1< / fxbh>
		sprintf(xml, "<fxbh>%s</fxbh>", get_fxbh());
		strxml.append(xml);

		//	<!--�������[����Ϊ�գ����룺1 - 99]-->
		//	<cdbh>2< / cdbh>
		sprintf(xml, "<cdbh>%s</cdbh>", get_cdbh());
		strxml.append(xml);
		//	<!--�����ٶ�[����Ϊ�գ����룺1 - 300]-->
		//	<clsd>76</clsd>
		sprintf(xml, "<clsd>%s</clsd>", get_clsd());
		strxml.append(xml);
		//	<!--֤���ļ�1[����Ϊ�գ�ȫ��ͼƬ��������Ч��http·��-->
		//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
		sprintf(xml, "<zjwj1>%s</zjwj1>", get_zjwj1());
		strxml.append(xml);
		//<!--֤���ļ�2[�ܿգ���дͼƬ��������Ч��http·��-->
		//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>
		sprintf(xml, "<zjwj2>%s</zjwj2>", get_zjwj2());
		strxml.append(xml);
		//	<!--֤���ļ�3[�ɿգ�����ͼƬ��������Ч��http·��]-->
		//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
		sprintf(xml, "<zjwj3>%s</zjwj3>", get_zjwj3());
		strxml.append(xml);
		//	<!--֤���ļ�4[[�ɿգ�¼���ļ���������Ч��http·��-->
		//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
		sprintf(xml, "<zjwj4>%s</zjwj4>", get_zjwj4());
		strxml.append(xml);
		//	<!--��¼���� : [����Ϊ��, 0����������1������������2������������3�����س���4��ռ������5����ʷΥ������6�����г���7�����䳬�ٳ���8������Υ������9������ 10��ת��Υ��  11.�����Υ�� 12.����������ʻ 13.Υ��ͣ��  14.ѹ����] -->
		//	<jllx>0</jllx>
		sprintf(xml, "<jllx>%s</jllx>", get_jllx());
		strxml.append(xml);
		//	<!--���ٺ���[�ɿ�, ���ٵĺ��벿�֣�3λ]-->
		//	<cshm>869< / cshm>
		sprintf(xml, "<cshm>%s</cshm>", get_cshm());
		strxml.append(xml);
		//	< / passcarinfo>
		sprintf(xml, "</passcarinfo>");
		strxml.append(xml);
		//	< / message>
		sprintf(xml, "</message>");
		strxml.append(xml);
		return 0;
	};

} ;

class mux
{
public:
	CRITICAL_SECTION critcal;
public:
	mux()
	{
		InitializeCriticalSection(&critcal);
	}
	~mux()
	{
		DeleteCriticalSection(&critcal);
	}
public:
	void lock()
	{
		EnterCriticalSection(&critcal);
	}
	void unlock()
	{
		LeaveCriticalSection(&critcal);
	}
}gmux;

c_data_convert_hkfilename g_datafile_convert_hkfilename;
#include ".\lib\write_log.h"
class waitproc_info
{
private:
	struct _tmpdata
	{
		string datainfo;
		int imgcount;
		string img1;
		string img2;
		string img3;
	};

private:
	list<_tmpdata *> m_waitproc_info;
public:
	int waitcount()
	{
		return m_waitproc_info.size();
	}
	void add_proc(const char * datainfo, int imgcount, char * img1, char * img2, char * img3)

	{
		gmux.lock();
		_tmpdata * tmpdata = new _tmpdata;
		tmpdata->datainfo = datainfo;
		tmpdata->imgcount = imgcount;
		tmpdata->img1 = img1;
		tmpdata->img2 = img2;
		tmpdata->img3 = img3;
		m_waitproc_info.push_back(tmpdata);
		gmux.unlock();
	};
private:
	/*
	< ? xml version = "1.0" encoding = "GB2312" ? >
	<message System = "ATMS" Ver = "1.0">
	<systemtype>TGS< / systemtype>
	<messagetype>FEEDBACK< / messagetype>
	<sourceIP>3.0< / sourceIP>
	<targetIP>< / targetIP>
	<user>< / user>
	<password>< / password>
	<executeresult>
		<!- ����ɹ�������ִ�гɹ����¼���]-->
		<recordid>< / recordid>
		<!- ��������]-->
		<errordescription>������ȷ��xml��ʽ��< / errordescription>
		<!- �ɹ���Ӱ�������]-->
		<resultnum>0< / resultnum>
		<!- �ɹ��������]-->
		<resultdescription>< / resultdescription>
		<!- �������]-->
		<errorcode>0< / errorcode>
	< / executeresult>
	< / message>
	*/
	int check_result_xml(const char * xml)
	{
		string str = "";
		char * p = (char *)strstr((const char *)xml, ((const char *)"<errorcode>"));
		p += strlen("<errorcode>");
		while (*p != '<' && *p != '\0')
		{
			if (*p >= '0' && *p <= '9')
				str += *p;
			p++;
		};
		return atoi(str.c_str());
	};
public:
	void proc_info(const char * datastr, int * iresult_code, char * reset_msg, int imgcount,const char * img1,const char * img2,const char * img3)
	{
		printf("datastr = %s\n",datastr);
		g_datafile_convert_hkfilename.read_baseinfo((char *)datastr,imgcount,img1,img2,img3);
		string strxml = "";
		char stmp[256];
		//strxml.append(g_datafile_convert_hkfilename.sdatainfo);
		int iresult = 0;
		if (g_datafile_convert_hkfilename.get_datatype() == 0)
		{
			//tracert car
			 iresult = g_datafile_convert_hkfilename.get_passcar_xml(strxml);
			 printf(strxml.c_str());
			 if (iresult == 0)
				 iresult = upload_data_inpasscar(strxml.c_str(), reset_msg);
		}
		else
		{
			//vio car
			 iresult = g_datafile_convert_hkfilename.get_viodata_xml(strxml);
			 printf(strxml.c_str());
			 if (iresult == 0)
				 iresult = upload_data_inviocar(strxml.c_str(), reset_msg);
		};
		WriteLog((char *)strxml.c_str());

		if (iresult == 0)
		{
			
			if (reset_msg != "\0")
			{
				
				WriteLog((char *)reset_msg);
				iresult = check_result_xml(reset_msg);
			}
			else
			{
				iresult = 100;
			}
			
		}
	

		if (iresult)
		{
			*iresult_code = iresult;
			sprintf(stmp, "error[%d]:web service upload data fail!", iresult);
			WriteLog(stmp);
		};
	
	}
	bool gproc_flag;
	void proc_info()
	{
		gmux.lock();
		list<_tmpdata*>::const_iterator iter = m_waitproc_info.begin();
		gmux.unlock();
		if (iter != m_waitproc_info.end())
		{
			proc_info((*iter)->datainfo.c_str(), 0, 0, (*iter)->imgcount, (*iter)->img1.c_str(), (*iter)->img2.c_str(), (*iter)->img3.c_str());
			gmux.lock();
			m_waitproc_info.remove(*iter);
			delete (_tmpdata*)(*iter);
			gmux.unlock();
			Sleep(1);
		}
			else
			{
				Sleep(100);
			}
		
	}
} gwaitproc_info;



static void __cdecl thread_proc_datainfo(void * param)
{
	gwaitproc_info.proc_info();
};
#include <process.h>
class c_work
{
private:
	uintptr_t thread;
public:
	c_work()
	{
		WriteLog("thread work begin!");
		gwaitproc_info.gproc_flag = true;
		thread = _beginthread(thread_proc_datainfo, NULL, NULL);
	};
	~c_work()
	{
		gwaitproc_info.gproc_flag = false; 
		//SignalObjectAndWait()
	}
}g_work;

void __stdcall plug_proc_data(int itype, const char * datastr, int * irescode, char * proc_msg,int imgcount,char * img1,char * img2,char * img3)
{
	if (itype == 0)
	{
		gwaitproc_info.proc_info(datastr, irescode, proc_msg,imgcount,img1,img2,img3);
	}
	else
	{
		gwaitproc_info.add_proc(datastr, imgcount, img1, img2, img3);
	}
		//sprintf(proc_msg, "process [*s]", strxml);
		sprintf(proc_msg, "process [%s],wait_proc[%d]", datastr,gwaitproc_info.waitcount());
 };

void  __stdcall init_work_mode(int workmode /*= 0*/, const char * webserviceurl /*= "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx"*/)
{
	sprintf(soap_endpoint, webserviceurl);
}


int __cdecl main(int argc, char * argv[])
{

	printf(argv[1]);
	char reftest[1024];
	//void  plug_proc_data(int itype, const char * datastr, char * proc_msg)
	plug_proc_data(0, (const char *)argv[1], NULL, reftest, 1, argv[1],"","");
	printf("\n");
	printf(reftest);
	system("PAUSE");

	return 0;
}

