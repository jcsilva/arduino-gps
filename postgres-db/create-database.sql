create database gpstrack;

\connect gpstrack;

create table gpspos (id serial not null primary key, lat_coord varchar(20), lon_coord varchar(20));
