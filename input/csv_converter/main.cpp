#include <iostream>
#include "listener.h"



using namespace std;

string path_to_listen_directory = "/var/www/laravel/storage/downloads/";

int main() {

    // Start the listener on the directory
    listener(path_to_listen_directory);

    return 0;
}


