#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // wait() でエラーになる場合は、こちらのヘッダを追加

// 背景色用
#define BACKGROUND_RED    "\x1b[41m"
#define BACKGROUND_GREEN  "\x1b[42m"
#define BACKGROUND_YELLOW "\x1b[43m"
#define BACKGROUND_BLUE   "\x1b[44m"

// 文字色用
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"

// リセット (色や装飾を標準に戻す)
#define RESET   "\x1b[0m"

int main()
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        // 子プロセス
        printf(BACKGROUND_RED"Shell PID: %d" RESET, getppid());
        printf("\n================\n");

        // 文字色を変えて表示
        printf(GREEN "Child's Child process\n" RESET);
        printf(GREEN "PID: %d\t" RESET, getpid());
        printf(GREEN "PPID: %d\n" RESET, getppid());

        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            // 孫プロセス
            printf(YELLOW "Child's Child's Child process\n" RESET);
            printf(YELLOW "PID: %d\t" RESET, getpid());
            printf(YELLOW "PPID: %d\n" RESET, getppid());

            pid_t pid3 = fork();
            if (pid3 == 0)
            {
                // 曾孫プロセス
                printf(BLUE "Child's Child's Child's Child process\n" RESET);
                printf(BLUE "PID: %d\t" RESET, getpid());
                printf(BLUE "PPID: %d\n" RESET, getppid());
                exit(3);
            }
            else
            {
                // 孫プロセス(子の終了待ち)
                wait(NULL);
                printf(BLUE "Parent process\n" RESET);
                printf(BLUE "PID: %d\t" RESET, getpid());
                printf(BLUE "PPID: %d\n" RESET, getppid());
            }
            exit(2);
        }
        else
        {
            // 子プロセス(孫の終了待ち)
            wait(NULL);
            printf(YELLOW "Parent process\n" RESET);
            printf(YELLOW "PID: %d\t" RESET, getpid());
            printf(YELLOW "PPID: %d\n" RESET, getppid());
        }
        exit(1);
    }
    else
    {
        // 親プロセス(子の終了待ち)
        wait(NULL);
        printf(GREEN "Parent process\n" RESET);
        printf(GREEN "PID: %d\t" RESET, getpid());
        printf(GREEN "PPID: %d\n" RESET, getppid());
    }
    return 0;
}
