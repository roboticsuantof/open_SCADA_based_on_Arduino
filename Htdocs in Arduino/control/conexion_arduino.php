<?php

require_once("herramienta_introducir_datos.php");

$herramienta = new Herramienta();
//if($_GET["F01T01SHum_php"]== null){
//echo "No se pudo obtener valores temperatura y humedad desde arduino";exit;
//}else{
$ingresar_dato = $herramienta->ingresar_datos($_GET["F01T01SHum_php"]);

?>
