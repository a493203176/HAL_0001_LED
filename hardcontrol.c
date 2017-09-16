
#include <jni.h>  /* /usr/lib/jvm/java-1.7.0-openjdk-amd64/include/ */
#include <stdio.h>
#include <malloc.h>

#if 0
typedef struct {
    char *name;          /* Java中函?的名字 */
    char *signature;    /* 描述了函?的??和返回值  */
    void *fnPtr;          /* 函?指?,指向C函? */
} JNINativeMethod;
#endif

jint ledOpen(JNIEnv * env, jobject cls) 
{
	return  0;
}

void ledClose(JNIEnv * env, jobject cls) 
{

}

jint ledCtrl(JNIEnv * env, jobject cls, jint which, jint status) 
{

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



