#!/bin/bash
for entry in "text"/*
do
  pico2wave -w=audio/${entry:5:-4}.wav "$(cat $entry)"
done


