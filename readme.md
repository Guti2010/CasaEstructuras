    El programa posee un main en donde se pueden definir cuantas partes de cada una de las partes de la casa se quieren contruir y la cantidad de piezas que hay disponibles,
hay una clae para que s epueda crear cada una de las piezas y cada una de las partes de la casa en genereal, sin importar cual sea, ya en el método ConstruirCasa que recibe 
cada una de las partes de la casa que se desean y las piezas disponibles, se crean las partes base de la casa y segun se indique se van construyendo, hay que tomar en cuenta 
que si no hay ciminetos no se puyede crear una pared, si no hay 4 paredes al menos no se puede crear un techo, si hay una pared y se usa para poner una puerta y no hay más paredes, una ventana que también requiere de una pared,
no va a poder ser construida y el piso, la terraza y la piscina se puede crear en cualquier orden pero siguiendo 
esta prioridad vector<string> prioridad = {"Cimientos","Pared", "ParedConPuerta", "ParedConVentana", "Piso", "Techo", "Terraza", "Piscina"};

