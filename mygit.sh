#!/bin/bash
# by castorga

# Verificar si existe un repositorio en el directorio actual
if [ ! -d .git ]; then
    echo "No se encontró un repositorio en este directorio. Saliendo."
    exit 1
fi

git status

git add .

git status

echo "Message: "
read message

git commit -m "$message"

git push
