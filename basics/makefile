CC=g++
CFLAGS=-I/usr/local/include/opencv4 
LDFLAGS=-lstdc++ -lopencv_imgcodecs -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_videoio -lopencv_video

showim.o: showim.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

showvid.o: showvid.cpp
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

vidtrackbar.o: vidwithtrackbar.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

transforms.o: transforms.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

test.o: test.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

mycanny.o: mycanny.cpp utils.hpp utils.cpp
	$(CC) $(CFLAGS) mycanny.cpp utils.cpp -o $@ $(LDFLAGS)

laplacian.o: laplacian.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

houghlines.o: houghlines.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

ransac.o: ransac.cpp 
	$(CC) $(CFLAGS) $? -o $@ $(LDFLAGS)

clean:
	rm -f *.o