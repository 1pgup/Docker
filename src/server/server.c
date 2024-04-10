#include <fcgi_stdio.h>
#include <stdlib.h>

int main(void) {
    while (FCGI_Accept() >= 0) {
        printf("Content-Type: text/html\r\n\r\n");
        printf("<html><head><title>Hello World FastCGI</title></head>");
        printf("<body><h1>Hello World!</h1></body></html>");
    }

    return 0;
}
