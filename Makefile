# opencv_practice

HTML_DIR = generated_html


all : html
	cd chapter_02/ && $(MAKE)
	cd chapter_03/ && $(MAKE)
	cd chapter_04/ && $(MAKE)
	cd chapter_13/ && $(MAKE)

clean :
	$(RM) -rf $(HTML_DIR)
	cd chapter_02/ && $(MAKE) clean
	cd chapter_03/ && $(MAKE) clean
	cd chapter_04/ && $(MAKE) clean
	cd chapter_13/ && $(MAKE) clean

html : $(HTML_DIR)/index.html

.PHONY : all clean html
######################################################################
$(HTML_DIR)/index.html : Makefile Doxyfile $(wildcard dox/* chapter_01/* chapter_02/* chapter_03/* chapter_04/* chapter_05/* chapter_13/*)
	doxygen
