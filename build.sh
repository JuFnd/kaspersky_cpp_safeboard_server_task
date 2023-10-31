#!/bin/bash

if [ -d "client" ] && [ -d "server" ]; then
    echo "Папки client и server найдены."
else
    echo "Папки client и/или server не найдены."
    exit 1
fi

mkdir -p client/build
mkdir -p server/build

cd client/build
cmake ..
make

mv client_binary ../../

cd ../../

cd server/build
cmake ..
make

mv server_binary ../../

cd ..

echo "Сборка бинарников завершена."
