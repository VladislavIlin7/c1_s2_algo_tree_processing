#!/usr/bin/env bash

if [ "$#" -ne 3 ]; then
    echo "Было введено $# аргументов. Нужно 3 аргумента: <каталог> <длина> <знак>"
    exit 1
fi

directory="$1"
target_length="$2"
fill_char="$3"

if [ ! -d "$directory" ]; then
    echo "$directory - не существует или не является директорией"
    exit 1
fi

if ! [[ "$target_length" =~ ^[1-9][0-9]*$ ]]; then
    echo "$target_length - длина должна быть положительным целым числом"
    exit 1
fi

if [ "${#fill_char}" -ne 1 ]; then
    echo "$fill_char - знак должен состоять из одного символа"
    exit 1
fi

directory="$(cd "$directory" && pwd)"

pad_file_name() {
    local file_path="$1"
    local parent
    local file_name
    local name
    local extension
    local new_name
    local new_path

    parent="$(dirname "$file_path")"
    file_name="$(basename "$file_path")"

    if [[ "$file_name" == *.* && "$file_name" != .* ]]; then
        name="${file_name%.*}"
        extension=".${file_name##*.}"
    else
        name="$file_name"
        extension=""
    fi

    if [ "${#name}" -ge "$target_length" ]; then
        return
    fi

    new_name="$name"
    while [ "${#new_name}" -lt "$target_length" ]; do
        new_name="${new_name}${fill_char}"
    done

    new_name="${new_name}${extension}"
    new_path="${parent}/${new_name}"

    if [ -e "$new_path" ]; then
        echo "Пропущено: $file_path -> $new_path уже существует"
        return
    fi

    mv "$file_path" "$new_path"
    echo "$file_path -> $new_path"
}

walk() {
    local current_dir="$1"
    local item

    for item in "$current_dir"/* "$current_dir"/.[!.]* "$current_dir"/..?*; do
        [ -e "$item" ] || continue

        if [ -d "$item" ]; then
            walk "$item"
        elif [ -f "$item" ]; then
            pad_file_name "$item"
        fi
    done
}

walk "$directory"
