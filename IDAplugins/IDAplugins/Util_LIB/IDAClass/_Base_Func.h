#include "Util_LIB.H"
class _Base_Func{
public:
	ea_t StartEA;
	char* Name;
	char* Cmt;
	char* ReCmt;
/**
* @See		��ȡIDA ��������
* @Param��	inFun -> IDA������
* @Return��	Out_Sec -> ��������
*/
	static char* GetFuncName(func_t* inFun){
		char* Out = NULL;
		char* Buf = (char*)Util_Base::Alloc(10240);
		
		if (get_func_name(inFun->startEA, Buf, 10240) != NULL){
			Out = strdup(Buf);
		}
		free(Buf);
		return Out;
	}
/**
* @See		��ȡIDA ��������
* @Param��	inFun -> IDA������
* @Return��	Out_Sec -> ��������
*/
	static char* GetFuncCmt(func_t* inFun,bool rptble){
		if (get_func_cmt(inFun, rptble) != NULL){
			return strdup(get_func_cmt(inFun, rptble));
		}
		return NULL;
	}


/**
* @See		������ת����INI��ģʽ
* @Param��	inIni -> INI��
* @Return��	inSecName -> ����
*/
	void To_Ini(INI* inIni, char* inSecName){
		inIni->addIntValue(inSecName, "StartEA", StartEA);
		if (Name != NULL)
			inIni->addStrValue(inSecName, "Name", Name);
		if (Cmt != NULL)
			inIni->addStrValue(inSecName, "Cmt", Cmt);
		if (ReCmt != NULL)
			inIni->addStrValue(inSecName, "ReCmt", ReCmt);
	}
/**
* @See		�����ݼ��ص�IDA�ڴ���
* @Param��	inStartEA -> ����ʵ��ַ
*/
	void To_IDAMem(ea_t inStartEA){
		if (Cmt != NULL){
			set_cmt(inStartEA + StartEA, Cmt, 0);
		}
		if (ReCmt != NULL){
			set_cmt(inStartEA + StartEA, ReCmt, 1);
		}
		func_t* _func = get_func(inStartEA + StartEA);
		if (_func == NULL)return;
//		ua_code(inStartEA + StartEA);		//���Ӻ����ߴ�����
		if (Cmt != NULL){
			set_func_cmt(_func, Cmt, 0);
		}
		if (ReCmt != NULL){
			set_func_cmt(_func, ReCmt, 1);
		}	
		if (Name == NULL)return;
		if (memcmp(Name, "sub_", 4) == 0)return;
		if (memcmp(Name, "loc_", 4) == 0)return;
		if (memcmp(Name, "_", 1) == 0)return;
		if (memcmp(Name, "j_", 2) == 0)return;
	//	set_name(inStartEA + StartEA, Name, 1);
	}
/**
* @See		��ʼ��_Base_Func
* @Param��	inSeg -> IDA ����
* @Param��	inFun -> IDA ������
*/
	_Base_Func(segment_t* inSeg,func_t* inFun){
		StartEA = 0;
		Name = Cmt = ReCmt = NULL;
		if (inFun == NULL)return;
		//��ȡƫ��
		StartEA = inFun->startEA - inSeg->startEA;
		//��ȡ���֡�ע��
		Name = GetFuncName(inFun);
		Cmt = GetFuncCmt(inFun, 0);
		ReCmt = GetFuncCmt(inFun, 1);
	}
/**
* @See		��ʼ��_Base_Func
* @Param��	inSection -> INI�ļ� ��
*/
	_Base_Func(C_INI_Section* inSection){
		if (inSection == NULL)return;
		StartEA = inSection->GetInt("StartEA");
		Name = inSection->GetString("Name");
		Cmt = inSection->GetString("Cmt");
		ReCmt = inSection->GetString("ReCmt");
	}
/**
* @See		��ʼ��_Base_Func
* @Param��	inIni -> INI��
* @Param��	inSecName -> ����
*/
	_Base_Func(INI* inIni, char* inSecName){
		if (inIni == NULL)return;
		StartEA = inIni->GetIntValue(inSecName, "StartEA");
		Name = inIni->GetStrValue(inSecName, "Name");
		Cmt = inIni->GetStrValue(inSecName, "Cmt");
		ReCmt = inIni->GetStrValue(inSecName, "ReCmt");
	}
};

