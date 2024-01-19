#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {

    uid_t uID = getuid(); // User ID
    uid_t euID = geteuid(); // effective User ID

    printf("User ID: %d\n", uID);
    printf("effective User ID: %d\n", euID);
    return 0;
}