FROM php:7.0-apache
RUN docker-php-ext-install mysqli json

# Avoids write/read permission problems
RUN chmod 755 /var/www/html 
