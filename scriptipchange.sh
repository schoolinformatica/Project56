#!/bin/bash 

1=$(docker inspect $CID | grep IPAddress | cut -d '"' -f 4)

replacestring=$(cat .env | grep DB_HOST )
newstring='DB_HOST='$1

sed -i 's/'$replacestring'/'$newstring'/g' .env


replacestring1=$(cat credentials.pgconf | grep hostip )
newstring1='hostip: '$1

sed -i "s/$replacestring1/$newstring1/g" credentials.pgconf

