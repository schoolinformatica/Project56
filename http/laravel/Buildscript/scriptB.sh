#/!/bin/bash
echo "Cloning the Project56 github repo if it isnt there."
if [ ! -d "project56" ]
then
	echo "Repo not yet there, starting to clone."
	git init
	git clone https://github.com/cooperatio/project56
	git checkout https://github.com/cooperatio/project56 feature-2.0
else
	echo "Repo already there."
	cd project56/http/
	git pull https://github.com/cooperatio/project56 feature-2.0
fi

#php mess detector
if [ ! -f /usr/bin/phpmd ]
then
	echo "Retrieving phpmd"
        wget http://static.phpmd.org/php/latest/phpmd.phar
        chmod +x phpmd.phar
        sudo mv phpmd.phar /usr/bin/phpmd
else
        echo "Phpmd phar already installed."
fi

#phpunit
if  [ ! -f /usr/bin/phpunit ]
then
        wget https://phar.phpunit.de/phpunit.phar
        chmod +x phpunit.phar
        sudo mv phpunit.phar /usr/bin/phpunit
else
        echo "PHPUnit phar already installed."
fi


#phpdox 
if  [ ! -f /usr/bin/phpdox ]
then
	wget https://github.com/theseer/phpdox/releases/download/0.8.0/phpdox-0.8.0.phar
	chmod +x phpdox-0.8.0.phar
	sudo mv phpdox-0.8.0.phar /usr/bin/phpdox
else
	echo "PHPDox phar already installed."
fi

#phploc 
if  [ ! -f /usr/bin/phploc ]
then
        wget https://phar.phpunit.de/phploc.phar
        chmod +x phploc.phar
        sudo mv phploc.phar /usr/bin/phploc
else
        echo "PHPLoc phar already installed."
fi


echo "Building using Ant!"
ant -buildfile build.xml
#todo: Select parts to build
