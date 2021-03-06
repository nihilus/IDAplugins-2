#include "Util_LIB.H"
class Util_File{
public:
/**
* @See		将数据写入文件中
* @Param　in_fd -> 文件句柄
* @Param　in_Str -> 写入字符串
* @Return　m_writeLen -> 写入数据长度
*/
	static ssize_t fwrite(FILE* in_fd,char* in_Str){
		ssize_t m_writeLen = 0;
		int m_int = 0;
		qfwrite(in_fd, in_Str, strlen(in_Str));
		return m_writeLen;
	}
/**
* @See		读取文件
* @Param　inPath -> 文件地址
* @Param　mode -> 打开模式
* @Return　m_buf -> 读取到的BUF
*/
	static char* Read(const char* inPath, const char *mode){
		if (inPath == NULL)return NULL;
		if (mode == NULL)return NULL;
		FILE* mFile = fopen(inPath, mode);
		if (mFile == NULL)return NULL;
		fseek(mFile, 0, SEEK_END); //定位到文件末 
		ulong fileSzie = qftell(mFile);
		if (fileSzie == 0){
			fclose(mFile);
			return NULL;
		}
		fseek(mFile, 0, SEEK_SET); //定位到文件初
		char* m_buf = (char*)malloc(fileSzie+1);
		memset(m_buf, -1, fileSzie);
		qfread(mFile, m_buf, fileSzie);
		fclose(mFile);
		return m_buf;
	}
/**
* @See		复制文件
* @Param　inDest -> 目的文件
* @Param　mode -> 源文件
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
* @Param　
* @Param　
*/
};

