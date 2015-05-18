#!/bin/sh

echo "Choose a version"
echo "  1 - Terminal"
echo "  2 - Graphical"
echo " 3 - Exit"
read REP

case $REP in

    1)
        ./bin/main1
        ;;

    2)

        ./bin/main2
        ;;

    3)
        exit 0


    *)
        echo "Please answer 1, 2 or 3"
        labyrinthe.sh
        ;;

esac

if [ $? -eq 0 ]
then
    exit 0
fi
