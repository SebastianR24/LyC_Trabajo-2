# λ Multiplicación de Matrices en Haskell: Evaluación Paralela y Secuencial

Este proyecto demuestra cómo implementar operaciones intensivas (multiplicación de matrices $N \times N$) en un lenguaje puramente funcional. Compara dos enfoques:

1.  **Secuencial:** Uso estándar de listas y evaluación perezosa.
2.  **Paralelo:** Uso de **Estrategias de Evaluación** (`Control.Parallel.Strategies`) para distribuir el cálculo de las filas de la matriz entre varios núcleos, sin cambiar la lógica del algoritmo.

## 📋 Requisitos

* **GHC** (Glasgow Haskell Compiler): El compilador estándar.
* **Cabal**: El gestor de paquetes (generalmente viene con GHC).

## ⚙️ Instalación de Dependencias

Haskell necesita dos librerías externas que no siempre están activas por defecto para scripts simples: `parallel` y `deepseq`.

Ejecuta este comando en tu terminal para instalarlas en tu entorno:

```bash
cabal install --lib parallel deepseq random
```
* **parallel**: Proporciona las herramientas para parList y rdeepseq.
* **deepseq**: Necesaria para forzar la evaluación completa de los datos (evitar que el tiempo marque 0.000s).

## 🛠️ Cómo Compilar y Ejecutar
El sistema de runtime de Haskell (RTS) necesita opciones específicas para habilitar el multihilo.

### 1. Compilar:

Bash
```shell
ghc -O2 -threaded -rtsopts MatrixMult.hs
```
* **`-O2`**: Optimización alta.
* **`-threaded`**: Usa el runtime multihilo.
* **`-rtsopts`**: Permite pasar opciones al runtime desde la línea de comandos.

### Ejecutar:

Bash
```shell
./MatrixMult +RTS -N4
```
* **`+RTS -N4`**: Le dice al programa que use 4 núcleos del procesador (o los que tengas disponibles).
