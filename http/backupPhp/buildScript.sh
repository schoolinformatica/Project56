#/!/bin/bash
echo "Cloning the Project56 github repo if it isnt there."
if [ ! -d "Project56" ]
then
        echo "Repo not yet there, starting to clone."
        git init
        git clone https://github.com/cooperatio/project56
        git checkout https://github.com/cooperatio/project56 feature-4.0
else
        echo "Repo already there."
        cd Project56/http/laravel/
        git pull https://github.com/cooperatio/project56 feature-4.0
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

echo "Building using Ant! Do you want to build fully, or just run the unit tests?"
 read -p "Do you want to build fully?" yn
    case $yn in
        [Yy]* ) ant full-build; break;;
        [Nn]* ) ant phpunit;;
        * ) ant full-build;;
    esac

echo "Since the build completed succesfully, we are going to copy the contents of http/Laravel to /var/www/laravel"

#postgres check
echo "Before we copy everything, I'm going to make sure the psql and nginx processes are running."

if ! [[ $(pgrep -n postgres) == "" ]]
then
  echo "Postgres is not running, so I will start it."
  sudo service postgresql restart
else
  echo "Postgres is running nicely, no need to do anything."
fi

#nginx check
if ! [[ $(pgrep -n nginx) == "" ]]
then
  echo "Nginx is not running, so I will start it."
  sudo service nginx restart
else
  echo "Nginx is running nicely, no need to do anything."
fi


echo "All required processes are now running! One last check to see if all dependencies are up to date: "
cd /var/www/laravel/
sudo composer update
