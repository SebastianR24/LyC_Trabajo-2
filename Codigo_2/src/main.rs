use rand::Rng;
use rayon::prelude::*; // Importante para acceder a .into_par_iter()
use std::time::Instant;

// Tipo de alias para simplificar (Matriz = Vector de Vectores)
type Matrix = Vec<Vec<f64>>;

// Función para inicializar una matriz con valores aleatorios
fn initialize_matrix(n: usize) -> Matrix {
    let mut rng = rand::thread_rng();
    // Creamos n filas, cada una con n elementos aleatorios
    (0..n)
        .map(|_| (0..n).map(|_| rng.gen_range(0.0..10.0)).collect())
        .collect()
}

// -----------------------------------------------------------------------------
// Versión Secuencial (un solo hilo)
// -----------------------------------------------------------------------------
fn multiply_sequential(a: &Matrix, b: &Matrix) -> Matrix {
    let n = a.len();
    // Pre-asignamos la matriz resultado con ceros
    let mut c = vec![vec![0.0; n]; n];

    for i in 0..n {
        for j in 0..n {
            let mut sum = 0.0;
            for k in 0..n {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
    c
}

// -----------------------------------------------------------------------------
// Versión Paralela con Rayon (Rust Way)
// -----------------------------------------------------------------------------
fn multiply_parallel(a: &Matrix, b: &Matrix) -> Matrix {
    let n = a.len();

    // into_par_iter() convierte el rango (0..n) en un iterador paralelo.
    // Rayon distribuye estos índices (las filas) entre los núcleos disponibles.
    (0..n)
        .into_par_iter()
        .map(|i| {
            // Este bloque se ejecuta en paralelo para diferentes 'i'
            let mut row = vec![0.0; n];
            for j in 0..n {
                let mut sum = 0.0;
                for k in 0..n {
                    sum += a[i][k] * b[k][j];
                }
                row[j] = sum;
            }
            row // Retornamos la fila calculada
        })
        .collect() // Rayon junta todas las filas en el orden correcto en un Vec<Vec<f64>>
}

fn main() {
    let n = 500; // Tamaño de la matriz

    println!("Iniciando multiplicación de matrices de {}x{}", n, n);

    // Inicialización
    println!("Generando matrices...");
    let a = initialize_matrix(n);
    let b = initialize_matrix(n);

    // -------------------------------------------------------------------------
    // Medir tiempo Secuencial
    // -------------------------------------------------------------------------
    println!("\nEjecutando versión secuencial...");
    let start_seq = Instant::now();
    let c_seq = multiply_sequential(&a, &b);
    let duration_seq = start_seq.elapsed();
    println!(
        "Tiempo secuencial: {:.4} segundos",
        duration_seq.as_secs_f64()
    );

    // -------------------------------------------------------------------------
    // Medir tiempo Paralelo
    // -------------------------------------------------------------------------
    println!("\nEjecutando versión paralela...");
    let start_par = Instant::now();
    let c_par = multiply_parallel(&a, &b);
    let duration_par = start_par.elapsed();
    println!(
        "Tiempo paralelo:   {:.4} segundos",
        duration_par.as_secs_f64()
    );

    // -------------------------------------------------------------------------
    // Verificación
    // -------------------------------------------------------------------------
    let valid = c_seq.iter().zip(c_par.iter()).all(|(row_s, row_p)| {
        row_s
            .iter()
            .zip(row_p.iter())
            .all(|(val_s, val_p)| (val_s - val_p).abs() < 1e-9)
    });

    if valid {
        println!("\nResultados coinciden.");
    } else {
        println!("\nADVERTENCIA: Los resultados no coinciden.");
    }
}
