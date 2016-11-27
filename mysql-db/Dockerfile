FROM mysql

# According do the documentation section "Initializing a fresh instance"
# (https://hub.docker.com/_/mysql/), everything inside 
# /docker-entrypoint-initdb.d/ is executed when a new container is created

COPY create-database.sql  /docker-entrypoint-initdb.d/

