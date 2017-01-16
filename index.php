<?php
//Cedar Point//Dylan Bickerstaff//2016//CFIT Inventory

error_reporting(E_ALL);
ini_set('display_errors', 1);

require 'shaledatamanager.lib.php';

$_GET = filter_var_array($_GET, FILTER_SANITIZE_STRING);
$_POST = filter_var_array($_POST, FILTER_SANITIZE_STRING);

session_name('cfit');
session_start();

if(!isset($_SESSION['cat'])) {
    $_SESSION['cat'] = '';
}

if(isset($_GET['act']) && $_GET['act'] !== ''  && ctype_alpha($_GET['act']) && file_exists('act/'.$_GET['act'].'.inc')) {
    include 'act/'.$_GET['act'].'.inc';
} else {
    include 'act/index.inc';
}
?>