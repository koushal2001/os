#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

using namespace std;

int main()
{
    key_t key = 1234;

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    char *str = (char *)shmat(shmid, (void *)0, 0);

    cout << "Write Data: ";
    cin >> str;

    printf("Data written in memory: %s\n", str);

    shmdt(str);

    return 0;
}
