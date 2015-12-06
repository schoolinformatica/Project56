#include <iostream>
#include "listener.h"



using namespace std;

string path_to_listen_directory = "/var/www/laravel/storage/downloads/";

<<<<<<< HEAD
int main() {
=======
    // start the listener on the given path
    listener("/home/cooperatio/filedatabase/");
>>>>>>> 71731456bbe7a3bbc39693cd079a9a97716cc065

    // Start the listener on the directory
    listener(path_to_listen_directory);

    return 0;
}


