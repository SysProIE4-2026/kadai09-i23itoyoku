/*
 *  myenv.c : env コマンドのクローン
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#ifdef __linux__
#include "myputenv.h"
#endif

extern char **environ;

int main(int argc, char *argv[]) {
    int i = 1;

    while (argv[i] != NULL && strchr(argv[i], '=') != NULL) {
#ifdef __linux__
        if (_putenv(argv[i]) != 0) {
#else
        if (putenv(argv[i]) != 0) {
#endif
            perror("putenv");
            exit(1);
        }
        i++;
    }

    if (argv[i] == NULL) {
        for (int j = 0; environ[j] != NULL; j++) {
            printf("%s\n", environ[j]);
        }
    } else {
        execvp(argv[i], &argv[i]);
        
        perror(argv[i]);
        exit(1);
    }

    return 0;
}

/* 実行例

ここに実行例を書く
./myenv
TMPDIR=/var/folders/y4/q1tsjrq535b4kx96j13k_35h0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=FDA04482-94AC-4ADE-A6EF-3099C5C735D1
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.QQ4QzLAAT2/Listeners
SECURITYSESSIONID=186af
.......続いた

./myenv FOO=bar sh -c 'echo $FOO'
bar

./myenv FOO=bar
TMPDIR=/var/folders/y4/q1tsjrq535b4kx96j13k_35h0000gn/T/
__CFBundleIdentifier=com.apple.Terminal
XPC_FLAGS=0x0
LaunchInstanceID=FDA04482-94AC-4ADE-A6EF-3099C5C735D1
TERM=xterm-256color
SSH_AUTH_SOCK=/var/run/com.apple.launchd.QQ4QzLAAT2/Listeners
SECURITYSESSIONID=186af
...(1個目のと同じ動作)

./myenv FOO ls             
FOO: No such file or directory
*/
