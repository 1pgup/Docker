FROM nginx:latest

RUN apt-get update && apt-get install -y gcc libfcgi-dev spawn-fcgi

COPY ./server/server.c /home

RUN gcc -o /home/server.cgi /home/server.c -lfcgi

COPY ./server/nginx/ /etc/nginx/

EXPOSE 8080

CMD nginx && spawn-fcgi -p 8080 -n /home/server.cgi
