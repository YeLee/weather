#!/bin/bash
arg=${1}
arg=${arg##*/}
arg=${arg/./_}
arg=${arg%.gz}
arg=${arg%.json}
echo $arg

echo "CREATE TABLE city_list(_id INTEGER UNIQUE, name TEXT, country TEXT, coord_lon FLOAT, coord_lat FLOAT);" >${arg}.sql
zcat $1 |sed "s='=''=g" |sed "s=^{\"_id\":\([0-9]\+\),\"name\":\"\([^\"]*\)\",\"country\":\"\([^\"]*\)\",\"coord\":{\"lon\":\(-\?[0-9.]\+\),\"lat\":\(-\?[0-9.]\+\)}}=INSERT INTO city_list VALUES(\1,\'\2\',\'\3\',\4,\5);=g" >>${arg}.sql

sqlite3 ${arg} < ${arg}.sql
rm ${arg}.sql
mv ${arg} weather_config.db
