# Template de TP
# Todo

- Auto-install third parties (glm/assimp)
- simpler camera
- simple template shader

## Dépendances

- cmake (Outil pour créer des projets cross-plateforme)
- glm (Bibliothèque de mathématiques adaptées à OpenGL)
- glut
- assimp (Bibliothèque d'import de modèles 3D)

Sur Ubuntu (avec les droits administateurs):
```
apt install cmake freeglut3-dev libassimp-dev libglm-dev
```

Si vous n'avez pas les droits il vous faut compiler les deux sous-modules dans le dossier "thirdparties".
```
git submodule update --init --recursive
```
Normalement le script de compilation s'occupe de compiler les deux modules une fois que le code est téléchargé.

## Compilation

```
mkdir build
cd build
cmake ..
```
