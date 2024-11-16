# TP 01 - Génération de courbe

**Auteur**: Raquel Maciel Coelho de Sousa 
**Turme**: 2026  
**Cours**: Systèmes d'exploitation  
**TP groupe**: 4  

## Compilation

Pour compiler le programme, assurez-vous d'être dans le dossier `tp01` et exécutez la commande suivante:

```bash
make
```

Cela générera un exécutable nommé `plot`.

## Exécution

Pour exécuter le programme, lancez simplement :

```bash
./plot
```

Suivez les instructions à l’écran pour entrer une borne pour l’intervalle d’affichage de la courbe.

## Test

1. Exécutez le programme `plot` en utilisant `./plot`.
2. Entrez différentes valeurs de borne pour observer les graphiques générés par Gnuplot.
3. Pour voir la couverture (overlay) des processus, ouvrez un autre terminal et lancez `htop`.
4. Dans `htop`, filtrez les processus `iplot` et `gnuplot` pour observer leur comportement pendant l'exécution.

## Nettoyage

Pour supprimer les fichiers objets et l'exécutable, utilisez la commande :

```bash
make clean
```