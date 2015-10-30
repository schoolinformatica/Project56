#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main() {

    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create a fifo (fifo is a named pipe)*/
    mkfifo(myfifo, 0666);

    /* Writing to the FIFO ( "HI")  */
    fd = open(myfifo, O_WRONLY);
    write(fd, "Hi", sizeof("Hi"));
    close(fd);

    //remove the fifo
    unlink(fd);


    return 0;
}