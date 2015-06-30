
#ifndef _litelog_c_
#define _litelog_c_

LiteLog::LiteLog(){
	mGroup = strdup((char*)"anon");
	char hostname[LITELOG_MAX_LEN_HOST];
	if (gethostname(hostname, LITELOG_MAX_LEN_HOST - 1) != 0){
		mHost = strdup((char*)"unknown");
	}
	else {
		mHost = strdup(hostname);
	}
	
	char logname[8];
	sprintf(logname, "%d", getpid());
	mName = strdup(logname);
}

LiteLog::~LiteLog(){
	if (mGroup != NULL)	free(mGroup);
	if (mHost != NULL) free(mHost);
	if (mName != NULL) free(mName);
	if (mLiteLog != NULL) free(mLiteLog);
}

int LiteLog::setLogLevel(int level){
	swtich (level){
		case L_ALL:
		case L_DBG:
		case L_INF:
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
	
	mName = strdup(host);
	return 0;
}

int LiteLog::setLiteLogd(struct sockaddr* dest, size_t sock_len){
	if (dest == NULL)	return -1;
	if (	sock_len != sizeof(sockaddr_in)
		&&	sock_len != sizeof(sockaddr_in6)	){
		return -2;
	}
	mLiteLog = (struct sockaddr*) malloc(sock_len);
	memcpy((void*)mLitelog, (void*)dest, sock_len);
	setMethod(M_NET);
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
	
}




#endif


