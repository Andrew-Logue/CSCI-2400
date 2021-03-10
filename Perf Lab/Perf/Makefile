##
##

CXX	=g++
##
## Use our standard compiler flags for the course...
## You can try changing these flags to improve performance.
##
## changed -O0 to -O3 and added -mavx2 so that I could use AVX2 registers
CXXFLAGS= -g -O3 -mavx2 -fno-omit-frame-pointer -Wall

goals: judge
	@echo "Done"

filter: FilterMain.cpp Filter.cpp cs1300bmp.cc cs1300bmp.h Filter.h rdtsc.h
	$(CXX) $(CXXFLAGS) -o filter FilterMain.cpp Filter.cpp cs1300bmp.cc

##
## Parameters for the test run
##
FILTERS = gauss.filter vline.filter hline.filter emboss.filter
IMAGES = boats.bmp blocks-small.bmp
TRIALS = 1 2 3 4

judge: filter
	-./Judge -p ./filter -i boats.bmp
	-./Judge -p ./filter -i blocks-small.bmp

test:	filter
	@find filtered*bmp | xargs -I @@ bash -c 'cmp --silent @@ tests/@@ && echo @@ looks correct. || echo INCORRECT: @@ does not match the reference image tests/@@.'

clean:
	-rm -f *.o
	-rm -f filter
	-rm -f filtered-*.bmp