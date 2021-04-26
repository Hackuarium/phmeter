# ---
# To buid Doxygen and PDF documentation all in one
#
all: docman pdf

# ---
# To buid Doxygen HTML and latex documentation of code
#

docman:
	doxygen Doxyfile
	
# ---
# To buid PDF documentation from latex
#
pdf:
	make -C ../docs/latex/

# ---
# To remove all the documentation of code
#
clean:
	rm -r ../docs/latex && rm -r ../docs/html
