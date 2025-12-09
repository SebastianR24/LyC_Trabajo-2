# 🦀 Multiplicación de Matrices en Rust: Secuencial vs. Paralelo

Este proyecto es una demostración de rendimiento y concurrencia en **Rust**. Implementa la multiplicación de matrices cuadradas grandes ($N \times N$) utilizando dos enfoques:

1.  **Secuencial:** Un solo hilo (CPU core) realiza todo el trabajo.
2.  **Paralelo:** Utiliza la librería **`Rayon`** para distribuir la carga de trabajo entre todos los núcleos disponibles del procesador de forma segura y eficiente (Work-stealing).

El objetivo es demostrar cómo Rust garantiza la seguridad de memoria (*memory safety*) en contextos concurrentes sin sacrificar el rendimiento.

## 📋 Requisitos

* **Rust y Cargo**: Debes tener instalado el toolchain de Rust.
    * Si no lo tienes, instálalo ejecutando: `curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh` (o visita [rust-lang.org](https://www.rust-lang.org/es)).

## 🚀 Configuración del Proyecto

1.  **Crear el proyecto** (si aún no lo has hecho):
    ```bash
    cargo new matrix_mult
    cd matrix_mult
    ```

2.  **Configurar dependencias**:
    Abre el archivo `Cargo.toml` en la raíz del proyecto y añade las siguientes líneas bajo `[dependencies]`:

    ```toml
    [dependencies]
    rand = "0.8"    # Para generar números aleatorios
    rayon = "1.10"  # Para el paralelismo de datos (Data Parallelism)
    ```

3.  **El Código**:
    Asegúrate de que tu código fuente esté en `src/main.rs`.

## ⚡ Cómo Ejecutar (¡Importante!)

Para ver la verdadera potencia de Rust y obtener mediciones de tiempo realistas, **SIEMPRE** debes compilar en modo **Release**.

### 1. Modo Release (Recomendado para Benchmarks)
Este modo activa todas las optimizaciones del compilador (vectorización, inlining, eliminación de comprobaciones de límites innecesarias).

```bash
cargo run --release
