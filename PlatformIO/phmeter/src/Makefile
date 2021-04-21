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
# To buid Doxygen and PDF documentation all in one
#
all: docman pdf

clean:
	rm -r ../docs/latex && rm -r ../docs/html
