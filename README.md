# Tp-final-argentum

# Argentum - TP final
### 1er cuatrimestre de 2020

**Integrantes:** \
    Alasino Franco 102165\
    Mariotti Franco 102223\
    Leguizamon Agustin 99535

    
* URL: https://github.com/FrancoMariotti/tp-final-argentum      

## El juego

El juego desarrollador es una variante del videojuego de rol multijugador conocido como AO(Argentum Online).En este el jugador conforma parte de un mundo habitado por NPCs (criaturas controladas por el juego) y otros jugadores. El jugador pueden combatir contra estas criaturas y otros jugadores para obtener oro, items y subir de nivel, y volverse cada vez más fuerte. En el juego existen ciudades donde los jugadores podrán comerciar, sanar sus heridas y depositar sus objetos, además estarán protegidos de criaturas y jugadores hostiles ya que las criaturas no pueden acceder y no se puede combatir en las ciudades.

<img src="https://github.com/FrancoMariotti/tp-final-argentum/blob/master/resources/pantalla_ingreso.png" width="852" height="651">

<img src="https://github.com/FrancoMariotti/tp-final-argentum/blob/master/resources/pantalla_juego.png" width="852" height="651">


## Instalación

1- Si no se poseen las dependencias (ver [Documentación Técnica](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Documentacion%20Tecnica.pdf), ejecutar el archivo
install.sh.​ Es decir: 
```
./install.sh
```

2- Una​ ​vez​ ​instaladas​ ​las​ ​dependencias,​bajar los paquetes .deb de la carpeta /packages y ejecutar los siguientes comandos:
```
dpkg -i argentumClientPackage.deb
dpkg -i argentumServerPackage.deb
```

3- Para ejecutar la aplicacion Servidor, ejecutar el siguiente comando:
```
argentumServidor config/config.json

Correr la aplicacion desde la carpeta src/Server porque sino no encuentra los archivos de persistencia.
Hay un problema con la ruta relativa que toma.

Nota: para ejecutar con esa ruta el 
directorio actual debe contener esa 
carpeta con ese archivo json. Caso 
contrario la aplicacion no va a correr.
```

4- Para ejecutar la aplicacion Cliente, ejecutar el siguiente comando:
```
Ejecutar la aplicacion instalada desde el acceso generado SimpleQt Client(En aplicaciones).
Sino tiene un problema similar a la aplicacion argentumServidor al ejecutarla desde la consola.
```

## Más información
- [Manual de usuario](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Manual%20de%20Usuario.pdf)
- [Documentación Técnica](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Documentacion%20Tecnica.pdf)
- [Manual de proyecto](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Manual%20de%20Proyecto.pdf)
