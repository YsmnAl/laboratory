#!/bin/bash
if [ -z "$1" ]
    then
    s=`df -h | sed -n '4p' | awk '{print $1}'`
    echo "Так как Вы не указали параметры, то будут использованы стандартные значения"
    size=`sudo blockdev --getsize64 $s`
    else
        if [ "$1" = "?" ]
        then
            echo "Конкатенация файлов наименьшей длины до тех пор, пока размер результирующего файла не превысит размера блока заданного устройства"
            echo "Использование: ./concat [ФАЙЛОВАЯ СИСТЕМА] [ПУТЬ К ДИРЕКТОРИИ С ФАЙЛАМИ]"
            echo "Пример ввода: ./concat /dev/sda1 /home/jasmin"
        else
            size=`sudo blockdev --getsize64 $1`
        fi
fi
if [ -z "$2" ]
    then
    path=`pwd`
    else
    path="$2"
fi
list=`ls $path -lSr`
list=$(echo "$list" | sed '1d' | cut -d' ' -f 9)
result=""
while IFS= read -r line
do
    size1="${#result}"
    if (( size1 <= size ))
    then
        file=`echo "$path/$line"`
        file=$(cat $file)
        result=`echo -e "${result}\n${file}"`
    else
        break
    fi
done < <(printf '%s\n' "$list")
if [ "$1" != "?" ]
then
    echo "$result"
fi
