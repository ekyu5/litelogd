
#ifndef _litelog_c_
#define _litelog_c_

#include "litelog4cpp.h"

LiteLog::LiteLog(){
	mGroup = strdup((char*)"anon");
	char hostname[LITELOG_MAXLEN_HOST];
	if (gethostname(hostname, LITELOG_MAXLEN_HOST - 1) != 0){
		mHost = strdup((char*)"unknown");
	}
	else {
		mHost = strdup(hostname);
	}
	
	char logname[8];
	sprintf(logname, "%d", getpid());
	mName = strdup(logname);
	mLevel = L_ALL;
	mMethod = M_STDOUT;
	mLogPath = NULL;
	mLogFileSize = LITELOG_FILE_DEFAULT_SIZE;
	mLogFileBackup = LITELOG_FILE_DEFAULT_BACKUP;
	mLitelog = NULL;
	mSockLen = 0;
}

LiteLog::~LiteLog(){
	if (mGroup != NULL)	free(mGroup);
	if (mHost != NULL) free(mHost);
	if (mName != NULL) free(mName);
	if (mLitelog != NULL) free(mLitelog);
}

int LiteLog::setLogLevel(char level){
	switch (level){
		case L_ALL:
		case L_DBUG:
		case L_INFO:
		case L_WARN:
		case L_EMIN:
		case L_EMAJ:
		case L_CRIT:
			break;
		default:
			return -1;
	}
	mLevel = level;
	return 0;
}

int LiteLog::setLogMethod(int method){
	switch(method){
		case M_STDOUT:
		case M_FILE:
			break;
		case M_NET:
			if (mLitelog == NULL)	return -2;
			break;
		default:
			return -1;
	}
	mMethod = method;
	return 0;
}

int LiteLog::setGroup(char* group){
	if (group == NULL)	return -1;
	if (strlen(group) >= LITELOG_MAXLEN_GROUP) return -2;
	if (mGroup != NULL) free(mGroup);
	
	mGroup = strdup(group);
	return 0;
}

int LiteLog::setHost(char* host){
	if (host == NULL)	return -1;
	if (strlen(host) >= LITELOG_MAXLEN_HOST) return -2;
	if (mHost != NULL) free(mHost);
	
	mHost = strdup(host);
	return 0;
}

int LiteLog::setName(char* name){
	if (name == NULL)	return -1;
	if (strlen(name) >= LITELOG_MAXLEN_NAME) return -2;
	if (mName != NULL) free(mName);
	
	mName = strdup(name);
	return 0;
}

int LiteLog::setLiteLogd(struct sockaddr* dest, size_t sock_len){
	if (dest == NULL)	return -1;
	if (	sock_len != sizeof(struct sockaddr_in)
		&&	sock_len != sizeof(struct sockaddr_in6)	){
		return -2;
	}
	mLitelog = (struct sockaddr*) malloc(sock_len);
	memcpy((void*)mLitelog, (void*)dest, sock_len);
	setLogMethod(M_NET);
	return 0;
}

int LiteLog::setFileLog(char* path, size_t max_file_size, size_t max_backup_count){
	if (path == NULL)	return -1;
	struct stat statBuffer;
	if (stat(path, &statBuffer) == 0 && S_ISDIR(statBuffer.st_mode)){
		// TODO Check path permission, compare with excuter.
		mLogPath = strdup(path);
	}
	else {
		return -2;
	}
	return 0;
}

int LiteLog::logFile(char* log){
	if (mLogPath == NULL) return -1;
	int rVal = 0;
	char destfile[LITELOG_MAXLEN_NAME * 2];
	sprintf(destfile, "%s/%s.log", mLogPath, mName);

	int fileSize = 0;
	
	/* Check file size */
	struct stat file;
	int r = stat(destfile, &file);
	if (r < 0){
		switch (errno){
			case ENOENT:
				break;
			default:
				printf("WARN: Can't access log file (%d:%s)\n"
						,	errno
						,	strerror(errno)
						);
				return -1;
		}
	}
	else{
		fileSize = (int32)file.st_size;
	}

	/* Move log files when over the size limit */
	if (fileSize >= (int)lSize){
		char fileOld[1024];
		char fileNew[1024];

		for (int i = lBackup - 1 ; i >= 0 ; i--){ 
			if (i != 0){                                   
				rVal = sprintf(fileOld, "%s/%s.bak.%u"
								,   mLogPath
								,   mName
								,   i
							  );      
			}          
			else{     
				rVal = sprintf(fileOld, "%s/%s.log"
								,   mLogPath
								,   mName
							  );                                   
			}                                       

			rVal = sprintf(fileNew, "%s/%s.bak.%u"
							,   mLogPath
							,   mName
							,   i+1                             
					  );                                     

			rVal = rename(fileOld, fileNew);        
		}                                            
	}

	FILE* fp = fopen(destfile, "a+");
	if (!fp){
		return -11;
	}

	rVal = fputs(log, fp);
	if (rVal < 0){
		fclose(fp);
		return -12;
	}

	fclose(fp);
	return 1;
}

int LiteLog::logLogd(char level, char* log){
	char hd1 = 0x00;
	char hd2 = 0x00;

	hd1 |= LITELOG_BIT_VERSION;
	hd2 &= 0x0F;

	static unsigned short seq = 0;
	seq++;

	char sendbuff[LITELOG_MAXLEN_LOGLINE];
	sendbuff[0] = hd1;
	sendbuff[1] = hd2;
	memcpy((void*)&sendbuff[2], (void*)&htons(seq), 2);

	int len = strncpy(&sendbuff[4], log, LITELOG_MAXLEN_LOGLINE - 4);
	sendbuff[len + 4] = 0x00;

	ssize_t len = sendto(mSock, (void*)&sendbuff, len+3, 0, mLiteLog, mSockLen);

	return (int)len;
}

int LiteLog::logStdout(char level, char* log){
	char printBuff[LITELOG_MAXLEN_LOGLINE];
	int remain = LITELOG_MAXLEN_LOGLINE;
	
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct tm*	cTime = localtime(&tv.tv_sec);

	int len = sprintf(	printBuff, "%04d-%02d-%02d %02d:%02d:%02d.%04u [%s]"
					,   cTime->tm_year+1900
					,   cTime->tm_mon+1
					,   cTime->tm_mday
					,   cTime->tm_hour
					,   cTime->tm_min
					,   cTime->tm_sec
					,   (uint32)tv.tv_usec/100
					,	getLogName(level)
			);  
	remain -= len;
}

int LiteLog::getLogName(char level)
{
	char l = level & L_CRIT;
	
	switch (l){
		case 0x00:	return (char*)"ALL";
		case 0x02:	return (char*)"DBUG";
		case 0x03:	return (char*)"INFO";
		case 0x04:	return (char*)"WARN";
		case 0x05:	return (char*)"EMIN";
		case 0x06:	return (char*)"EMAJ";
		case 0x07:	return (char*)"CRIT";
	}
	return (char*)"UDEF";
}

#endif


