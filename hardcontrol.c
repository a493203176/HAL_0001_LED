
#include <jni.h>  /* /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include <stdio.h>
#include <malloc.h>

#include <android/log.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>


#if 0
typedef struct {
    char *name;          /* Java中函?的名字 */
    char *signature;    /* 描述了函?的??和返回值  */
    void *fnPtr;          /* 函?指?,指向C函? */
} JNINativeMethod;
#endif

static int fd;

jint ledOpen(JNIEnv * env, jobject cls) 
{
	fd = open("/dev/leds",O_RDWR);
	
	__android_log_print(ANDROID_LOG_DEBUG, "LEDemo", "native ledOpen fd = %d",fd);

	if (fd >= 0)
		return 0;
	else
		return -1;
}

void ledClose(JNIEnv * env, jobject cls) 
{
	__android_log_print(ANDROID_LOG_DEBUG, "LEDemo", "native ledClose ...");

	close(fd);
}

jint ledCtrl(JNIEnv * env, jobject cls, jint which, jint status) 
{
	int ret = ioctl(fd,status,which);

	__android_log_print(ANDROID_LOG_DEBUG, "LEDemo", "native ledCtrl which: %d, status : %d,ret = %d",which,status,ret);


	return	0;

}



static const JNINativeMethod methods[] = {
	{"ledOpen", "()I", (void *)ledOpen},
	{"ledClose", "()V", (void *)ledClose},
	{"ledCtrl", "(II)I", (void *)ledCtrl},
};


JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;

	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_4)) {
		return JNI_ERR; /* JNI version not supported */
	}
	cls = (*env)->FindClass(env, "com/example/aiyu/hardlibrary/HardControl"); // 完整路径
	if (cls == NULL) {
		return JNI_ERR;
	}

	
	if ((*env)->RegisterNatives(env,cls,methods,sizeof(methods)/sizeof(methods[0])) < 0) {
		return JNI_ERR;
	}
	return JNI_VERSION_1_4;
}



