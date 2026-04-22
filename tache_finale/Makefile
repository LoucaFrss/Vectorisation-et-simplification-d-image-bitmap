#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = $(INCLUDEOPTS) -O3 -march=native -flto -Wall -Wextra
LDFLAGS = -flto
# liste des executables
EXECUTABLES =  simplification_segment simplification_bezier3 simplification_bezier2 


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geom2d.o : geom2d.c geom2d.h liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		
contour.o : contour.c contour.h  image.h geom2d.h liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geom2d"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
		

eps.o : eps.c eps.h bezier.h  liste.h bezier.h segment.h

liste.o : liste.c liste.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module liste"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


bezier.o : bezier.c geom2d.h liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

segment.o : segment.c segment.h geom2d.h liste.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module segment"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


simplification_segment.o : simplification_segment.c liste.h geom2d.h contour.h image.h eps.h bezier.h segment.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_segment"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier3.o : simplification_bezier3.c liste.h geom2d.h contour.h image.h eps.h bezier.h segment.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_bezier2.o : simplification_bezier2.c liste.h geom2d.h contour.h image.h eps.h bezier.h segment.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_bezier2"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


########################################################
# regles explicites de creation des executables

simplification_segment : simplification_segment.o liste.o geom2d.o contour.o image.o eps.o bezier.o segment.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $(LDFLAGS) $^ $(LDOPTS) -o $@

simplification_bezier3 : simplification_bezier3.o  geom2d.o contour.o image.o bezier.o liste.o eps.o segment.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $(LDFLAGS) $^ $(LDOPTS) -o $@

simplification_bezier2 : simplification_bezier2.o  geom2d.o contour.o image.o bezier.o liste.o eps.o segment.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $(LDFLAGS) $^ $(LDOPTS) -o $@
# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
