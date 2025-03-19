LOG='LOG_LEVEL=DEBUG'
#LOG='LOG_LEVEL=INFO'
#LOG='LOG_LEVEL=SILENT'

all: wordcount countdown addup

wordcount: wordcount.c
	gcc wordcount.c -o wordcount

countdown: countdown.c seethe.h
	gcc countdown.c -D$(LOG) -o countdown

addup: addup.c seethe.h
	gcc addup.c -D$(LOG) -o addup

rebuild: clean all

clean:
	rm wordcount countdown addup
