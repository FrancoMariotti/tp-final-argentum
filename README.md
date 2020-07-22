# Tp-final-argentum

# Argentum - TP final
### 1er cuatrimestre de 2020

**Integrantes:** \
    Alasino Franco 102165\
    Mariotti Franco 102223\
    Leguizamon Agustin 99535

    
* URL: https://github.com/FrancoMariotti/tp-final-argentum      

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


Advertencia:para ejecutar con esa ruta el 
directorio actual debe contener esa 
carpeta con ese archivo json. Caso 
contrario la aplicacion no va a correr.
```

4- Para ejecutar la aplicacion Cliente, ejecutar el siguiente comando:
```
argentumCliente
```

## Más información
- [Manual de usuario](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Manual%20de%20Usuario.pdf)
- [Documentación Técnica](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Documentacion%20Tecnica.pdf)
- [Manual de proyecto](https://github.com/FrancoMariotti/tp-final-argentum/tree/master/Documentos/Manual%20de%20Proyecto.pdf)
