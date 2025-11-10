# Étape 1 : Image GCC officielle
FROM gcc:latest

# Étape 2 : Dossier de travail
WORKDIR /app

# Étape 3 : Copier les fichiers du projet
COPY . .

# Étape 4 : Compiler le programme (avec -lm pour les fonctions math)
RUN gcc jerome_cardan.c -o jerome_cardan -lm

# Étape 5 : Commande à exécuter au démarrage
CMD ["./jerome_cardan"]

