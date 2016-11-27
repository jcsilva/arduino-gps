create database gpstrack;
use gpstrack;
create table gpspos (id int not null auto_increment primary key, lat_coord varchar(20), lon_coord varchar(20));


CREATE USER "gpsuser"@"%" IDENTIFIED BY "1234";
GRANT ALL PRIVILEGES ON gpstrack.* TO "gpsuser"@"%" WITH GRANT OPTION;
