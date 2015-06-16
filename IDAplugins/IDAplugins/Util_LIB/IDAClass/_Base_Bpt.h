#include "Util_LIB.H"
class _Base_Bpt{
public:
	ulong Flags;
	ulong Size;
	ulong Type;
	ea_t StartEA;
/**
* @See		������ת����INI��ģʽ
* @Param��	inIni -> INI��
* @Return��	inSecName -> ����
*/
	void To_Ini(INI* inIni, char* inSecName){
		inIni->addIntValue(inSecName, "StartEA", StartEA);
		inIni->addIntValue(inSecName, "Flags", Flags);
	}
/**
* @See		�����ݼ��ص�IDA�ڴ���
* @Param��	inStartEA -> ����ʵ��ַ
*/
	void To_IDAMem(ea_t inStartEA){
		if (check_bpt(inStartEA + StartEA) != BPTCK_NONE)return;
		add_bpt(inStartEA + StartEA);
	}
/**
* @See		��ʼ��_Base_Cmt
*/
	_Base_Bpt(segment_t* inSeg, ea_t inStart){
		StartEA = inStart - inSeg->startEA;
		Flags = check_bpt(inStart);
	}
/**
* @See		��ʼ��_Base_Cmt
* @Param��	inSection -> INI�ļ� ��
*/
	_Base_Bpt(C_INI_Section* inSection){
		if (inSection == NULL)return;
		StartEA = inSection->GetInt("StartEA");
		Flags = inSection->GetInt("Flags");
	}
/**
* @See		��ʼ��_Base_Cmt
* @Param��	inIni -> INI��
* @Param��	inSecName -> ����
*/
	_Base_Bpt(INI* inIni, char* inSecName){
		if (inIni == NULL)return;
		StartEA = inIni->GetIntValue(inSecName, "StartEA");
		Flags = inIni->GetIntValue(inSecName, "Flags");
	}
};

