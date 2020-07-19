@echo off

cd frames
ffmpeg -i frame%%d.pbm -vcodec mpeg4 output.avi
del /Q *.pbm
cd ..

REM ffmpeg -r 30 -f image2 -s %1x%2 -i frames/frame%%d.png -vcodec libx264 -crf 25  -pix_fmt yuv420p movies/movie.mp4
REM cd frames
REM del /Q *.png
REM cd ..