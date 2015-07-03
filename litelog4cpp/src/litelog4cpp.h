
#ifndef _litelog_h_
#define _litelog_h_


#define log(_l_,_f_,...) setlog(_l_,(char*)__FILE__,__LINE__,(char*)_f_,##__VA_ARGS__)

#define LITELOG_MAXLEN_GROUP	64
#define LITELOG_MAXLEN_HOST		64
#define LITELOG_MAXLEN_NAME		64

#define LITELOG_FILE_DEFAULT_SIZE	100*1024*1024
#define LITELOG_FILE_DEFAULT_BACKUP	3

#define L_ALL	0x00
#define L_DBG	0x01
#define L_INF	0x02

#define M_STDOUT 	1
#define M_FILE		2
#define M_NET		3

void	setLog(int level, char* file, int line, char*fmt, ...);

class LiteLog {
	private:
		int		mLevel = L_ALL;
		int		mMethod = M_STDOUT;
		char*	mGroup = NULL;
		char*	mHost = NULL;
		char*	mName = NULL;
		
		char*	mLogPath = NULL;
		size_t	mLogFileSize = LITELOG_FILE_DEFAULT_SIZE;
		size_t	mLogFileBackup = LITELOG_FILE_DEFAULT_BACKUP;
		

		struct sockaddr	*mLitelog = NULL;
		size_t	mSockLen = 0;	
	
	public:
		LiteLog();
		~LiteLog();

		int	setLogLevel(int level);
		int	setLogMethod(int method);
		
		int	setGroup(char* group);
		int	setHost(char* host);
		int	setName(char* name);
		int setLiteLogd(struct sockaddr* dest, size_t sock_len);
		int setFileLog(	char* path
					,	size_t max_file_size = LITELOG_DEFAULT_FILE_SIZE
					,	size_t max_backup_count = LITELOG_FILE_DEFAULT_BACKUP
				);
		
};

#endif

