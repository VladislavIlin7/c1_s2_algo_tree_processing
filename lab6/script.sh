#!/usr/bin/env bash

directory="$1"
target_length="$2"
fill_char="$3"

pad_file_name() {
    local file_path="$1"
    local parent file_name name extension new_name new_path

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

    new_path="${parent}/${new_name}${extension}"

    if [ -e "$new_path" ]; then
        echo "Пропущено: $file_path -> $new_path уже существует"
        return
    fi

    mv "$file_path" "$new_path"
    echo "$file_path -> $new_path"
}

find "$directory" -type f -print0 | while IFS= read -r -d '' file; do
    pad_file_name "$file"
done