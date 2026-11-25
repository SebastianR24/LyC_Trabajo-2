import time

def movimiento_valido(pos_actual, pos_nueva):
    dx = abs(ord(pos_actual[0]) - ord(pos_nueva[0]))
    dy = abs(int(pos_actual[1]) - int(pos_nueva[1]))
    return (dx == 1 and dy == 2) or (dx == 2 and dy == 1)

def verificar_movimientos(ak, cadena_movimientos):
    movimientos = cadena_movimientos.split()
    pos_actual = ak
    
    for i, mov in enumerate(movimientos):
        # Verificar la notación de la pieza
        if mov[0] != 'K':
            return f"movimiento INCORRECTO falla letra {mov[0]} no pertenece a un caballo."
        
        pos_nueva = mov[1:]
        
        # Verificar si el salto en 'L' es válido
        if not movimiento_valido(pos_actual, pos_nueva):
            return f"INCORRECTO falla en el movimiento {i + 1}."
            
        pos_actual = pos_nueva
        
    return "movimiento CORRECTO."

def main():
    # Casos de prueba solicitados en el documento
    print(verificar_movimientos("a1", "Kc2 Kd4 Kb3 Kc5"))
    print(verificar_movimientos("a1", "Kc2 Kd4 Kb4 Kc5"))
    print(verificar_movimientos("a8", "Kb6 Kd7"))
    print(verificar_movimientos("a1", "Kc2 Kd4 Kf3 Ke5 Kg6 Kh8 Kf7 Kd8 Kc6 Qb4"))
    
    # Cadena de 500 movimientos para la prueba de rendimiento
    movimientos_500 = (
        "Kb4 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 "
        "Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 "
        "Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 "
        "Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 "
        "Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 "
        "Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 "
        "Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg1 Kh3 Kg5 Ke6 Kc5 Ka4 Kc3 "
        "Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd6 Kb7 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Ka6 Kb8 Kd7 "
        "Kb6 Ka8 Kc7 Ka6 Kc5 Ka4 Kc3 Ka2 Kc1 Ke2 Kg3 Kh5 Kg7 Ke8 Kc7 Ka8 Kc7 Kb5 Kd4 Kb3 Ka1 Kc2 Ka3 "
        "Kc4 Ka5 Kc6 Ka7 Kc8 Ka7 Kc6 Ka5 Kc4 Ka3 Kc2 Ka1 Kc2 Kb4 Kd5 Kb6 Ka8"
    )
    
    # Medición de tiempo (10 iteraciones)
    inicio = time.perf_counter()
    for _ in range(10):
        # Asumimos inicio en a2 para que el primer salto a Kb4 sea válido, 
        # o simplemente lo evalúa hasta donde falle.
        resultado_500 = verificar_movimientos("a2", movimientos_500)
    fin = time.perf_counter()
    
    tiempo_total = fin - inicio
    
    # Escritura en archivo txt
    with open("resultado.txt", "a") as f:
        f.write(f"Tiempo Python (10 iteraciones, 500 movs): {tiempo_total:.6f} segundos\n")
    print(f"Medición guardada en resultado.txt. Tiempo: {tiempo_total:.6f} s")

if __name__ == "__main__":
    main()