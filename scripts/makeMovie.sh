#!/bin/bash
ffmpeg -framerate  -i $1 -c:v libx264 -r 30 -pix_fmt yuv420p $2
