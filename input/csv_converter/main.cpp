#include <iostream>
#include "listener.h"

using namespace std;

int main() {
    //NOTE: Always call listener with an extra backslash. 
    //IE: etc/etc/etc/ instead of etc/etc/etc
    listener("/var/www/laravel/storage/uploads/");
    return 0;
}
