
#ifndef _litelog_h_
#define _litelog_h_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>


#define log(_l_,_f_,...) setlog(_l_,(char*)__FILE__,__LINE__,(char*)_f_,##__VA_ARGS__)

#define LITELOG_MAXLEN_GROUP	64
#define LITELOG_MAXLEN_HOST		64
#define LITELOG_MAXLEN_NAME		64
#define LITELOG_MAXLEN_LOGLINE	1024

#define LITELOG_FILE_DEFAULT_SIZE	100*1024*1024
#define LITELOG_FILE_DEFAULT_BACKUP	3

#define LITELOG_BIT_VERSION		0x20

#define L_ALL	0x00
#define L_DBUG	0x02
#define L_INFO	0x03
#define L_WARN	0x04
#define L_EMIN	0x05
#define L_EMAJ	0x06
#define L_CRIT	0x07

#define L_TRACE 0x08


#define M_STDOUT 	1
#define M_FILE		2
#define M_NET		3

class LiteLog {
	private:
		int		mLevel;
		int		mMethod;
		char*	mGroup;
		char*	mHost;
		char*	mName;
		
		char*	mLogPath;
		size_t	mLogFileSize;
		size_t	mLogFileBackup;
	
		int		mSock;	
		struct sockaddr	*mLitelog;
		size_t	mSockLen;	

		int logFile(char* log);
		int logLogd(char* log);
		int logStdout(char* log);
	
	public:
		LiteLog();
		~LiteLog();

		int	setLogLevel(char level);
		int	setLogMethod(int method);
		
		int	setGroup(char* group);
		int	setHost(char* host);
		int	setName(char* name);
		int setLiteLogd(struct sockaddr* dest, size_t sock_len);
		int setFileLog(	char* path
					,	size_t max_file_size = LITELOG_FILE_DEFAULT_SIZE
					,	size_t max_backup_count = LITELOG_FILE_DEFAULT_BACKUP
				);
		void writeLog(char level, char* file, int line, char*fmt, ...);

		static char* getLogName(char level);
};

#endif

