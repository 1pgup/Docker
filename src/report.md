# Simple Docker

## Содержание

1. [Готовый докер](#part-1-готовый-докер)
2. [Операции с контейнером](#part-2-операции-с-контейнером)
3. [Мини веб-сервер](#part-3-мини-веб-сервер)
4. [Свой докер](#part-4-свой-докер)
5. [Dockle](#part-5-dockle)
6. [Базовый Docker Compose](#part-6-базовый-docker-compose)

## Part 1. Готовый докер

1. Загружаем официальный докер-образ **nginx** с помощью команды `docker pull nginx`.

![docker pull nginx](../misc/report_images/part1-1.png)

2. Проверяем наличие докер-образа через `docker images`.

![docker images](../misc/report_images/part1-2.png)

3. Запускаем докер-образ через `docker run -d nginx`

![docker run -d nginx](../misc/report_images/part1-3.png)

4. Проверяем, что образ запустился через `docker ps`.

![docker ps](../misc/report_images/part1-4.png)

5. Смотрим информацию о контейнере через `docker inspect [container_id]`.

![docker inspect](../misc/report_images/part1-5.png)

6. По выводу команды определяем размер контейнера, список замапленных портов и ip контейнера.

![docker inspect](../misc/report_images/part1-6.png)

![docker inspect](../misc/report_images/part1-7.png)

![docker inspect](../misc/report_images/part1-8.png)

7. Останавливаем докер образ через `docker stop [container_id]`.

![docker stop](../misc/report_images/part1-9.png)

8. Проверяем, что образ остановился через `docker ps`.

![docker ps](../misc/report_images/part1-10.png)

9. Запускаем докер с портами 80 и 443 в контейнере, замапленными на такие же порты на локальной машине, через команду *run*.

![docker run](../misc/report_images/part1-11.png)

10. Проверяем, что в браузере по адресу *localhost:80* доступна стартовая страница **nginx**.

![localhost:80](../misc/report_images/part1-12.png)

11. Перезапускаем докер контейнер через `docker restart [container_id]` и проверяем , что контейнер запустился.

![docker run](../misc/report_images/part1-13.png)

## Part 2. Операции с контейнером

1. Читаем конфигурационный файл *nginx.conf* внутри докер контейнера через команду *exec*.

![exec cat](../misc/report_images/part2-1.png)

2. Создаём на локальной машине файл *nginx.conf* и настраиваем в нем по пути */status* отдачу страницы статуса сервера **nginx**..

![nginx.conf](../misc/report_images/part2-2.png)

3. Копируем созданный файл *nginx.conf* внутрь докер-образа через команду `docker cp`.

![docker cp](../misc/report_images/part2-3.png)

4. Перезапускаем **nginx** внутри докер-образа через команду *exec*.

![nginx -s reload](../misc/report_images/part2-4.png)

5. Проверяем, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.

![localhost:80/status](../misc/report_images/part2-5.png)

6. Экспортируем контейнер в файл *container.tar* через команду *export*.

![docker export](../misc/report_images/part2-6.png)

7. Останавливаем контейнер.

![docker stop](../misc/report_images/part2-7.png)

8. Удаляем образ через `docker rmi --force [image_id]`, не удаляя перед этим контейнеры.

![docker rmi](../misc/report_images/part2-8.png)

9. Удаляем остановленный контейнер.

![docker rm](../misc/report_images/part2-9.png)

10. Импортируем контейнер обратно через команду *import*.

![docker import](../misc/report_images/part2-10.png)

11. Запускаем импортированный контейнер.

![docker run](../misc/report_images/part2-12.png)

12. Проверяем, что по адресу *localhost:80/status* отдается страничка со статусом сервера **nginx**.

![localhost:80/status](../misc/report_images/part2-11.png)

## Part 3. Мини веб-сервер

1. Пишем мини-сервер на **C** и **FastCgi**, который будет возвращать простейшую страничку с надписью `Hello World!`.

![fastcgi server](../misc/report_images/part3-1.png)

2. Пишем свой *nginx.conf*, который будет проксировать все запросы с 81 порта на *127.0.0.1:8080*.

![nginx.conf](../misc/report_images/part3-2.png)

3. Перезапускаем nginx с написанным файлом nginx.conf (может понадобиться команда `sudo fuser -k 81/tcp`)

![nginx -c](../misc/report_images/part3-3.png)

4. После компиляции .c файла (`gcc -o server.cgi server.c -lfcgi`) запускаем написанный мини-сервер через *spawn-fcgi* на порту 8080 (может понадобиться команда `sudo fuser -k 8080/tcp`).

![spawn-fcgi](../misc/report_images/part3-4.png)

5. Проверяем, что в браузере по *localhost:81* отдается написанная страничка.

![localhost:81](../misc/report_images/part3-5.png)

## Part 4. Свой докер

1. Пишем свой докер-образ, который:
    1) собирает исходники мини сервера на FastCgi из [Части 3](#part-3-мини-веб-сервер);
    2) запускает его на 8080 порту;
    3) копирует внутрь образа написанный *./nginx/nginx.conf*;
    4) запускает **nginx**.

![Dockerfile](../misc/report_images/part4-1.png)

2. Собираем написанный докер-образ через `docker build` при этом указав имя и тег.

![docker build](../misc/report_images/part4-2.png)

3. Проверяем через `docker images`, что все собралось корректно.

![docker images](../misc/report_images/part4-3.png)

4. Запускаем собранный докер-образ с маппингом 81 порта на 80 на локальной машине и маппингом nginx.conf

![docker run](../misc/report_images/part4-4.png)

5. Проверяем, что по localhost:80 доступна страничка написанного мини сервера.

![localhost:80](../misc/report_images/part4-5.png)

6. Дописываем в *./nginx/nginx.conf* проксирование странички */status*, по которой надо отдавать статус сервера **nginx**.

![nginx.conf](../misc/report_images/part4-6.png)

7. Перезапускаем контейнер.

![docker restart](../misc/report_images/part4-9.png)

8. Проверяем, что nginx.conf изменился

![nginx.conf](../misc/report_images/part4-7.png)

9. Проверяем, что теперь по *localhost:80/status* отдается страничка со статусом **nginx**

![localhost:80/status](../misc/report_images/part4-8.png)

## Part 5. **Dockle**

1. Сканируем образ из предыдущего задания через `dockle [image_id]`.

![dockle old](../misc/report_images/part5-1.png)

2. Исправляем образ так, чтобы при проверке через **dockle** не было ошибок и предупреждений.

![Dockerfile fixed](../misc/report_images/part5-2.png)

3. Вывод команды `dockle` для исправленного Dockerfile

![dockle new](../misc/report_images/part5-3.png)

## Part 6. Базовый **Docker Compose**

1. Пишем файл *docker-compose.yml*, с помощью которого:
    1) Поднимаем докер-контейнер из [Части 5](#part-5-инструмент-dockle) _(он должен работать в локальной сети, т.е. не нужно использовать инструкцию **EXPOSE** и мапить порты на локальную машину)_.
    2) Поднимаем докер-контейнер с **nginx**, который будет проксировать все запросы с 8080 порта на 81 порт первого контейнера.
    3) Мапим 8080 порт второго контейнера на 80 порт локальной машины.

![docker-compose](../misc/report_images/part6-1.png)

* Нужно закомментировать некоторые строчки в Dockerfile.fixed 

![Dockerfile.fixed](../misc/report_images/part6-2.png)

* Вид nginx.conf файла для второго контейнера

![nginx.conf](../misc/report_images/part6-6.png)

2. Останавливаем все запущенные контейнеры командой `docker stop $(docker ps -a -q)`
3. Собираем и запускаем проект с помощью команд `docker-compose build` и `docker-compose up`.

![docker-compose build](../misc/report_images/part6-3.png)

![docker-compose up](../misc/report_images/part6-4.png)

4. Проверяем, что в браузере по *localhost:80* отдается написанная страничка, как и ранее.

![localhost:80](../misc/report_images/part6-5.png)
