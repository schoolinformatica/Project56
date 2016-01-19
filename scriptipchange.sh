#!/bin/bash 

ip=$(docker inspect postgres | grep IPAddress | cut -d '"' -f 4)

replacestring=$(cat .env | grep DB_HOST )
newstring='DB_HOST='$ip

sed -i 's/'$replacestring'/'$newstring'/g' .env


replacestring1=$(cat credentials.pgconf | grep hostip )
newstring1='hostip: '$ip

sed -i "s/$replacestring1/$newstring1/g" credentials.pgconf

