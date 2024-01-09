#!/bin/bash
# by castorga

if [ ! -d .git ]; then
    echo "Repo not found!"
    exit 1
fi

git status

git add .

git status

echo "Message: "
read message

git commit -m "$message"

git push
