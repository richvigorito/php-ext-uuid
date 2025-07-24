FROM debian:bookworm

##  src: https://github.com/bogkonstantin/php-extension-hello-world/blob/main/Dockerfile

RUN apt update \
    && apt install -y \
    build-essential \
    autoconf \
    libtool \
    bison \
    re2c \
    pkg-config \
    git \
    libxml2-dev \
    libsqlite3-dev \
    gdb \
    nano \
    uuid-dev
    procps

RUN git clone https://github.com/php/php-src.git --branch=php-7.4.33 --depth=1 \
    && cd php-src \
    && ./buildconf --force \
    && ./configure --enable-debug \
    && make -j $(nproc) \
    && make install \
    && php -v

COPY ./ext /php-src/ext/uuid

WORKDIR /php-src

RUN cd /php-src/ext/uuid \
    && phpize \
    && LDFLAGS="-luuid" ./configure --enable-uuid
    && make \
    && make test \
    && echo "extension=/php-src/ext/uuid/modules/uuid.so" >> /usr/local/lib/php.ini
