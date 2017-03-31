<?php
if(isset($_GET['code'])) {
    $sessionKeep = $_SESSION['cat'];
    ob_start();
    include('index.inc');
    $ob = ob_get_clean();
    $_SESSION['cat'] = $sessionKeep;
    $find = array(
    'act=item',
    '<body class="index textborder">',
    '<a href="?act=ccategor" class="cbu cc button">',
    '<div class="cat">'
    );
    $replace = array(
    'act=scanner&code='.$_GET['code'],
    '<body class="index textborder associate">',
    '<a href="./" class="cbu associate button">Exit Associate</a><a href="?act=ccategor" class="cbu cc button">',
    '<div class="cat">'.$_GET['code'].'</div><div class="cat" style="display:none;">'
    );
    $output = str_replace($find, $replace, $ob);
    echo $output;
} else {
    header('location: ./');
}
?>