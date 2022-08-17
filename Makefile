PANDOC=/usr/bin/pandoc

PANDOC_OPTIONS= -V 'mainfont:/usr/share/fonts/TTF/CascadiaCodePL.ttf'
         

PANDOC_HTML_OPTIONS=--to html5
PANDOC_PDF_OPTIONS= --pdf-engine pdflatex 
PANDOC_DOCX_OPTIONS=
PANDOC_RTF_OPTIONS=
PANDOC_ODT_OPTIONS=
PANDOC_EPUB_OPTIONS=--to epub3

PANDOC_BUILD_DIR=pandoc
TARGET=ComputerSystemsNotes
PDF_TARGET=$(PANDOC_BUILD_DIR)/$(TARGET).pdf
HTML_TARGET=$(PANDOC_BUILD_DIR)/$(TARGET).html

SRC := src/SUMMARY.md \
			 src/01tour.md \
			 src/part01intro.md \
			 src/02info_repr_manip.md \
			 src/03machine_representation.md \
			 src/04processor_architecture.md \
			 src/05program_optimization.md \
			 src/06memory_hierarchy.md \
			 src/part02intro.md \
			 src/07linking.md \
			 src/08control_flow.md \
			 src/09virtual_memory.md \
			 src/part03intro.md \
			 src/10system_level_io.md \
			 src/11network_programming.md \
			 src/12concurrent_programming.md \

.PHONY: all clean

all: pdf
	

$(PANDOC_BUILD_DIR):
	mkdir $(PANDOC_BUILD_DIR)


pdf: $(PDF_TARGET)
$(PDF_TARGET): $(PANDOC_BUILD_DIR)
	$(PANDOC) $(PANDOC_OPTIONS) $(PANDOC_PDF_OPTIONS) -o $(PDF_TARGET) $(SRC) 

html: $(HTML_TARGET)
$(HTML_TARGET): $(PANDOC_BUILD_DIR)
	$(PANDOC) $(PANDOC_OPTIONS) $(PANDOC_HTML_OPTIONS) -o $(HTML_TARGET) $(SRC) 

mdbook:
	mdbook build
serve:
	mdbook serve -p 3003

clean:
	rm -rf $(PANDOC_BUILD_DIR)


