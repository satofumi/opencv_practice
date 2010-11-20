# opencv_practice

HTML_DIR = generated_html


all : html
	cd chapter_02/ && $(MAKE)

clean :
	$(RM) -rf $(HTML_DIR)
	cd chapter_02/ && $(MAKE) clean

html : $(HTML_DIR)/index.html

.PHONY : all clean html
######################################################################
$(HTML_DIR)/index.html : Makefile Doxyfile $(wildcard dox/* chapter_01/* chapter_02/*)
	doxygen
