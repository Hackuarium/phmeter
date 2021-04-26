PHMETER Code on PlatformIO
===

This code is provided with Doxygen documentation, so you can run this command to build a new documentation if the comments into the code changed:

- Go to *src* folder and run:

```bash
$ make clean // If you want to remove the old documentation.
```

After that, you need to create the new documentation, please run:

```bash
$ make all // Create Doxygen documentation and refman.pdf.
```

---

Requirements
---
To run all the commands inside Doxyfile and Makefile, you need to install:

- Doxygen.
- LaTeX.
- PDFlatex.

### Install software on Ubuntu

- [Doxygen](https://www.doxygen.nl/index.html):

```bash
$ sudo apt-get install doxygen // To install Doxygen.
```

(See: [How to install Doxygen on Ubuntu](https://askubuntu.com/questions/1291874/how-to-install-doxygen-on-ubuntu-20-04) for more information).

- [LaTeX](https://www.latex-project.org/):
```bash
$ $ sudo apt install texlive-full // To install LaTeX full installation.
```

You can install other alternatives to full installation LaTeX, please see: [How to install LaTex on Ubuntu](https://linuxconfig.org/how-to-install-latex-on-ubuntu-20-04-focal-fossa-linux).