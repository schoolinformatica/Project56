#include <iostream>
#include "listener.h"

using namespace std;

int main() {

    // start the listener on the given path
    listener("/var/www/laravel/storage/uploads/");

    return 0;
}

