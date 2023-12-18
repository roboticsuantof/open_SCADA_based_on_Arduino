# open_SCADA_based_on_Arduino
El Sistema de Control y Adquisición de Datos (SCADA) implementado para un invernadero se elige como un entorno inteligente y automatizado, integrando tecnologías como PHP, Arduino IDE y una base de datos en XAMPP. Este sistema persigue mediante la estación de monitoreo, visualizar las variables constantemente.

![MonitoreoTiempoReal](https://i.imgur.com/udldEcx.png)
![GraficoyDescargadeDatos](https://i.imgur.com/AgYPiO6.png)

***La comunicación entre los Arduinos que tendrán la lectura inicial de los sensores, serán denominados como “Slave”, mientras que, los Arduinos encargados de recibir la información y subirlos a la estación de monitoreo, serán denominados como “Master”.***

# Instalación Programas

Los siguientes programas se deben descargar e instalar en su última versión desde sus paginas oficiales:

1. [Arduino IDE](https://www.arduino.cc/en/software): Se utiliza para la programación de la placa Arduino, actuando como el corazón del sistema al interactuar con los sensores y actuadores instalados en el invernadero. Los sensores capturan datos cruciales como temperatura, humedad, luminosidad, niveles de CO2, entre otros, mientras que los actuadores controlan elementos como sistemas de riego, ventilación y calefacción.

2. [XAMPP Control Panel](https://www.apachefriends.org/es/download.html): Actúa como el repositorio central de datos, almacenando la información adquirida por los sensores y generando un historial completo de las condiciones del invernadero. La estructura de la base de datos se ha diseñado para permitir consultas eficientes, análisis de tendencias y generación de informes.

3. [IP Advanced Scanner](https://www.advanced-ip-scanner.com/es/): Herramienta que se utiliza para escanear y analizar redes informáticas en busca de dispositivos conectados y para recopilar información detallada sobre estos dispositivos y su configuración de red. Permite realizar la busqueda de las ip disponibles para la programación de arduino.


# Programación

En esta fase del sistema, es necesario la configuración de los archivos de programación para su posterior instalación en las carpetas correspondientes, por lo que se deben descargar los siguientes archivos:

1. Arduinos: (https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/tree/main/Arduino%20NRF24L01%20-%20Comunicacion%20Inalambrica, branch: Main)
2. Estación de Monitoreo: (https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/tree/main/Htdocs%20in%20Arduino, branch: Main)

# Configuraciones

1. Descargar e instalar programa de Arduino IDE.
2. Abrir los archivos descargados (1) del apartado "# Programación" e insertar variables a medir.
- [“Master”](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/tree/main/Arduino%20NRF24L01%20-%20Comunicacion%20Inalambrica/MaestroARD): Usar como referencia "F01T01SHum", sólo deberás replicar este codigo asignando nuevo nombre y datos recibidos. 
Ejemplo:
```
F01T01SHum=datos[1];
F02T02STemp=datos[2];
.
.
.
F0nT0nS(nombresensor)=datos[n];
```
Este mismo ejemplo replicarlo cada vez que se repita la variable en el código. Por otro lado, en este caso se le asigna una ip al Arduino “Master” que contiene un shield ethernet. Esta ip la podemos buscar de las disponibles analizadas por el programa Advanced IP Scanner indicado en el apartado de "#Instalación de Programas" punto 3. Este programa te muestra las ips que están siendo ocupadas en el rango indicado, por lo que si no aparece es porque está disponible.

Ejemplo:
Insertamos la ip del servidor que siempre será la que aparezca de primera opción en el buscador del programa Advanced IP Scanner. En este caso es: 172. 16. 30. 201
Por lo que lo insertamos en la siguiente variable:
```
byte server []={ 172, 16, 30, 201 }
```
e insertamos la Direccion IP a utilizar por el Arduino:
```
byte ip []={ 172, 16, 30, 2nn }
```
Donde "n" son los numeros de la ip que estan disponible y podemos seleccionar cualquiera, que en este caso la que se encuentra disponible y se utiliza es:
```
byte ip []={ 172, 16, 30, 207 }
```
- [“Slave”](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/tree/main/Arduino%20NRF24L01%20-%20Comunicacion%20Inalambrica/SlaveARD): Para este caso es más sencillo, ya que solo declaramos las variables a medir mediante los canales analogicos de arduino. En este caso deberemos replicar los siguientes codigos según necesidad:

Para datos enviados:
```
datos[1]=analogRead(A1)
datos[3]=analogRead(A2)
.
.
.
datos[n]=analogRead(An)
```
Para poder visualizar mediante el monitor serial del programa de Arduino IDE, deberás replicar el siguiente codigo las veces que sea necesario.
```
Serial.print("Datos enviados:")
Serial.println(datos[1])
Serial.println(datos[3])
.
.
.
Serial.println(datos[n])
```
Evitando ocupar para ambos casos datos[2], dado que, este es ocupado durante la programación para el envio de datos. 

3. Abrir los archivos descargados (2) del apartado "# Programación" e insertar variables para que sean recibidas por la estación de monitoreo.
- [Control](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/blob/main/Htdocs%20in%20Arduino/control/conexion_arduino.php): En este archivo solo se deberá replicar el siguiente código:
```
$ingresar_dato = $herramienta->ingresar_datos($_GET["F01T01SHum_php", "F02T02STemp_php", - - -, "F0nT0nS(nombredesensor)_php"])
```
- [Control](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/blob/main/Htdocs%20in%20Arduino/control/herramienta_introducir_datos.php): En este archivo solo se deberá replicar el siguiente código:
```
public function ingresar_datos($F01T01SHum_php, $F02T02STemp_php, ..., $F0nT0nS(nombredesensor)_php){
		$sql = " insert into tabla_sensor values (null, ?, ?, ..., n?, now()) "
		$stmt = $this->conexion->conexion->prepare($sql)

		$stmt->bindValue(1, $F01T01SHum_php, $F02T02STemp_php, ..., $F0nT0nS(nombredesensor)_php)
``` 
En la parte de "?" significan las variables que se insertarán y esto va directamente con los sensores colocados, por lo que si coloca 7 sensores, deberían haber 7 "?".

- [Grafico](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/blob/main/Htdocs%20in%20Arduino/grafico/generate_pdf.php): En este archivo se deberán replicar las siguientes dos lineas de código:
```
$display_heading = array('id'=>'ID', 'F01T01SHum'=> 'F01T01SHum', 'F02T02STemp'=> 'F02T02STemp', ..., 'F0nT0nS(nombredesensor)'=> 'F0nT0nS(nombredesensor)', 'fecha_hora'=> 'Fecha y hora',)

$result = mysqli_query($connString, "SELECT id, F01T01SHum, F02T02STemp, ..., F0nT0nS(nombredesensor), fecha_hora FROM tabla_sensor")
```
- [Graficos](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/blob/main/Htdocs%20in%20Arduino/grafico/grafico.php): En los gráficos de los sensores, se deberán replicar las líneas de códigos que incluyan al nombre de la variable.

Ejemplo: 
```
            {   name: 'F'F0nT0nS(nombresensor)',
                data: [
                <?php
                    $query = " select 'F0nT0nS(nombresensor) from tabla_sensor order by id desc limit 10 ";
                    $resultados = mysqli_query($connection, $query);
                    while($rows = mysqli_fetch_array($resultados)){
                        ?>
                            <?php echo $rows["'F0nT0nS(nombresensor)"]?>,
                        <?php
                    }
                ?>]
            }
```
El código se deberá replicar en su forma completa y sustituyendo el nombre de la variable "F01T01SHum" por las varibles que insertamos anteriormente.


# Configuración de Estación de Monitoreo

Una vez se haya descargado e instalado el programa "XAMPP CONTROL PANEL", procederemos con su configuración y nos dirigiremos a su carpeta de origen. En esta, existe una carpeta llamada "htdocs" la cual procederemos a seleccionar y abrir. Una vez dentro, creamos la carperta bajo el nombre "arduino" e insertamos todos los archivos configurados anteriormentes de la sección "# Configuraciones", exceptuando el archivo "Insert SQL in PHP" que ocuparemos más adelante. 

Una vez hecho esto, configuraremos el siguiente archivo para crear la tabla de la base de datos:
[InsertTabla](https://github.com/roboticsuantof/open_SCADA_based_on_Arduino/blob/main/Htdocs%20in%20Arduino/Insert%20SQL%20in%20PHP.sql)

En el cual, solo deberemos replicar la linea de código de las variables de los sensores usados anteriormente, tal que:
```
CREATE TABLE IF NOT EXISTS `tabla_sensor` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `F01T01SHum` int(2) NOT NULL,
  `F02T02STemp` int(2) NOT NULL,
  .
  .
  .
  `F0nT0nS(nombredesensor)` int(2) NOT NULL,
  `fecha_hora` datetime NOT NULL,
```
Una vez hecho lo anterior, iniciamos el programa "XAMPP CONTROL PANEL", seguimos los siguientes pasos:

1. Iniciar el Modulo de "Apache" y "MySQL"
2. Ingresar a nuestro navegador de preferencia y escribir en la barra de busqueda "localhost".
3. Ir a la sección de PHPMyAdmin
4. Crear una nueva base de datos llamada "ardbd"
5. Seleccionar la base de datos "ardbd" y seleccionar el apartado de "SQL"
6. Ingresamos el código configurado de [InsertTabla] y le damos continuar
7. Actualizar página y verificar que la tabla fue creada con nuestras variables
8. Cerramos navegador y apagamos modulos

# Visualización del programa

Una vez hecho todos los pasos anteriores y realizadas las conexiones fisicas de los arduino, se inicia nuevamente el programa "XAMPP CONTROL PANEL" para poder visualizar el monitoreo de las variables. Para esto, se deben seguir los siguientes pasos:

1. Iniciar programa "XAMPP CONTROL PANEL"
2. Iniciar modulos "Apache" y "SQL"
3. Abrir navegador de preferencia y escribir en la barra de búsqueda "localhost"
4. Ir a la sección PHPMyAdmin
5. Seleccionar el apartado creado anteriormente "ardbd" y verificar la actualización de datos
6. Abrir otra pestaña y escribir en la barra de busqueda "/arduino/grafico"

Siguiendo los pasos anteriores se podrán visualizar los datos tanto en la base de datos como en los graficos creados. Además, se pueden descargar estos datos mediante las dos opciones entregadas por "/arduino/grafico" de descarga de datos en PDF y Excel.


