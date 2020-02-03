#/bin/sh

test=`curl -V | grep 'curl'`

if [ -z "$test" ]; then
  exit 1
else
  exit 0
fi

