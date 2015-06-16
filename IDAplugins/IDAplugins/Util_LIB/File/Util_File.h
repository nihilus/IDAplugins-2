#include "Util_LIB.H"
class Util_File{
public:
/**
* @See		������д���ļ���
* @Param��in_fd -> �ļ����
* @Param��in_Str -> д���ַ���
* @Return��m_writeLen -> д�����ݳ���
*/
	static ssize_t fwrite(FILE* in_fd,char* in_Str){
		ssize_t m_writeLen = 0;
		int m_int = 0;
		qfwrite(in_fd, in_Str, strlen(in_Str));
		return m_writeLen;
	}
/**
* @See		��ȡ�ļ�
* @Param��inPath -> �ļ���ַ
* @Param��mode -> ��ģʽ
* @Return��m_buf -> ��ȡ����BUF
*/
	static char* Read(const char* inPath, const char *mode){
		if (inPath == NULL)return NULL;
		if (mode == NULL)return NULL;
		FILE* mFile = fopen(inPath, mode);
		if (mFile == NULL)return NULL;
		fseek(mFile, 0, SEEK_END); //��λ���ļ�ĩ 
		ulong fileSzie = qftell(mFile);
		if (fileSzie == 0){
			fclose(mFile);
			return NULL;
		}
		fseek(mFile, 0, SEEK_SET); //��λ���ļ���
		char* m_buf = (char*)malloc(fileSzie+1);
		memset(m_buf, -1, fileSzie);
		qfread(mFile, m_buf, fileSzie);
		fclose(mFile);
		return m_buf;
	}
/**
* @See		�����ļ�
* @Param��inDest -> Ŀ���ļ�
* @Param��mode -> Դ�ļ�
*/
	static void CPFile(const char* inDest, const char* inSrc){
		if (inDest == NULL)return;
		if (inSrc == NULL)return;
		char* _Buf = Read(inSrc, "rb+");
		if (_Buf == NULL)return;
		if (strlen(_Buf) > 5){
			FILE* m_fd = fopen(inDest, "wb+");
			if (m_fd != NULL){
				fwrite(m_fd, _Buf);
				fclose(m_fd);
			}
		}
		free(_Buf);
	}
/**
* @See		
* @Param��
* @Param��
*/
};

