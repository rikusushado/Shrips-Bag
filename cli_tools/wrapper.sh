#!/usr/bin/env bash

APP_DIR="/opt/shrips-bag/bin"

if [ -z "$1" ]; then
    echo "Error: No command specified."
    echo "Available commands:"
    ls -1 "$APP_DIR" 2>/dev/null | sed 's/^/  /' | grep -vE "wrapper"
    exit 1
fi

if [ ! -x "$APP_DIR/$1" ]; then
    echo "Error: Command '$1' not found in $APP_DIR"
    exit 1
fi

"$APP_DIR/$1" "${@:2}"
