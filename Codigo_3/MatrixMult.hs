import Control.Exception (evaluate)
import Control.DeepSeq (force)
import Data.List (transpose)
import System.CPUTime (getCPUTime)
import Text.Printf (printf)
import Control.Parallel.Strategies (using, parList, rdeepseq)

-- Definimos la Matriz como una lista de listas de Doubles
type Matrix = [[Double]]

-- Generador determinista de matrices (para evitar complejidad de IO con Random)
-- Crea una matriz de N x N donde el valor depende de i y j
buildMatrix :: Int -> Matrix
buildMatrix n = 
    [ [ sin (fromIntegral (i * n + j)) | j <- [1..n] ] | i <- [1..n] ]

-- -----------------------------------------------------------------------------
-- Lógica Central: Producto Punto
-- -----------------------------------------------------------------------------
dotProduct :: [Double] -> [Double] -> Double
dotProduct row col = sum $ zipWith (*) row col

-- -----------------------------------------------------------------------------
-- Versión Secuencial
-- -----------------------------------------------------------------------------
-- El algoritmo es: Para cada fila de A, multiplicarla por cada columna de B.
-- Truco de Haskell: Transponemos B primero para trabajar con sus "filas" cómodamente.
multSeq :: Matrix -> Matrix -> Matrix
multSeq a b = 
    let bTransposed = transpose b
    in [ [ dotProduct row col | col <- bTransposed ] | row <- a ]

-- -----------------------------------------------------------------------------
-- Versión Paralela (Strategies)
-- -----------------------------------------------------------------------------
-- Aquí ocurre la magia. Usamos la misma lógica que 'multSeq', pero añadimos
-- una "Estrategia de Evaluación" (`using`).
multPar :: Matrix -> Matrix -> Matrix
multPar a b = 
    let bTransposed = transpose b
        result = [ [ dotProduct row col | col <- bTransposed ] | row <- a ]
    in result `using` parList rdeepseq 
    -- `parList`: Evalúa cada elemento de la lista (cada fila) en paralelo.
    -- `rdeepseq`: Fuerza la evaluación completa de la fila (deep evaluation).

-- -----------------------------------------------------------------------------
-- Utilidades para medir tiempo
-- -----------------------------------------------------------------------------
time :: IO t -> IO t
time a = do
    start <- getCPUTime
    v <- a
    end   <- getCPUTime
    let diff = (fromIntegral (end - start)) / (10^12)
    printf "Tiempo de ejecución: %0.3f seg\n" (diff :: Double)
    return v

main :: IO ()
main = do
    let n = 500 -- Puedes subir a 400 o 500 si sigue siendo muy rápido
    
    putStrLn $ "Generando matrices de " ++ show n ++ "x" ++ show n ++ "..."
    -- Forzamos la creación de las matrices antes de empezar a medir nada
    let matA = force $ buildMatrix n
    let matB = force $ buildMatrix n
    
    -- Evaluar matA y matB aquí para que no afecten al tiempo de multiplicación
    evaluate matA
    evaluate matB

    putStrLn "Calculando Versión Secuencial..."
    -- Usamos 'evaluate $ force', Esto asegura que el cálculo ocurra DENTRO de la función 'time'
    resultSeq <- time $ evaluate (force (multSeq matA matB))

    putStrLn "\nCalculando Versión Paralela..."
    resultPar <- time $ evaluate (force (multPar matA matB))

    putStrLn "\nVerificación completada."