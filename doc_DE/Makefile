INCFILES = taborg*.tex pscpu.tex pscomm.tex

all: as.doc as.html as.ps

as.ps: as.dvi
	dvips as -o

as.dvi: as.tex $(INCFILES)
	latex as
	latex as
	makeindex as
	latex as

as.doc: as.tex  $(INCFILES) $(TEX2DOC)
	$(TEX2DOC) as.tex as.doc
	$(TEX2DOC) as.tex as.doc

as.html: as.tex  $(INCFILES) $(TEX2HTML)
	$(TEX2HTML) as.tex as.html
	$(TEX2HTML) as.tex as.html

clean:
	$(RM) as.dvi
	$(RM) as.ps
	$(RM) as.i*
	$(RM) *log
	$(RM) as.aux
	$(RM) as.toc
	$(RM) *~
	$(RM) DEADJOE
	$(RM) as.doc
	$(RM) as.dtoc
	$(RM) as.daux
	$(RM) as.html
	$(RM) as.htoc
	$(RM) as.haux
	$(RM) commpseudo.tex cpupseudo.tex
