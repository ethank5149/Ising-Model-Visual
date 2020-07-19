@echo off

cd frames
magick mogrify -format png *.pbm
del /Q *.pbm
cd ..