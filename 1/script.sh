#!/bin/bash

t=$(mktemp -d)

trap "rm -rf $t; exit 1" SIGHUP SIGINT SIGQUIT SIGTERM
trap "rm -rf $t" EXIT

if [ -z $1 ]; then
  echo Имя файла не указано
  exit 1
fi

string="$(grep -i "Output:" $1)"
string_without_output=${string#//Output:}
file_name=$(echo "$string_without_output" | tr -d '[:space:]')

if [ -z "$file_name" ]; then
  echo Название файла не найдено
  exit 1
fi

cp "$1" "$t"

dir=$(pwd)

cd "$t"

gcc "$1" -o "$file_name"

if [ $? -ne 0 ]; then
  cd "$dir"
  echo Ошибка компиляции!
  exit 1
fi

mv "$file_name" "$dir"
cd "$dir"
echo Готово!
exit 0
