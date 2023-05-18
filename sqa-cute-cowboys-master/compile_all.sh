#!/bin/bash

# Compile back-end
echo "compiling backend..."
make

# Compile front-end
echo -e "\ncompiling frontend..."
cd frontend/
make
cd ..

# Create users file and items file nessesary to run
echo -e "\nCopying users and items file from backup..."
(cat "backup_users_file.txt") > "current_user_accounts_file.txt"
(cat "backup_items_file.txt") > "available_items_file.txt"

echo "Done!"