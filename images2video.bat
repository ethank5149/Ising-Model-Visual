@echo off

ffmpeg -r 30 -f image2 -s %1x%2 -i frames/frame%%d.png -vcodec libx264 -crf 25  -pix_fmt yuv420p movies/movie.mp4

cd frames
del /Q *.png
cd ..