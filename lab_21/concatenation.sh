#!/bin/bash
if [ -z "$1" ]
then
s=`df -h | sed -n '$p' | awk '{print $1}'`
echo "Так как Вы не указали параметры, то будут использованы стандартные значения"
size=`sudo blockdev —getsize64 $s`
else
if [ "$1" = "?" ]
then
echo "Конкатенация файлов наименьшей длины до тех пор, пока размер результирующего файла не превысит размера блока заданного устройства"
echo "Использование: ./concat [ФАЙЛОВАЯ СИСТЕМА] [ПУТЬ К ДИРЕКТОРИИ С ФАЙЛАМИ]"
echo "Пример ввода: ./concat /dev/sda1 /home/jasmin"
else
size=`sudo blockdev —getsize64 $1`
fi
fi
if [ -z "$2" ]
then
path=`pwd`
else
path="$2"
fi
ls $path -lSr | grep ^- > sorted_list
sed -i '1d' sorted_list
awk 'NF>1{print $NF}' sorted_list > sorted_list1
while IFS= read -r line
do
size1=`wc -c ~/result | awk '{print $1}'`
if (( size1 <= size ))
then
cat $path/$line » ~/result
else
break
fi
done < sorted_list1
if [ "$1" != "?" ]
then
cat result
fi
