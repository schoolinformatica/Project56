#!/bin/bash 

cd ~/http/laravel

replacestring=$(cat .env | grep DB_HOST )
newstring='DB_HOST='$1

sed -i 's/'$replacestring'/'$newstring'/g' .env

cd ~/processing

replacestring1=$(cat credentials.pgconf | grep hostip )
newstring1='hostip: '$1

sed -i "s/$replacestring1/$newstring1/g" credentials.pgconf

