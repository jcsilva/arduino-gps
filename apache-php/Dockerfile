FROM php:7.0-apache

RUN apt-get update && apt-get install -y libpq-dev && docker-php-ext-configure pgsql -with-pgsql=/usr/local/pgsql && docker-php-ext-install mysqli json pgsql

# Avoids write/read permission problems
RUN chmod 755 /var/www/html 
