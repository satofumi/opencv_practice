# opencv_practice

HTML_DIR = generated_html


all :
	doxygen

clean :
	$(RM) -rf $(HTML_DIR)
