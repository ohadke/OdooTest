#!/bin/bash

# get thr blocks from app

echo "**" > printdb1
URL_TO_GET=`curl https://api.blockcypher.com/v1/btc/main | grep latest_url | awk -F " " '{print $2}' | sed 's/,/ /g' | sed 's/"//g'`
COUNTER=1
curl $URL_TO_GET | grep -E "hash|height|total|time|relayed_by|prev_block" | sed 's/,/ /g' | sed 's/"//g' >> printdb1
echo "**" >> printdb1

until [ $COUNTER -gt 9 ]
do
  URL_TO_GET=`curl $URL_TO_GET | grep prev_block_url | awk -F " " '{print $2}' | sed 's/,/ /g' | sed 's/"//g'`
  curl $URL_TO_GET | grep -E "hash|height|total|time|relayed_by|prev_block" | sed 's/,/ /g' | sed 's/"//g' >> printdb1
  if [ $COUNTER -ne 9 ]
  then
    echo "**" >> printdb1
  fi
  ((COUNTER++))
done

echo All done
